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
#include "test_data_model.h"
#include "data_model.h"
namespace SVN_EXTERNALS_DISPOSER
{

Test_Data_Model::Test_Data_Model( QObject *parent )
  : QObject( parent )
{

}


void  Test_Data_Model::test_external1()
{
  Data_Model m;
  Data_Model::External result = m.parse_external(
        "-r 4 http://some-url/svn-xy@5 local-path", 
        "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "local-path" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://some-url/svn-xy" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "5" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "4" ) );
}





void  Test_Data_Model::test_external2()
{
  Data_Model m;
  Data_Model::External result = m.parse_external( "^/../some/other/path xyz", "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "xyz" ) );
  QCOMPARE( result.url.toString() ,                QString( "^/../some/other/path" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );
}



void  Test_Data_Model::test_external3()
{
  Data_Model m;
  Data_Model::External result = m.parse_external( "https:/svn_url/xyz@5 abc_def", "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "abc_def" ) );
  QCOMPARE( result.url.toString() ,                QString( "https:/svn_url/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "5" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );
}

void  Test_Data_Model::test_external4()
{
  Data_Model m;
  Data_Model::External result = m.parse_external( "^/../some_project/xyz test1/some_lib", "some/dir"  );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "test1/some_lib" ) );
  QCOMPARE( result.url.toString() ,                QString( "^/../some_project/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );
}



void  Test_Data_Model::test_external5()
{
  Data_Model m;
  Data_Model::External result = m.parse_external( 
        "test1/some_lib http://192.168.222.222/svn/testproj3/xyz", 
        "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "test1/some_lib" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://192.168.222.222/svn/testproj3/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );
}

void  Test_Data_Model::test_external6()
{
  Data_Model m;
  Data_Model::External result = m.parse_external( 
        "test1/some_lib   -r     4  http://192.168.222.222/svn/testproj3/xyz", 
        "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "test1/some_lib" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://192.168.222.222/svn/testproj3/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "4" ) );
}

void  Test_Data_Model::test_external7()
{
  Data_Model m;
  Data_Model::External result = m.parse_external( 
        "dir http://192.168.123.123",
        "some_dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "dir" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://192.168.123.123" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString(), QString( "" ) );
}


}; // namespace SVN_EXTERNALS_DISPOSER


//QTEST_MAIN(SVN_EXTERNALS_DISPOSER::Test_Data_Model)

// vim: filetype=cpp et ts=3 sw=3 sts=3

