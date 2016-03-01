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
#ifndef _SVN_EXTERNALS_DISPOSER_TABLE_VIEW_H_
#define _SVN_EXTERNALS_DISPOSER_TABLE_VIEW_H_
#include <QTableView>
#include <QTextStream>


namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief  Class to extend QTableView
class Table_View : public QTableView
{

   Q_OBJECT
public:

   /// @brief Ctor: not implemented!
   explicit Table_View( QWidget *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Table_View(const Table_View & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Table_View& operator= (const Table_View & a_tv ) = delete;


   /// @brief  Move constructor: not implemented!
   Table_View( Table_View && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Table_View& operator=( Table_View && rhs ) = delete;


   /// @brief Standard dtor
   ~Table_View() = default;


private:

protected:

   void selectionChanged( const QItemSelection &selected,
                          const QItemSelection &deselected);

signals:

   void selection_changed( const QItemSelection & selected );

}; // class Table_View

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TABLE_VIEW_H_

// vim: filetype=cpp et ts=3 sw=3 sts=3

