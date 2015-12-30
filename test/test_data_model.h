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
class Test_Data_Model : public QObject
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

public:


   /// @author feddischson
   /// @brief Ctor: not implemented!
   explicit Test_Data_Model( QObject *parent = nullptr );


   /// @author feddischson
   /// @brief  Copy ctor: not implemented!
   Test_Data_Model(const Test_Data_Model & m) = delete;


   /// @author feddischson
   /// @brief  Assignment operator: not implemented!
   Test_Data_Model& operator= (const Test_Data_Model & m) = delete;


   /// @author feddischson
   /// @brief  Move constructor: not implemented!
   Test_Data_Model( Test_Data_Model && rhs ) = delete;


   /// @author feddischson
   /// @brief  Move assignment operator: not implemented!
   Test_Data_Model& operator=( Test_Data_Model && rhs ) = delete;


   /// @author feddischson
   /// @brief Standard dtor
   ~Test_Data_Model() = default;


private:


}; // class Test_Data_Model

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TEST_DATA_MODEL_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3


