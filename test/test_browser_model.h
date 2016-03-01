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
#ifndef _SVN_EXTERNALS_DISPOSER_TEST_BROWSER_MODEL_H_ 
#define _SVN_EXTERNALS_DISPOSER_TEST_BROWSER_MODEL_H_
#include <QObject>
#include <QTextStream>
#include <QtTest/QtTest>


namespace SVN_EXTERNALS_DISPOSER
{


/// @brief Template class
class Test_Browser_Model : public QObject
{

   Q_OBJECT

private slots:


   void test_01_correct_root_url( void );

   void initTestCase();
   void cleanupTestCase();



public:

   /// @brief 
   explicit Test_Browser_Model( QObject *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Test_Browser_Model(const Test_Browser_Model & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Test_Browser_Model& operator= (const Test_Browser_Model & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Test_Browser_Model( Test_Browser_Model && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Test_Browser_Model& operator=( Test_Browser_Model && rhs ) = delete;


   /// @brief Standard dtor
   ~Test_Browser_Model() = default;

private:
   static const QString TEST_TREE_PATH;
   static const QString TEST_TREE_REPO_PATH;


}; // class Test_Browser_Model

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TEST_BROWSER_MODEL_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

