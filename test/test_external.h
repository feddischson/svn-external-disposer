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
#ifndef _SVN_EXTERNALS_DISPOSER_TEST_DATA_MODEL_H_ 
#define _SVN_EXTERNALS_DISPOSER_TEST_DATA_MODEL_H_
#include <QObject>
#include <QTextStream>
#include <QtTest/QtTest>


namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Test class to test Data_Model
class Test_External : public QObject
{

   Q_OBJECT

private slots:


   void test_external1();
   void test_external2();
   void test_external3();
   void test_external4();
   void test_external5();
   void test_external6();
   void test_external7();


   void test_comparison1();
   void test_comparison2();
   void test_comparison3();
   void test_comparison4();
   void test_comparison5();
   void test_comparison6();
   void test_comparison7();
   void test_comparison8();
public:


   /// @author feddischson
   /// @brief Ctor: not implemented!
   explicit Test_External( QObject *parent = nullptr );


   /// @author feddischson
   /// @brief  Copy ctor: not implemented!
   Test_External(const Test_External & m) = delete;


   /// @author feddischson
   /// @brief  Assignment operator: not implemented!
   Test_External& operator= (const Test_External & m) = delete;


   /// @author feddischson
   /// @brief  Move constructor: not implemented!
   Test_External( Test_External && rhs ) = delete;


   /// @author feddischson
   /// @brief  Move assignment operator: not implemented!
   Test_External& operator=( Test_External && rhs ) = delete;


   /// @author feddischson
   /// @brief Standard dtor
   ~Test_External() = default;


private:


}; // class Test_External

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TEST_DATA_MODEL_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3


