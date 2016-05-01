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
#ifndef _SVN_EXTERNALS_DISPOSER_BROWSER_DIALOG_H_ 
#define _SVN_EXTERNALS_DISPOSER_BROWSER_DIALOG_H_
#include <QDialog>
#include <QTextStream>

#include "ui_BrowserDialog.h"
#include "tree_view.h"
#include "table_view.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @brief  File Browser Dialog to browse SVN repositories.
///
/// @details 
///         The dialog is splitted into two parts, a tree part on the left
///         and a table part on the right. Both widgets are using the same
///         Browser_Model (an AbstractItemModel) to show the data once as
///         tree and once as table. The tree is mainly to have the navigation
///         overview and the table provides more details.
///         Furthermore, this dialog is able to open a revision browser to 
///         select a specific revision.
///
/// @author feddischson
class Browser_Dialog : public QDialog
{

   Q_OBJECT
public:

   /// @brief Sets the url  and revision, initializes the UI.
   ///
   /// @param url       The URL to the repository (root or sub-path)
   /// @param revision  The desired revision, can also be 'HEAD'.
   ///
   ///
   explicit Browser_Dialog( const QString & url,
                            const QString & revision,
                            QWidget *parent = nullptr );

   /// @brief Initializes the dialog and loads the data.
   /// @returns true If the initialization was successful
   /// @returns false If the initialization was not successful
   bool load( void );

   /// @brief  Copy ctor: not implemented!
   Browser_Dialog(const Browser_Dialog & a_template_) = delete;

   /// @brief  Assignment operator: not implemented!
   Browser_Dialog& operator= (const Browser_Dialog & a_template_) = delete;

   /// @brief  Move constructor: not implemented!
   Browser_Dialog( Browser_Dialog && rhs ) = delete;

   /// @brief  Move assignment operator: not implemented!
   Browser_Dialog& operator=( Browser_Dialog && rhs ) = delete;

   /// @brief Default dtor
   ~Browser_Dialog() = default;

   /// @brief Returns the selected URL (from the url_LE).
   QString get_url( void );

   /// @brief Returns the selected Revision (from the revision_LE).
   QString get_revision( void );

protected:

   /// @brief  Updates the table and resizes the width of each column.
   virtual void resizeEvent( QResizeEvent * );

private:

   /// @brief The internal UI instance (see forms/BrowserDialog.ui)
   Ui::BrowserDialog ui;

   /// @brief 
   QString url;

   /// @brief Pointer to the internal tree-view instance
   Tree_View * repository_TRV;

   /// @brief Pointer to the internal table-view instance
   Table_View * repository_TBV;

private slots:

   /// @brief Gets called if the selection in the tree view changes.
   void selection_changed( const QItemSelection & selection );

   /// @brief Gets called if the selection in the table view changes
   void table_selection_changed( const QItemSelection & selection );


   /// @brief Is called after the revision editing is finished. Calls 
   ///        further load().
   void on_revision_LE_editingFinished();


   /// @brief Is called after the url-editing is finished. Calls further load().
   void on_url_LE_editingFinished();

   /// @brief Is called after clicking the revision-browse button and 
   ///        opens the revision browser.
   void on_browse_PB_clicked();

}; // class Browser_Dialog

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_BROWSER_DIALOG_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

