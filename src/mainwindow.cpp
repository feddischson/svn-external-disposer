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
     working_cp_path( "" ),
     expanded( false )
{
   ui.setupUi(this);


   externals_TV = new Tree_View( this );
   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget( externals_TV );
   ui.externals_W->setLayout(layout);
   setup_actions( );

   // this loads also working_cp_path
   load_settings( );

   externals_TV->show();

   setWindowTitle( APP_NAME + " v" + APP_VERSION );
}

Main_Window::~Main_Window( )
{
   save_settings( );
   del_external_model( );
}


void Main_Window::del_external_model( void )
{
   externals_TV->setModel( nullptr );

   if( data_model != nullptr )
   {
      delete data_model;
      data_model = nullptr;
   }
}

/// @details
/// The function does the following:
///   - Load the working copy path setting
///   - Call update_tree(), which initializes the model
//      and calls load_column_settings().
void Main_Window::load_settings( void )
{
   QSettings settings;
   working_cp_path = settings.value( SET_CP_PATH, "" ).toString();
   ui.working_copy_path_LE->setText( working_cp_path );
   update_tree();
}


void Main_Window::save_column_settings( void )
{
   QSettings settings;
   settings.setValue( SET_COLUMN_W1, externals_TV->columnWidth(0) );
   settings.setValue( SET_COLUMN_W2, externals_TV->columnWidth(1) );
   settings.setValue( SET_COLUMN_W3, externals_TV->columnWidth(2) );
   settings.setValue( SET_COLUMN_W4, externals_TV->columnWidth(3) );
}

void Main_Window::load_column_settings( void )
{
   QSettings settings;
   externals_TV->setColumnWidth( 0, settings.value( SET_COLUMN_W1, 100 ).toInt() );
   externals_TV->setColumnWidth( 1, settings.value( SET_COLUMN_W2, 100 ).toInt() );
   externals_TV->setColumnWidth( 2, settings.value( SET_COLUMN_W3, 100 ).toInt() );
   externals_TV->setColumnWidth( 3, settings.value( SET_COLUMN_W4, 100 ).toInt() );
}

/// @details
/// This function saves the path and calls save_column_settings().
void Main_Window::save_settings( void )
{
   QSettings settings;
   settings.setValue( SET_CP_PATH, working_cp_path );

   // we only save the column settings, if we have a valid
   // model loaded
   if( data_model != nullptr )
      save_column_settings();
}


void Main_Window::setup_actions( void )
{
   quit_action    = new QAction(tr( "&Quit" ),                    this);
   open_action    = new QAction(tr( "&Open SVN Working Copy" ),   this);
   reload_action  = new QAction(tr( "&Reload"),                   this);
   discard_action = new QAction(tr( "&Discard"),                  this);
   save_action    = new QAction(tr( "&Save"),                     this);

   connect( quit_action,      SIGNAL(triggered()), qApp, SLOT(quit()));
   connect( open_action,      SIGNAL(triggered()), this, SLOT(on_working_copy_browse_PB_clicked()));
   connect( reload_action,    SIGNAL(triggered()), this, SLOT(on_reload_PB_clicked()));
   connect( discard_action,   SIGNAL(triggered()), this, SLOT(on_discard_PB_clicked()));
   connect( save_action,      SIGNAL(triggered()), this, SLOT(on_save_PB_clicked()));

   ui.file_M->addAction( open_action );
   ui.file_M->addAction( reload_action  );
   ui.file_M->addAction( discard_action );
   ui.file_M->addAction( save_action );
   ui.file_M->addAction( quit_action );
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
      data_model = new Data_Model( );
      data_model->setRootPath( working_cp_path );
      externals_TV->setModel( data_model );
      externals_TV->setRootIndex( data_model->index( working_cp_path ) );

      undo_action = data_model->create_undo_action( this, tr("&Undo" ) );
      undo_action->setShortcuts(QKeySequence::Undo);
      redo_action = data_model->create_redo_action( this, tr("&Redo" ) );
      redo_action->setShortcuts(QKeySequence::Redo);

      ui.edit_M->clear();
      ui.edit_M->addAction( undo_action    );
      ui.edit_M->addAction( redo_action    );
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
      externals_TV->collapseAll(); 
      ui.expand_PB->setText( tr("Expand all") );
   }
   else
   {
      expanded = true;
      externals_TV->expandAll(); 
      ui.expand_PB->setText( tr("Collapse all") );
   }
}


void Main_Window::on_reload_PB_clicked( void )
{
   save_settings();
   update_tree();
}


void Main_Window::on_save_PB_clicked( void )
{
   if( data_model != nullptr )
      data_model->save_externals( );
   save_settings();
   update_tree();
}


void Main_Window::on_discard_PB_clicked( void )
{
   if( data_model != nullptr )
      data_model->restore( );
   save_settings();
}


Main_Window::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Main_Window (" << reinterpret_cast< void* >( this ) << "): ";
   return s;
}

}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

