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
#include <QDomDocument>


#include "log_dialog.h"

namespace SVN_EXTERNALS_DISPOSER
{

Log_Dialog::Log_Dialog( 
      const QString & working_cp_path, 
      QWidget *parent  ) 
   : QDialog( parent ),
     working_cp_path( working_cp_path ),
     was_selected( false )
{
   ui.setupUi(this);
   ui.log_TW->setColumnCount( 4 );
   ui.log_TW->verticalHeader ()->hide();
   ui.log_TW->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui.log_TW->setSelectionMode(QAbstractItemView::SingleSelection);

   QStringList headers;
   headers << GUI_HEAD_REVISION
           << GUI_HEAD_AUTHOR
           << GUI_HEAD_MESSAGE
           << GUI_HEAD_DATE;
   ui.log_TW->setHorizontalHeaderLabels( headers );




   QHeaderView * view = ui.log_TW->horizontalHeader();
   view->setSectionResizeMode(QHeaderView::Stretch);
   load_svn_log();
   update_table();
}

bool Log_Dialog::load_svn_log(
      quint64 from,
      quint64 n )
{
   QProcess process;

   if( from == std::numeric_limits< quint64 >::max() )
   {
      process.start( SVN_CMD, QStringList() 
            << SVN_LOG 
            << SVN_ALL_REVPROPS
            << SVN_XML 
            << SVN_LIMIT 
            << QString::number( n ) 
            << working_cp_path );
      if( process.waitForFinished( SYS_PROCESS_TIMEOUT ) && 
          process.exitCode() == 0 ) 
      {
         QDomDocument doc;
         QString content = process.readAllStandardOutput();
         if ( !doc.setContent( content ) )
            return false;
         QDomNodeList logs  = doc.elementsByTagName( XML_NAME_LOG );

         if( logs.size() != 1 )
            return false;

         QDomNodeList entries = logs.item(0).childNodes();
         for( int i=0; i < entries.size(); i++ )
         {
            QDomNode entry = entries.item(i);

            if( entry.hasAttributes() && 
                entry.attributes().contains( XML_NAME_REVISION ) )
            {
               QString date   = "";
               QString msg    = "";
               QString author = "";
               QDomElement e    = entry.toElement();
               QString revision = e.attribute( XML_NAME_REVISION, "" );

               QDomNodeList content = entry.childNodes();
               for( int j=0; j < content.size(); j++ )
               {
                  QString name = content.item( j ).nodeName();
                  QString value  = content.item( j ).toElement().text();
                  if( name == XML_NAME_DATE )
                     date = value;
                  else if( name == XML_NAME_MSG )
                     msg = value;
                  else if( name == XML_NAME_AUTHOR )
                     author = value;
               }
               log_list.append( SVN_Log( revision, author, msg, date ) );
            }
         }
      }
      else
         return false;
   }

   return true;
}


void Log_Dialog::update_table( void )
{
   int table_entries = ui.log_TW->rowCount();
   int log_entries   = log_list.size();
   int delta         = log_entries - table_entries;
   int start         = log_entries - delta;

   ui.log_TW->setRowCount( ui.log_TW->rowCount() + delta );
   for( int i=0; i < delta; i++ )
   {
      SVN_Log l = log_list[ i ];
      ui.log_TW->setItem( i + start, 0, new QTableWidgetItem( l.revision ) );
      ui.log_TW->setItem( i + start, 1, new QTableWidgetItem( l.author   ) );
      ui.log_TW->setItem( i + start, 2, new QTableWidgetItem( l.message  ) );
      ui.log_TW->setItem( i + start, 3, new QTableWidgetItem( l.date     ) );
   }

   // if there are entries and this is the first call
   //   -> select the first row
   if( !was_selected && delta > 0 )
   {
      was_selected = false;
      ui.log_TW->selectRow( 0 );
   }

}


QVariant Log_Dialog::get_revision( void )
{
   auto l = ui.log_TW->selectionModel()->selectedRows( 0 );
   return l[0].data();
}


void Log_Dialog::on_load_more_PB_clicked( void )
{
   qDebug() << "should load more";
}



Log_Dialog::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Log_Dialog ("  << reinterpret_cast< void* >( this ) << "): "
       << "TODO=" << "Add more content of this instance here @ " 
       << __FILE__ << ":" << __LINE__;
   return s;
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

