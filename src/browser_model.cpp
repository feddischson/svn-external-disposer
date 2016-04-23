// SVN-Externals-Disposer 
//
// Copyright (C) 2016  Christian Haettich [feddischson]
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
#include <QProcess>
#include <QDebug>
#include <QDomDocument>

#include "browser_model.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{

Browser_Model::Browser_Model( 
      const QString & , 
      const QString & url,
      const QString & revision,
      QObject *parent ) 
   : QAbstractItemModel( parent ),
   root_item( nullptr ),
   url( url ),
   root_url( "" ),
   revision( revision )
{
   if( get_url_paths( url ) &&
       root_url.size() > 0 )
   {
      root_item = new Browser_Item( root_url,
            revision,
            QList< QVariant> () 
            << GUI_HEAD_NAME
            << GUI_HEAD_KIND 
            << GUI_HEAD_REVISION
            << GUI_HEAD_AUTHOR
            << GUI_HEAD_DATE
            << GUI_HEAD_SIZE
         );
   }
}

bool Browser_Model::get_url_paths( const QString & url )
{
   bool succ = true;

   QProcess process;
   process.start( SVN_CMD, QStringList() 
         << SVN_INFO 
         << url
         << SVN_XML );

   if( process.waitForFinished( SYS_PROCESS_TIMEOUT ) && 
       process.exitCode() == 0 ) // wait 3 seconds
   {
      // Parse the XML result
      QDomDocument doc;
      if ( !doc.setContent( process.readAllStandardOutput() ) )
      {
         qDebug() << "Failed to receive the svn info";
         succ = false;
      }
      else
      {
         QDomNodeList root = doc.elementsByTagName( XML_NAME_ROOT );
         if( root.count() != 1 )
         {
            qDebug() << "expected only one root entry in svn info";
            succ = false;
         }
         else
            root_url = root.item(0).toElement().text();
      }
   }
   else
      succ = false;

   return succ;

}


QVariant Browser_Model::data( const QModelIndex & index, int role ) const
{
   if (!index.isValid())
      return QVariant();

   if (role != Qt::DisplayRole)
      return QVariant();

   Browser_Item *item = static_cast< Browser_Item * >( index.internalPointer() );
      return item->data(index.column());
}

Qt::ItemFlags Browser_Model::flags( const QModelIndex & index ) const 
{
   if (!index.isValid())
      return 0;
   return QAbstractItemModel::flags(index);
}

QVariant Browser_Model::headerData( int section, 
                     Qt::Orientation orientation,
                     int role ) const 
{

   if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return root_item->data(section);
   return QVariant();
}

QModelIndex Browser_Model::index(   
                     int row, 
                     int column, 
                     const QModelIndex & parent ) const 
{
   if( !hasIndex( row, column, parent ) )
      return QModelIndex();


   Browser_Item * parent_item;

   if( !parent.isValid() )
      parent_item = root_item;
   else
      parent_item = static_cast< Browser_Item* >( parent.internalPointer() );

   Browser_Item * child_item = parent_item->child( row );
   if( child_item )
      return createIndex( row, column, child_item );
   else
      return QModelIndex();

}

QModelIndex Browser_Model::index( const QString & url )
{

   if( root_url.size() > url.size() )
      return QModelIndex();

   QStringRef beginning( &url, 0, root_url.size() );
   if ( beginning != root_url )
      return QModelIndex();

   QStringRef end( 
         &url, 
         root_url.size(), 
         url.size() - root_url.size()  );

   auto x = end.split("/", QString::SkipEmptyParts );
   return get_index_for_url( x, 0, root_item );
}

QModelIndex Browser_Model::get_index_for_url( 
      const QVector<QStringRef> & list, 
      int index, 
      Browser_Item * parent )
{

   bool found = false;

   if( root_item == nullptr )
      return QModelIndex();


   if( index == list.size() )
   {
      return createIndex( parent->row(), 0, parent );
   }

   Browser_Item * child = nullptr;
   for( int i=0; i < parent->child_count() ; i++ )
   {
      child = parent->child( i );
      if( child->data( BROWSER_I_NAME ).toString() ==  list.value( index ) )
      {
         found = true;
         break;
      }
   }

   if( found )
      // do the recursive call
      return get_index_for_url( list, index+1, child );
   else
      return QModelIndex();
}


QModelIndex Browser_Model::parent( const QModelIndex & index ) const 
{
   if( !index.isValid() )
      return QModelIndex();

   Browser_Item * child_item  = static_cast< Browser_Item * >( index.internalPointer() );
   Browser_Item * parent_item = child_item->parent();

   if(   parent_item == nullptr ||
         parent_item == root_item )
      return QModelIndex();

   return createIndex( parent_item->row(), 0, parent_item );


}

int Browser_Model::rowCount( const QModelIndex & parent ) const
{

   Browser_Item * parent_item;

   if( root_item == nullptr )
      return 0;

   if (parent.column() > 0)
      return 0;

   if (!parent.isValid())
      parent_item = root_item;
   else
      parent_item = static_cast< Browser_Item * >( parent.internalPointer() );

   return parent_item->child_count();
}

int Browser_Model::columnCount( const QModelIndex & parent ) const
{
   if( root_item == nullptr )
      return 0;

   if ( parent.isValid() )
      return static_cast< Browser_Item * >( parent.internalPointer() )->column_count();
   else
      return root_item->column_count();
}





QString Browser_Model::get_url( void )
{
   return url;
}

QString Browser_Model::get_root_url( void )
{
   return root_url;
}






Browser_Model::~Browser_Model()
{
   delete root_item;
}

}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

