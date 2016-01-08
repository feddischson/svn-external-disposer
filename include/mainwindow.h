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
#include <QDebug>

#include "tree_view.h"
#include "ui_MainWindow.h"
#include "data_model.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @brief The mainwindow class
///
/// @author feddischson
class Main_Window : public QMainWindow
{

   Q_OBJECT
public:

   /// @brief Ctor: not implemented!
   explicit Main_Window( QWidget *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Main_Window(const Main_Window & a_window) = delete;


   /// @brief  Assignment operator: not implemented!
   Main_Window& operator= (const Main_Window & a_window) = delete;


   /// @brief  Move constructor: not implemented!
   Main_Window( Main_Window && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Main_Window& operator=( Main_Window && rhs ) = delete;


   /// @brief Dtor, does only saving the settings.
   ~Main_Window();

   /// @brief QString operator, to print data to qDebug()
   virtual operator QString();

private:


   // the external model reflecting our tree of data.
   Data_Model *data_model;


   /// @brief UI instance, created from forms/MainWindow.ui.
   Ui::Main_Window ui;

   /// @brief The current working copy path.
   QString working_cp_path;

   /// @brief Loads the settings.
   void load_settings( void );

   /// @brief Loads the column settings (the width of four columns).
   void load_column_settings( void );

   /// @brief Saves the settings (including the column settings).
   void save_settings( void );

   /// @brief Saves the column settings.
   void save_column_settings( void );

   /// @brief Initializes most of the actions (except the edit settings).
   void setup_actions( void );

   /// @brief Expanded state.
   bool expanded;

   /// @brief Pointer to undo action instance (created by Data_Model).
   QAction * undo_action;

   /// @brief Pointer to redo action instance (created by Data_Model).
   QAction * redo_action;

   /// @brief Pointer to reload action instance.
   QAction * reload_action;

   /// @brief Pointer to discrad action instance.
   QAction * discard_action;

   /// @brief Pointer to quit action instance.
   QAction * quit_action;

   /// @brief Pointer to open action instance.
   QAction * open_action;

   /// @brief Pointer to save action instance.
   QAction * save_action;

   /// @brief Pointer to the tree-view instance.
   Tree_View * externals_TV;

private slots:

   /// @brief De-initializes externals_TV and delets it.
   void del_external_model( void );


   /// @brief  Creates a new Data_Model
   ///         and sets this instance to ui.working_copy_path_LE
   void update_tree( void );

   /// @brief  Handler slot for the working_copy_browse_PB button.
   void on_working_copy_browse_PB_clicked( void );

   /// @brief  Handler slot for the save_PB button.
   void on_save_PB_clicked( void );

   /// @brief Handler slot for the expand_PB button.
   void on_expand_PB_clicked( void );

   /// @brief Handler slot for the reload_PB button.
   void on_reload_PB_clicked( void );

   /// @brief Handler slot for the discard_PB button.
   void on_discard_PB_clicked( void );

}; // class Main_Window

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_MAINWINDOW_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

