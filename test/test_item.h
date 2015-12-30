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
#ifndef _SVN_EXTERNALS_DISPOSER_TEST_ITEM_H_ 
#define _SVN_EXTERNALS_DISPOSER_TEST_ITEM_H_
#include <QObject>
#include <QTextStream>
#include <QtTest/QtTest>


namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Test class to test Item
class Test_Item : public QObject
{

   Q_OBJECT

private slots:


   void test_column_count();
   void test_empty_column_count();
   void test_empty_child_count();
   void test_child_count();
   void test_child_access();
   void test_data_access();
   void test_data_access_default_variant();
   void test_replace();
   void test_row();
   void test_parent_item();

public:


   /// @author feddischson
   /// @brief Ctor: not implemented!
   explicit Test_Item( QObject *parent = nullptr );


   /// @author feddischson
   /// @brief  Copy ctor: not implemented!
   Test_Item(const Test_Item & m) = delete;


   /// @author feddischson
   /// @brief  Assignment operator: not implemented!
   Test_Item& operator= (const Test_Item & m) = delete;


   /// @author feddischson
   /// @brief  Move constructor: not implemented!
   Test_Item( Test_Item && rhs ) = delete;


   /// @author feddischson
   /// @brief  Move assignment operator: not implemented!
   Test_Item& operator=( Test_Item && rhs ) = delete;


   /// @author feddischson
   /// @brief Standard dtor
   ~Test_Item() = default;


private:


}; // class Test_Item

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TEST_ITEM_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

