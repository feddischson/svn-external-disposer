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
#ifndef _SVN_EXTERNALS_DISPOSER_TREE_VIEW_H 
#define _SVN_EXTERNALS_DISPOSER_TREE_VIEW_H
#include <QTreeView>
#include <QTextStream>


namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief  Class to extend QTreeView
class Tree_View : public QTreeView
{

   Q_OBJECT
public:

   /// @brief Ctor: not implemented!
   explicit Tree_View( QWidget *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Tree_View(const Tree_View & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Tree_View& operator= (const Tree_View & a_tv ) = delete;


   /// @brief  Move constructor: not implemented!
   Tree_View( Tree_View && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Tree_View& operator=( Tree_View && rhs ) = delete;


   /// @brief Standard dtor
   ~Tree_View() = default;


   /// @brief QSTring operator, to print data to qDebug()
   virtual operator QString();

private:


}; // class Tree_View

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TREE_VIEW_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

