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
//

#include <QTest>
#include <QApplication>
#include "test_external.h"
#include "test_data_model.h"

using namespace SVN_EXTERNALS_DISPOSER;


int main( int argc, char * argv [] )
{
   QApplication app(argc, argv);
   int status = 0;
   auto EXEC_TEST = [&status, argc, argv](QObject* obj) {
     status |= QTest::qExec(obj, argc, argv);
     delete obj;
   };
   EXEC_TEST( new Test_External( ) );
   EXEC_TEST( new Test_Data_Model( "/home/christian/Development/qt/svn-externals-disposer/test/test_tree" ) );
}
