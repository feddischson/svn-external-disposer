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

#include "browser_dialog.h"
#include "browser_model.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{

Browser_Dialog::Browser_Dialog( const QString & path, 
                                QWidget * parent )
   : QDialog( parent ),
     path( path )
{
   QVBoxLayout * layout;
   ui.setupUi(this);

   repository_TRV = new Tree_View( this );
   layout = new QVBoxLayout( this );
   layout->addWidget( repository_TRV );
   ui.repository_WL->setLayout(layout);



   repository_TBV = new Table_View( this );
   layout = new QVBoxLayout( this );
   layout->addWidget( repository_TBV );
   ui.repository_WR->setLayout(layout);


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

   Browser_Model * m = new Browser_Model( path, this );

   QString root_url = m->root_url();
   QString url      = m->url();

   ui.repository_L->setText( root_url );
   ui.path_LE->setText( url );

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

QString Browser_Dialog::get_url( void )
{
   return ui.path_LE->text();
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

