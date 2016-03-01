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

#include "browser_item.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{



Browser_Item::Browser_Item( 
         const QString & url_path, 
         const QString & revision,
         const QList< QVariant> & content, 
         Browser_Item *parent_item ) :
   QObject( parent_item ),
   item_data( content ),
   parent_item( parent_item ),
   url_path( url_path ),
   children_loaded( false ),
   revision( revision )
{
   // nothing more to do here ..
}



Browser_Item::~Browser_Item( )
{
   qDeleteAll( child_items );
}

void Browser_Item::load_children( void )
{

   if( children_loaded )
      return;

   if( item_data[ BROWSER_I_KIND ] != "dir" && parent_item != nullptr )
   {
      children_loaded = true;
      return;
   }


   QProcess process;
   qDeleteAll( child_items );

   process.start( SVN_CMD, QStringList() 
         << SVN_LIST 
         << url_path
         << SVN_XML
         << SVN_REVISION 
         << revision );
   if( process.waitForFinished( SYS_PROCESS_TIMEOUT ) && 
       process.exitCode() == 0 ) // wait 3 seconds
   {
      // Parse the XML result
      QDomDocument doc;
      if ( !doc.setContent( process.readAllStandardOutput() ) )
      {
         qDebug() << "Failed to receive the svn list";
         return;
      }
      else
      {
         QDomNodeList entries = doc.elementsByTagName( XML_NAME_ENTRY );

         // and iterate over all Entries.
         for (int i = 0; i < entries.size(); i++) 
         {
            QString name      = "";
            QString kind      = "";
            QString revision  = "";
            QString author    = "";
            QString date      = "";
            QString size      = "";

            QDomNode entry   = entries.item(i);

            if( entry.hasAttributes() && 
                entry.attributes().contains( XML_NAME_KIND ) )
            {
               QDomElement e    = entry.toElement();
               kind = e.attribute( XML_NAME_KIND, "" );
            }

            QDomElement name_element   = entry.firstChildElement( XML_NAME_NAME   );
            QDomElement size_element   = entry.firstChildElement( XML_NAME_SIZE   );
            QDomElement commit_element = entry.firstChildElement( XML_NAME_COMMIT );

            if( !name_element.isNull() )
               name = name_element.text();
            else
            {
               qDebug() << "Failed to read the name, skipping element";
               continue;
            }

            if( !size_element.isNull() )
               size = size_element.text();


            if( !commit_element.isNull() )
            {
               if( commit_element.hasAttributes() && 
                   commit_element.attributes().contains( XML_NAME_REVISION ) )
                  revision = commit_element.toElement().attribute( XML_NAME_REVISION, "" );


               QDomElement author_element = commit_element.firstChildElement( XML_NAME_AUTHOR );
               QDomElement date_element   = commit_element.firstChildElement( XML_NAME_DATE   );

               if( !author_element.isNull() )
                  author = author_element.text();

               if( !date_element.isNull() )
                  date = date_element.text();

            }

            child_items.append( new Browser_Item( url_path + "/" + name, revision,
                 QList< QVariant> () 
                 << name
                 << kind 
                 << revision
                 << author
                 << date
                 << size, this
               ) );
         }
      }
   }
   children_loaded = true;
}



Browser_Item * Browser_Item::child( int row )
{
   load_children();
   return child_items.value( row );
}

int Browser_Item::child_count( void ) 
{
   this->load_children();
   return child_items.count();
}

int Browser_Item::row( void ) const
{
   if( parent_item)
      return parent_item->child_items.indexOf( const_cast< Browser_Item* > ( this ) );
   return 0;
}

int Browser_Item::column_count() const
{
   return item_data.count();
}

QVariant Browser_Item::data( int col ) const
{
   return item_data.value( col );
}

Browser_Item* Browser_Item::parent( void )
{
   return parent_item;
}

QString Browser_Item::url( void )
{
   return url_path;
}

Browser_Item::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Browser_Item ("  << reinterpret_cast< void* >( this ) << "): "
       << url_path;
   return s;
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

