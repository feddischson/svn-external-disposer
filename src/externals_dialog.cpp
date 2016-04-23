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
#include <QMenu>
#include <QMessageBox>

#include "const.h"
#include "externals_dialog.h"
#include "browser_dialog.h"
#include "log_dialog.h"

namespace SVN_EXTERNALS_DISPOSER
{

Externals_Dialog::Externals_Dialog(
      const QString & path,
      Data_Model * data_model,
      QWidget *parent ) :
   QDialog( parent ), 
   path( path ), 
   data_model( data_model )
{
   ui.setupUi(this);
   setup_table();

   QHeaderView * view = ui.externals_TW->horizontalHeader();
   view->setSectionResizeMode(QHeaderView::Stretch);

   ui.path_L->setText( path );

   ui.externals_TW->setContextMenuPolicy( Qt::CustomContextMenu );
   connect( ui.externals_TW, SIGNAL( customContextMenuRequested( const QPoint & ) ), 
         this, SLOT(open_context_menu( const QPoint & ) ) );

   QAction * browse_rev_action  = new QAction(tr( "&Browse"), this);
   revision_menu                = new QMenu( ui.externals_TW );
   revision_menu->addAction( browse_rev_action );

   connect( browse_rev_action, SIGNAL( triggered( ) ), this, SLOT( browse_rev( ) ) );
   ui.externals_TW->selectRow( 0 );

}


void Externals_Dialog::setup_table( void )
{
   QStringList headers;

   // disconnect the cell_change slot first,
   // the slot is connected again after initialization
   disconnect( ui.externals_TW, SIGNAL( cellChanged(int,int) ), 0, 0 );
   ui.externals_TW->clear();

   // setup headers
   ui.externals_TW->setColumnCount( 4 );
   ui.externals_TW->verticalHeader ()->hide();
   ui.externals_TW->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui.externals_TW->setSelectionMode(QAbstractItemView::SingleSelection);
   headers << GUI_HEAD_TARGET 
           << GUI_HEAD_EXTERNAL
           << GUI_HEAD_PEG
           << GUI_HEAD_OPERATIVE;
   ui.externals_TW->setHorizontalHeaderLabels( headers );


   // setup content
   // content is a list of all target paths
   update_content();

   // connect the cell_change slot again
   connect( ui.externals_TW, SIGNAL( cellChanged(int,int) ), this, SLOT( cell_changed(int,int) ) );

}


void Externals_Dialog::update_content( void )
{
   int i = 0;
   content = data_model->get_externals_targets( path ); 
   ui.externals_TW->setRowCount( content.size() );
   foreach( auto target_path, content )
   {
      bool modified = data_model->is_external_modified( target_path );
      T_SP_External e = data_model->get_external( target_path );

      ui.externals_TW->setItem( i, 0, create_item( e->local_path.toString()        , modified ) );
      ui.externals_TW->setItem( i, 1, create_item( e->url.toString()               , modified ) );
      ui.externals_TW->setItem( i, 2, create_item( e->peg_revision.toString()      , modified ) );
      ui.externals_TW->setItem( i, 3, create_item( e->operative_revision.toString(), modified ) );
      i++;
   }
}


QTableWidgetItem * Externals_Dialog::create_item( const QString text, bool modified )
{
   QTableWidgetItem *item = new QTableWidgetItem( text );
   if( modified )
      item->setBackground( COL_MODIFIED );
   return item;
}

void Externals_Dialog::cell_changed( int row, int column )
{
   QString key = content[row];
   data_model->change_external( key,  QVariant( ui.externals_TW->item( row, column )->text() ), column );

   for( quint32 i=0; i < N_COLUMNS; i++ )
   {
      if( data_model->is_external_modified( key ) )
         ui.externals_TW->item( row, i )->setBackground( COL_MODIFIED );
      else
         ui.externals_TW->item( row, i )->setBackground( COL_NOT_MODIFIED );

   }
}

void Externals_Dialog::open_context_menu(const QPoint & p)
{
   QModelIndex index = ui.externals_TW->indexAt(p);

   if( !index.isValid() )
      return;

   last_context_row = ui.externals_TW->itemAt( p )->row();
   last_context_col = ui.externals_TW->itemAt( p )->column();

   if( last_context_col == 1 ||
       last_context_col == 2 || 
       last_context_col == 3 )
   {
      last_context_index = index;
      revision_menu->exec( ui.externals_TW->mapToGlobal( p ) );
   }
}


void Externals_Dialog::browse_rev( void )
{
   QString path = content[ last_context_row ];

   if( last_context_index.column() == 1 )
   {
      QString revision = "HEAD";
      int     revision_from = 0;

      auto old_url = ui.externals_TW->item( last_context_row, 1 )->text();
      auto tmp_peg = ui.externals_TW->item( last_context_row, 2 )->text();
      auto tmp_opr = ui.externals_TW->item( last_context_row, 3 )->text();
      if( tmp_peg.size() > 0 )
      {
         revision      = tmp_peg;
         revision_from = 2;
      }
      else if( tmp_opr.size() > 0 )
      {
         revision      = tmp_opr;
         revision_from = 3;
      }

      Browser_Dialog *d = new Browser_Dialog( path, old_url, revision );

      if( d->load() )
      {
         d->exec();
         if( d->result() )
         {
            QString rev      = d->get_revision();
            QString new_url = d->get_url();

            if( revision_from == 3 )
               ui.externals_TW->setItem( last_context_row, 3, create_item( rev, true ) );
            else if( revision_from == 2 )
               ui.externals_TW->setItem( last_context_row, 2, create_item( rev, true ) );
            else if( revision_from == 0 && rev.toLower() != "head" )
               ui.externals_TW->setItem( last_context_row, 2, create_item( rev, true ) );

            if( new_url != old_url )
            {
               ui.externals_TW->setItem( last_context_row, 1, create_item( new_url, true ) );
               update_content();
            }
         }
      }
      else
      {
         QMessageBox * m = new QMessageBox( );
         m->setText( tr("Failed to load the SVN repository browser" ) );
         m->setDetailedText( "Path: " + path );
         m->exec();

      }



   }
   else if( last_context_index.column() == 2 || last_context_index.column() == 3 )
   {

      Log_Dialog *d = new Log_Dialog( path, this );
      if( d->load() )
      {
         d->exec();
         if( d->result() )
         {
            // data_model->setData( last_context_row, d->get_revision(), Qt::EditRole  );
            QString rev = d->get_revision().toString();

            ui.externals_TW->setItem( last_context_row, last_context_col, create_item( rev, true ) );
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



}




}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

