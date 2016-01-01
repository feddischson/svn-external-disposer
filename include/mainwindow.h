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
#ifndef _SVN_EXTERNALS_DISPOSER_MAINWINDOW_H 
#define _SVN_EXTERNALS_DISPOSER_MAINWINDOW_H
#include <iostream>
#include <QWidget>
#include <QMap>


#include "ui_MainWindow.h"
#include "data_model.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief The mainwindow class
class Main_Window : public QMainWindow
{

   Q_OBJECT
public:

   /// @author feddischson
   /// @brief Ctor: not implemented!
   explicit Main_Window( QWidget *parent = nullptr );


   /// @author feddischson
   /// @brief  Copy ctor: not implemented!
   Main_Window(const Main_Window & a_window) = delete;


   /// @author feddischson
   /// @brief  Assignment operator: not implemented!
   Main_Window& operator= (const Main_Window & a_window) = delete;


   /// @author feddischson
   /// @brief  Move constructor: not implemented!
   Main_Window( Main_Window && rhs ) = delete;


   /// @author feddischson
   /// @brief  Move assignment operator: not implemented!
   Main_Window& operator=( Main_Window && rhs ) = delete;


   /// @author feddischson
   /// @brief Dtor, does only saving the settings.
   ~Main_Window();

   /// @author feddischson
   /// @brief QString operator, to print data to qDebug()
   virtual operator QString();

private:


   // the external model reflecting our tree of data
   Data_Model *data_model;


   /// @author feddischson
   /// @brief
   Ui::Main_Window ui;

   /// @author feddischson
   /// @brief
   QString working_cp_path;

   /// @author feddischson
   /// @brief
   void load_settings( void );

   /// @author feddischson
   /// @brief
   void load_column_settings( void );


   /// @author feddischson
   /// @brief
   void save_settings( void );

   /// @author feddischson
   /// @brief
   void save_column_settings( void );

   /// @author feddischson
   /// @brief
   bool expanded;


private slots:

   void del_external_model( void );


   /// @author feddischson
   /// @brief  Creates a new Data_Model
   ///         and sets this instance to ui.working_copy_path_LE
   void update_tree( void );

   /// @author feddischson
   /// @brief
   void on_working_copy_browse_PB_clicked( void );

   /// @author feddischson
   /// @brief
   void on_save_PB_clicked( void );

   /// @author feddischson
   /// @brief
   void on_expand_PB_clicked( void );


}; // class Main_Window

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_MAINWINDOW_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

