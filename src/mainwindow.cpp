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

#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <const.h>
#include <QProcess>

#include "mainwindow.h"

namespace SVN_EXTERNALS_DISPOSER
{

Main_Window::Main_Window( QWidget *parent  ) 
   : QMainWindow( parent ),
     data_model( nullptr ),
     settings_file( QApplication::applicationDirPath() + SET_FILE ),
     working_cp_path( "" ),
     expanded( false )
{
   ui.setupUi(this);

   // this loads also working_cp_path
   load_settings( );

   ui.externals_TV->show();
}

Main_Window::~Main_Window( )
{
   save_settings( );
   del_external_model( );
}


void Main_Window::del_external_model( void )
{
   ui.externals_TV->setModel( nullptr );

   if( data_model != nullptr )
   {
      delete data_model;
      data_model = nullptr;
   }
}

void Main_Window::load_settings( void )
{
   QSettings settings( settings_file, QSettings::NativeFormat);
   working_cp_path = settings.value( SET_CP_PATH, "" ).toString();
   ui.working_copy_path_LE->setText( working_cp_path );
   update_tree();
}

void Main_Window::save_column_settings( void )
{
   QSettings settings( settings_file, QSettings::NativeFormat);
   settings.setValue( SET_COLUMN_W1, ui.externals_TV->columnWidth(0) );
   settings.setValue( SET_COLUMN_W2, ui.externals_TV->columnWidth(1) );
   settings.setValue( SET_COLUMN_W3, ui.externals_TV->columnWidth(2) );
   settings.setValue( SET_COLUMN_W4, ui.externals_TV->columnWidth(3) );
}

void Main_Window::load_column_settings( void )
{
   QSettings settings( settings_file, QSettings::NativeFormat);
   ui.externals_TV->setColumnWidth( 0, settings.value( SET_COLUMN_W1, 100 ).toInt() );
   ui.externals_TV->setColumnWidth( 1, settings.value( SET_COLUMN_W2, 100 ).toInt() );
   ui.externals_TV->setColumnWidth( 2, settings.value( SET_COLUMN_W3, 100 ).toInt() );
   ui.externals_TV->setColumnWidth( 3, settings.value( SET_COLUMN_W4, 100 ).toInt() );
}

void Main_Window::save_settings( void )
{
   QSettings settings( settings_file, QSettings::NativeFormat);
   settings.setValue( SET_CP_PATH, working_cp_path );

   // we only save the column settings, if we have a valid
   // model loaded
   if( data_model != nullptr )
      save_column_settings();
}



void Main_Window::update_tree( void )
{
   QProcess process;

   del_external_model();

   // ensure, that we are having a copy of a SVN repo
   // by calling svn info <path>
   process.start( SVN_CMD, QStringList() << SVN_INFO << working_cp_path );
   if( process.waitForFinished( SYS_PROCESS_TIMEOUT ) && 
       process.exitCode() == 0 ) // wait 3 seconds
   {
      data_model = new Data_Model( working_cp_path );
      ui.externals_TV->setModel( data_model );
      load_column_settings();
   }

}

void Main_Window::on_working_copy_browse_PB_clicked( void )
{

   QString dir = QFileDialog::getExistingDirectory(this, 
         tr("Open Directory"),
         ui.working_copy_path_LE->text(),
         QFileDialog::ShowDirsOnly
         | QFileDialog::DontResolveSymlinks);
   if( dir.size() > 0 )
   {
      working_cp_path = dir;
      ui.working_copy_path_LE->setText( dir );
      update_tree();
   }
}


void Main_Window::on_expand_PB_clicked( void )
{
   if( expanded == true )
   {
      expanded = false;
      ui.externals_TV->collapseAll(); 
      ui.expand_PB->setText( tr("Expand all") );
   }
   else
   {
      expanded = true;
      ui.externals_TV->expandAll(); 
      ui.expand_PB->setText( tr("Collapse all") );
   }
}


Main_Window::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Main_Window (" << reinterpret_cast< void* >( this ) << "): "
       << "setting-file=" << settings_file;
   return s;
}

}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3
