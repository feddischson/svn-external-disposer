// SVN-Externals-Disposer 
//
// Copyright (C) 2015  Christian Haettich [feddischson]
//
// This program is free software; you can redistribute it 
// and/or modify it under the terms of the GNU General Public 
// License as published by the Free Software Foundation; 
// either version 3 of the License, or (at your option) 
// any later version.
//
// This program is distributed in the hope that it will 
// be useful, but WITHOUT ANY WARRANTY; without even the 
// implied warranty of MERCHANTABILITY or FITNESS FOR A 
// PARTICULAR PURPOSE. See the GNU General Public License 
// for more details.
//
// You should have received a copy of the GNU General 
// Public License along with this program; if not, see 
// <http://www.gnu.org/licenses/>. 
//
#include <QDebug>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include <QDomDocument>

#include "const.h"
#include "data_model.h"

namespace SVN_EXTERNALS_DISPOSER
{


Data_Model::Data_Model(  const QString  & path, 
                                 QObject *parent )
   : QAbstractItemModel( parent ),
     external_matcher( EXTERNAL_REGEX ),
     old_external_matcher( OLD_EXTERNAL_REGEX ),
     root_item( nullptr )
{
   if( path.size() > 0 )
   {
      QList<QVariant> root_data;
      root_data  << GUI_HEAD_FOLDER
                 << GUI_HEAD_EXTERNAL  
                 << GUI_HEAD_PEG      
                 << GUI_HEAD_OPERATIVE;

      root_item = new Item( root_data, false );
      setup_model_data( path, root_item );
   }
}

Data_Model::~Data_Model( )
{
   if( root_item != nullptr)
      delete root_item;
}



bool Data_Model::setData( const QModelIndex & index,
                              const QVariant & value, int )
{
   Item *item = static_cast<Item*>(index.internalPointer());
   item->set_data( index.column(), value );
   return true;
}


QVariant Data_Model::data(const QModelIndex &index, int role) const 
{
   if (!index.isValid())
       return QVariant();

   if (role != Qt::DisplayRole)
       return QVariant();

   Item *item = static_cast<Item*>(index.internalPointer());

   return item->data(index.column());
}


Qt::ItemFlags Data_Model::flags(const QModelIndex &index) const 
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}


QVariant Data_Model::headerData(int section, Qt::Orientation orientation,
                     int role ) const 
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root_item->data(section);

    return QVariant();
}


QModelIndex Data_Model::index( int row, int column,
                            const QModelIndex &parent ) const 
{
   if (!hasIndex(row, column, parent))
       return QModelIndex();

   Item *parent_item;

   if (!parent.isValid())
       parent_item = root_item;
   else
       parent_item = static_cast<Item*>(parent.internalPointer());

   Item *childItem = parent_item->child(row);
   if (childItem)
       return createIndex(row, column, childItem);
   else
       return QModelIndex();
}


QModelIndex Data_Model::parent( const QModelIndex &index) const 
{
   if (!index.isValid())
       return QModelIndex();

   Item *child_item = static_cast<Item*>(index.internalPointer());
   Item *parent_item = child_item->get_parent_item();

   if ( parent_item == root_item)
       return QModelIndex();

   return createIndex( parent_item->row(), 0,  parent_item );
}


int Data_Model::rowCount( const QModelIndex &parent ) const 
{
   Item *parent_item;
   if (parent.column() > 0)
       return 0;

   if (!parent.isValid())
       parent_item = root_item;
   else
       parent_item = static_cast<Item*>( parent.internalPointer() );

   return parent_item->child_count();
}


int Data_Model::columnCount( const QModelIndex &parent ) const 
{
   if (parent.isValid())
       return static_cast<Item*>(parent.internalPointer())->column_count();
   else
       return root_item->column_count();
}


void Data_Model::setup_model_data( 
      const QString                  & path,
      Item * parent )
{
   QDir dir( path ); 
   QList<Item*> parents;
   parents << parent;

   // A hash-map, storing paths as key and the property as value
   QMap< QString, QString >         external_map;

   // A hash-map, storing local-paths as key and External_Items as value
   QMap< QString, Item* >  external_children;


   // read the external property of 'path'
   read_externals( path, &external_map );


   // ensure, that the path is correct
   if( external_map.contains( path) )
      external_children = extract_externals( parent, external_map.value( path ) );
   // TODO: check if there is a sub-path entry

   // get all directories without . and ..
   QFileInfoList files = dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );

   // loop over all entries 
   foreach(const QFileInfo &file, files) 
   {
      QString child_path = file.absoluteFilePath();  
      QList<QVariant> column_data;

      Item * child;
      if( external_children.contains( file.fileName() ))
         child = external_children[ file.fileName() ];
      else
      {
         column_data << file.fileName()
                     << EMPTY_STRING
                     << EMPTY_STRING
                     << EMPTY_STRING;
         child = new Item( column_data, false, parents.last() );
      }
      parents.last()->append_child( child );

      if( file.isDir() ) 
         // recursive call to add all sub-paths
         setup_model_data( child_path, child );             
   }
}


bool Data_Model::read_externals( 
      const QString & path,
      QMap< QString, QString > * external_map )
{

   // start a svn propget svn:externals process
   QProcess process;
   process.start( SVN_CMD, QStringList() 
         << SVN_PROPGET
         << SVN_EXTERNALS
         << SVN_XML
         << SVN_DEPTH
         << SVN_FILES
         << path );


   // wait until the process is done
   // and check the result
   if( process.waitForFinished( SYS_PROCESS_TIMEOUT ) && 
       process.exitCode() == 0 )
   {

      // Parse the XML result
      QDomDocument doc;
      if ( !doc.setContent( process.readAllStandardOutput() ) )
         return false;
      QDomNodeList targets = doc.elementsByTagName( XML_NAME_TARGET );

      // and iterate over all svn:externals properties.
      // If we have a valid entry, add the entry to the external_map.
      for (int i = 0; i < targets.size(); i++) {

         QDomNode target   = targets.item(i);
         QDomElement value = target.firstChildElement( XML_NAME_PROPERTY );

         if( !value.isNull()          && 
              target.hasAttributes( ) && 
              target.attributes().contains( XML_NAME_PATH ) )
         {
            QDomElement e    = target.toElement();
            QString     path = e.attribute( XML_NAME_PATH, "" );
            QString     prop = value.text();
            external_map->insert( path, prop );
         }
      }
   }
   else
      return false;

   return true;
}


QMap< QString, Item* > Data_Model::extract_externals( 
            Item * parent, 
      const QString       & external_property )
{

   QMap< QString, Item* >  external_children;
   foreach (
         const QString &str, 
         external_property.split( SVN_EXTERNAL_SEP, QString::SkipEmptyParts )  ) 
   {

      QList<QVariant> column_data = parse_external( str );

      if( column_data.size() > 0 )
      {
         Item * child = new Item( column_data, true, parent );
         external_children.insert( external_matcher.cap(6), child );
      }
   }
   return external_children;
}


QList< QVariant > Data_Model::parse_external( const QString & entry )
{
   QList<QVariant> column_data;
   int pos;

   // first: try the old syntax
   pos = old_external_matcher.indexIn( entry );
   if( pos > -1 )
   {

      column_data << old_external_matcher.cap(1);
      column_data << old_external_matcher.cap(4);
      column_data << QString("");
      column_data << old_external_matcher.cap(3);
   }
   else
   {

      // second: try the current syntax
      pos = external_matcher.indexIn( entry );

      if( pos > -1 )
      {
         column_data << external_matcher.cap(6);
         column_data << external_matcher.cap(3);
         column_data << external_matcher.cap(5);
         column_data << external_matcher.cap(2);
      }
   }
   return column_data;
}



}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

