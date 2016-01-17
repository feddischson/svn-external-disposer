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
#ifndef _SVN_EXTERNALS_DISPOSER_EXTERNALS_DIALOG_H 
#define _SVN_EXTERNALS_DISPOSER_EXTERNALS_DIALOG_H
#include <QDialog>
#include <QTextStream>

#include "ui_ExternalsDialog.h"
#include "data_model.h"
#include "external.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @brief Externals editing dialog
///
/// @details
///   This dialoge contains a QTableWidget with four columns:
///      1. The target path
///      2. URL (from where the external data is loaded)
///      3. Peg-Revision
///      4. Operative Revision
///    Furthermore, there is a label whcih shows, where the svn:externals 
///    property is stored.
///
/// @author feddischson
class Externals_Dialog : public QDialog
{

   Q_OBJECT
public:

   /// @brief Initializes the labels, the table, a context-menu and actions.
   explicit Externals_Dialog( 
         const QString & path,
         Data_Model * data_model,
         QWidget    * parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Externals_Dialog(const Externals_Dialog & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Externals_Dialog& operator= (const Externals_Dialog & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Externals_Dialog( Externals_Dialog && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Externals_Dialog& operator=( Externals_Dialog && rhs ) = delete;


   /// @brief Standard dtor
   ~Externals_Dialog() = default;


   /// @brief Initializes the table.
   void setup_table( void );

private slots:

   // @brief Is called if a cell changes (not during initialization via `setup_table`.
   void cell_changed( int row, int column );

   // @brief Opens the custpom context menu and is connected to the QTableWidget.
   void open_context_menu(const QPoint &point);

   // @brief Handles the browse for revision action.
   void browse_rev( void );

private:

   /// @brief 
   QTableWidgetItem * create_item( const QString text, bool modified );


   /// @brief UI instance, created from forms/ExternalsDialog.ui.
   Ui::ExternalsDialog ui;

   /// @brief The external target list
   QList< QString > content;

   /// @brief 
   QString path;

   // @brief Pointer to the data-model, which holds the externals.
   Data_Model * data_model;

   /// @brief Pointer to undo action instance (created by Data_Model).
   QAction * undo_action;

   /// @brief Pointer to redo action instance (created by Data_Model).
   QAction * redo_action;

   /// @brief number of columns in the QTreeWidget 
   static const quint32 N_COLUMNS = 4;

   /// @brief A menu used for browse revisions, provided by the main-window.
   QMenu      * revision_menu;

   /// @brief The last row, where the context of the tablew-widget is opened.
   quint32 last_context_row;

   /// @brief The last column, where the context of the tablew-widget is opened.
   quint32 last_context_col;

}; // class Externals_Dialog

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_EXTERNALS_DIALOG_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

