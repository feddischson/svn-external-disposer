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
#include <QDebug>
#include <QMessageBox>


#include "log_dialog.h"
#include "browser_dialog.h"
#include "browser_model.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{

Browser_Dialog::Browser_Dialog( 
      const QString & path,
      const QString & url,
      const QString & revision,
      QWidget * parent )
   : QDialog( parent ),
     path( path ),
     url( url )
{
   QVBoxLayout * layout;
   ui.setupUi(this);

   repository_TRV = new Tree_View( this );
   layout = new QVBoxLayout( );
   layout->addWidget( repository_TRV );
   ui.repository_WL->setLayout(layout);



   repository_TBV = new Table_View( this );
   layout = new QVBoxLayout( );
   layout->addWidget( repository_TBV );
   ui.repository_WR->setLayout(layout);

   ui.revision_LE->setText( revision );

   repository_TBV->setSelectionBehavior( QAbstractItemView::SelectRows );
   repository_TBV->setSelectionMode( QAbstractItemView::SingleSelection );

   connect( 
         repository_TBV, 
         SIGNAL( selection_changed( const QItemSelection & ) ),
         this,
         SLOT( table_selection_changed( const QItemSelection & ) ) ) ;

   connect( repository_TRV, 
         SIGNAL( selection_changed( const QItemSelection & ) ), 
         this, 
         SLOT( selection_changed( const QItemSelection & ) ) );
}

bool Browser_Dialog::load( void )
{

   Browser_Model * m = new Browser_Model( path, url, ui.revision_LE->text(), this );

   QString root_url = m->get_root_url();
   QString url      = m->get_url();

   ui.repository_L->setText( root_url );
   if( url.size() > 0 )
      ui.path_LE->setText( url );
   else
      ui.path_LE->setText( path );

   repository_TRV->setModel( m );
   repository_TBV->setModel( m );

   auto selected_index = m->index( url );
   repository_TBV->setRootIndex( selected_index );
   for( int i=1; i < BROWSER_N_COL; i++ )
      repository_TRV->setColumnHidden( i, true );
   repository_TRV->setHeaderHidden( true );

   while( selected_index.isValid() )
   {
      repository_TRV->expand( selected_index );
      selected_index = selected_index.parent();
   }
   return true;
}


void Browser_Dialog::selection_changed( const QItemSelection & selected )
{
   if( selected.indexes().size() > 0 )
   {
      Browser_Item * item = static_cast< Browser_Item* >(
            selected.indexes()[0].internalPointer());
      repository_TBV->setRootIndex( selected.indexes()[0] );
      ui.path_LE->setText( item->url() );
      repository_TBV->clearSelection();
   }
}

void Browser_Dialog::table_selection_changed( const QItemSelection & selected )
{
   if( selected.indexes().size() > 0 )
   {
      Browser_Item * item = static_cast< Browser_Item* >(
            selected.indexes()[0].internalPointer());
      ui.path_LE->setText( item->url() );
      repository_TRV->clearSelection();
   }
}


void Browser_Dialog::on_revision_LE_editingFinished( )
{
   load();
}


void Browser_Dialog::on_path_LE_editingFinished()
{
   path = ui.path_LE->text();
   load();
}

void Browser_Dialog::on_browse_PB_clicked()
{
   Log_Dialog *d = new Log_Dialog( path, this );
   if( d->load() )
   {
      d->select_revision( ui.revision_LE->text() );
      d->exec();
      if( d->result() )
      {
         ui.revision_LE->setText( d->get_revision().toString() );
         load();
      }
   }
   else
   {
      QMessageBox * m = new QMessageBox( );
      m->setText( tr("Failed to load the SVN revision log" ) );
      m->setDetailedText( "Path: " + path );
      m->exec();
   }

}


QString Browser_Dialog::get_url( void )
{
   return ui.path_LE->text();
}

QString Browser_Dialog::get_revision( void )
{
   return ui.revision_LE->text();
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

