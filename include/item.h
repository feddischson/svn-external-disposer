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
#ifndef _SVN_EXTERNALS_DISPOSER_EXTERNAL_ITEM_H_ 
#define _SVN_EXTERNALS_DISPOSER_EXTERNAL_ITEM_H_
#include <QObject>
#include <QList>
#include <QVariant>

namespace SVN_EXTERNALS_DISPOSER
{


/// @brief This class represents an file entry and is used by the item-model.
/// @author feddischson
class Item : public QObject
{

   Q_OBJECT
public:

   /// @brief Ctor
   explicit Item( 
         const QList< QVariant > & data, 
         bool is_external = true,
         Item *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Item(const Item & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Item& operator= (const Item & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Item( Item && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Item& operator=( Item && rhs ) = delete;


   /// @brief Default dtor
   ~Item() = default;


   /// @brief QSTring operator, to print data to qDebug()
   operator QString();


   /// @brief Adds a child to the internal child-list
   void append_child( Item * child );


   /// @brief Returns a child from the internal child-list
   Item *child(int row);


   /// @brief Returns the number of childs in our internal child-list
   int child_count() const;


   /// @brief Returns the number of elements of this Item
   int column_count() const;


   /// @brief Returns the QVariant entry for a given column.
   ///        If column is out of bounds, a default constructed 
   ///        QVariant is returned.
   QVariant data(int column) const;


   /// @brief Sets a given data element to the specified column
   void set_data( int column, const QVariant & data );


   /// @brief Returns the row-number of this child. 
   ///        Of this is the root-item, 0 is returned.
   ///        
   int row() const;


   /// @brief Returns the parent item. If none was given for the CTOR, nullptr is returned.
   Item * get_parent_item();


private:


   /// @brief  Internal list of child-items
   QList< Item * > child_items;


   /// @brief  Tnternal list, which holds the data (of type QVariant) of this item.
   QList< QVariant > item_data;


   /// @brief  Defines, if this is an external entry or not
   bool is_external;


   /// @brief Pointer to the parent item.
   Item * parent_item;

}; // class Item

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_EXTERNAL_ITEM_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

