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
#ifndef _SVN_EXTERNALS_DISPOSER_LOGIN_DIALOG_H 
#define _SVN_EXTERNALS_DISPOSER_LOGIN_DIALOG_H
#include <QDialog>
#include <QTextStream>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>


namespace SVN_EXTERNALS_DISPOSER
{


/// @brief A login-dialog, which asks for a user-name and password.
///
/// @details
///         It uses a QComboBox for selecting / entering user-names.
///         The user-names are stored via QSettings, the passwords not.
///       
/// @author feddischson
class Login_Dialog : public QDialog
{

   Q_OBJECT
public:

   /// @brief Ctor: not implemented!
   explicit Login_Dialog( QWidget *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Login_Dialog(const Login_Dialog & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Login_Dialog& operator= (const Login_Dialog & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Login_Dialog( Login_Dialog && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Login_Dialog& operator=( Login_Dialog && rhs ) = delete;


   /// @brief Standard dtor
   ~Login_Dialog() = default;

   /// @brief Returns the user-name.
   QString username( void );

   /// @brief Returns the password.
   QString password( void );

private:

   /// @brief  The username cobobox.
   QComboBox        * username_CB;

   /// @brief The password lineedit.
   QLineEdit        * password_LE;

   /// @brief The Username label.
   QLabel           * username_L;

   /// @brief The password label.
   QLabel           * password_L;

   /// @brief The button-box.
   QDialogButtonBox * buttons_BB;

   /// @brief Initialization function for the GUI elements
   void setup_gui( void );

private slots:

   /// @brief Slot which is called after clicking authenticate.
   void authenticate( void );


}; // class Login_Dialog

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_LOGIN_DIALOG_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

