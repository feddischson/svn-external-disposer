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
#include "test_external.h"
#include "external.h"
namespace SVN_EXTERNALS_DISPOSER
{

Test_External::Test_External( QObject *parent )
  : QObject( parent )
{

}


void  Test_External::test_external1()
{
  QString input = "-r4 http://some-url/svn-xy@5 local-path";
  External result(
        input, 
        "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "local-path" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://some-url/svn-xy" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "5" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "4" ) );

  QString string_result = result;
  QCOMPARE( string_result, input );
}





void  Test_External::test_external2()
{
  QString input = "^/../some/other/path xyz";
  External result( input, "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "xyz" ) );
  QCOMPARE( result.url.toString() ,                QString( "^/../some/other/path" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );

  QString string_result = result;
  QCOMPARE( string_result, input );
}



void  Test_External::test_external3()
{
  QString input = "https:/svn_url/xyz@5 abc_def";
  External result( input, "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "abc_def" ) );
  QCOMPARE( result.url.toString() ,                QString( "https:/svn_url/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "5" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );

  QString string_result = result;
  QCOMPARE( string_result, input );
}

void  Test_External::test_external4()
{
  QString input = "^/../some_project/xyz test1/some_lib";
  External result( input, "some/dir"  );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "test1/some_lib" ) );
  QCOMPARE( result.url.toString() ,                QString( "^/../some_project/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );

  QString string_result = result;
  QCOMPARE( string_result, input );
}



void  Test_External::test_external5()
{
  QString input    = "test1/some_lib http://192.168.222.222/svn/testproj3/xyz";
  QString expected = "http://192.168.222.222/svn/testproj3/xyz test1/some_lib";
  External result( 
        input, 
        "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "test1/some_lib" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://192.168.222.222/svn/testproj3/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "" ) );

  QString string_result = result;
  QCOMPARE( string_result, expected );
}

void  Test_External::test_external6()
{
  QString input = "test1/some_lib   -r     4  http://192.168.222.222/svn/testproj3/xyz";
  QString expected = "-r4 http://192.168.222.222/svn/testproj3/xyz test1/some_lib";
  External result( 
        input, 
        "some/dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "test1/some_lib" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://192.168.222.222/svn/testproj3/xyz" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString() , QString( "4" ) );

  QString string_result = result;
  QCOMPARE( string_result, expected );
}

void  Test_External::test_external7()
{
  QString input    = "dir http://192.168.123.123";
  QString expected = "http://192.168.123.123 dir";
  External result( 
        input,
        "some_dir" );
  QCOMPARE( result.valid, true );
  QCOMPARE( result.local_path.toString() ,         QString( "dir" ) );
  QCOMPARE( result.url.toString() ,                QString( "http://192.168.123.123" ) );
  QCOMPARE( result.peg_revision.toString() ,       QString( "" ) );
  QCOMPARE( result.operative_revision.toString(), QString( "" ) );

  QString string_result = result;
  QCOMPARE( string_result, expected );
}



void Test_External::test_comparison1()
{
  QString se1 = "http://192.168.123.123@2 dir";
  QString se2 = "http://192.168.123.123@3 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, false );
}



void Test_External::test_comparison2()
{
  QString se1 = "http://192.168.123.123@2 dir";
  QString se2 = "http://192.168.123.123@2 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, true );
}



void Test_External::test_comparison3()
{
  QString se1 = "http://192.168.123.123@2 dir1";
  QString se2 = "http://192.168.123.123@2 dir2";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, false );
}



void Test_External::test_comparison4()
{
  QString se1 = "http://192.168.123.123@2 dir";
  QString se2 = "http://192.168.123.123@2 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dirx" ) );
  QCOMPARE( e1 == e2, false );
}


void Test_External::test_comparison5()
{
  QString se1 = "http://192.168.123.123@2 dir";
  QString se2 = "http://192.168.123.111@2 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, false );
}



void Test_External::test_comparison6()
{
  QString se1 = "http://192.168.123.123@2 dir";
  QString se2 = " http://192.168.123.123@2 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, true );
}


void Test_External::test_comparison7()
{
  QString se1 = "  -r  3 http://192.168.123.123@2 dir";
  QString se2 = "-r3 http://192.168.123.123@2 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, true );
}


void Test_External::test_comparison8()
{
  QString se1 = "  -r  3 http://192.168.123.123@2 dir";
  QString se2 = "     -r4 http://192.168.123.123@2 dir";
  T_SP_External e1( new External( 
        se1,
        "some_dir" ) );
  T_SP_External e2( new External( 
        se2,
        "some_dir" ) );
  QCOMPARE( e1 == e2, false );
}




}; // namespace SVN_EXTERNALS_DISPOSER


// vim: filetype=cpp et ts=3 sw=3 sts=3

