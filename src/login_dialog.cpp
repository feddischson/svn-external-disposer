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
#include <QGridLayout>
#include <QSettings>
#include <QDebug>

#include "login_dialog.h"
#include "const.h"
namespace SVN_EXTERNALS_DISPOSER
{

Login_Dialog:: Login_Dialog( QWidget *parent ) 
   : QDialog( parent )
{
   setup_gui();
}


void Login_Dialog::setup_gui( void )
{
   QGridLayout * layout_GL = new QGridLayout( this );
   QSettings settings;

   // the user-name combo-box
   username_CB = new QComboBox( this );
   username_CB->setEditable( true );

   int size = settings.beginReadArray( SET_USERNAMES );
   for( int i=0; i < size; i++ )
   {
      settings.setArrayIndex( i );
      username_CB->addItem( settings.value( SET_USERNAME ).toString( ) );
   }
   settings.endArray();

   if( size > 0 )
   {
      int last_name = settings.value( SET_LASTNAME, 0 ).toInt();
      username_CB->setCurrentIndex( last_name );
   }


   // the password line edit
   password_LE = new QLineEdit( this );
   password_LE->setEchoMode( QLineEdit::Password );

   // initialize the labels
   username_L = new QLabel( this );
   password_L = new QLabel( this );
   username_L->setText( tr( "Username" ) );
   username_L->setBuddy( username_CB );
   password_L->setText( tr( "Password" ) );
   password_L->setBuddy( password_LE );

   // initialize buttons
   buttons_BB = new QDialogButtonBox( this );
   buttons_BB->addButton( QDialogButtonBox::Ok );
   buttons_BB->addButton( QDialogButtonBox::Cancel );
   buttons_BB->button( QDialogButtonBox::Ok )->setText( tr("Authenticate") );
   buttons_BB->button( QDialogButtonBox::Cancel )->setText( tr("Abort") );

   connect( buttons_BB->button( QDialogButtonBox::Cancel ),
      SIGNAL ( clicked() ),
      this,
      SLOT ( close() )
   );

   connect( buttons_BB->button( QDialogButtonBox::Ok ),
      SIGNAL ( clicked() ),
      this,
      SLOT ( authenticate() ) 
   );

   // place components into the dialog
   layout_GL->addWidget( username_L, 0, 0 );
   layout_GL->addWidget( username_CB, 0, 1 );
   layout_GL->addWidget( password_L, 1, 0 );
   layout_GL->addWidget( password_LE, 1, 1 );
   layout_GL->addWidget( buttons_BB, 2, 0, 1, 2 );

   setLayout( layout_GL );
}

QString Login_Dialog::username( void )
{
   return username_CB->currentText();
}

QString Login_Dialog::password( void )
{
   return password_LE->text();
}

void Login_Dialog::authenticate( void )
{
   QSettings settings;
   QStringList usernames;
   QString name = username();


   // get the saved user-names
   int size = settings.beginReadArray( SET_USERNAMES );
   for( int i=0; i < size; i++ )
   {
      settings.setArrayIndex( i );
      usernames << settings.value( SET_USERNAME ).toString( );
   }
   settings.endArray();

   // extend the list if necessary and save it
   if( !usernames.contains( name ) )
   {
      usernames << name;
      settings.beginWriteArray( SET_USERNAMES );
      for( int i=0; i < size+1; i++ )
      {  
         settings.setArrayIndex( i );
         settings.setValue( SET_USERNAME, usernames[i] );
      }
      settings.endArray();
      settings.setValue( SET_LASTNAME, size+1-1 );
   }
   else
      settings.setValue( SET_LASTNAME, username_CB->currentIndex() );

   accept();
}

}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

