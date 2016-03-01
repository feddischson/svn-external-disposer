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
#ifndef _SVN_EXTERNALS_DISPOSER_BROWSER_ITEM_H_ 
#define _SVN_EXTERNALS_DISPOSER_BROWSER_ITEM_H_
#include <QObject>
#include <QTextStream>

namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Item used within Browser_Model (which is an AbstractItemModel).
/// @details
///      Stores all necessary data of one file/folder entry and holds
///      pointers to sub-entries.
class Browser_Item : public QObject
{

   Q_OBJECT
public:

   /// @brief Initializes the parent_item, url_path and the item_data.
   explicit Browser_Item( 
         const QString & url_path,
         const QString & revision,
         const QList< QVariant> & content, 
         Browser_Item *parent = nullptr );

   /// @brief  Copy ctor: not implemented!
   Browser_Item(const Browser_Item & a_template_) = delete;

   /// @brief  Assignment operator: not implemented!
   Browser_Item& operator= (const Browser_Item & a_template_) = delete;

   /// @brief  Move constructor: not implemented!
   Browser_Item( Browser_Item && rhs ) = delete;

   /// @brief  Move assignment operator: not implemented!
   Browser_Item& operator=( Browser_Item && rhs ) = delete;

   /// @brief Standard dtor
   ~Browser_Item();

   /// @brief QSTring operator, to print data to qDebug()
   virtual operator QString();

   /// @brief 
   void load_children( void );

   /// @brief Returns a child for a given row.
   Browser_Item * child( int row );

   /// @brief Returns the number of children.
   int child_count( void );

   /// @brief Returns the row of this item (via parent).
   int row( void ) const;

   /// @brief Returns the number of columns.
   int column_count() const;

   /// @brief Returns an entry for a given column.
   QVariant data( int col ) const;

   /// @brief Returns the parent item.
   Browser_Item * parent( void );

   /// @brief Returns the URL.
   QString url( void );

private:

   /// @brief Holds all child items.
   QList< Browser_Item* > child_items;

   /// @brief The content of this item.
   QList< QVariant > item_data;

   /// @broef Points to the parent item.
   Browser_Item * parent_item;

   /// @brief
   QString url_path;

   /// @brief Defines if the children are loaded or not
   bool children_loaded;

   /// @brief The revision
   QString revision;
}; // class Browser_Item

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_BROWSER_ITEM_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

