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
#include "test_data_model.h"
#include <QDebug>
#include <QProcess>

namespace SVN_EXTERNALS_DISPOSER
{


const QString Test_Data_Model::TEST_TREE_PATH      = "./test/test_tree";
const QString Test_Data_Model::TEST_TREE_REPO_PATH = "./test/test_tree_repo";


Test_Data_Model::Test_Data_Model( 
      const QString & root_path, QObject *parent )
  : QObject( parent ), data_model( nullptr ), root_path( root_path )
{

}
void Test_Data_Model::initTestCase()
{
   QProcess process;
   qDebug() << "Initialize test repository ...";
   process.start( "python", QStringList() 
         << "./test/setup_test_repo.py" 
         << TEST_TREE_PATH
         << TEST_TREE_REPO_PATH );
   if( !( process.waitForFinished( 60000 ) && 
          process.exitCode() == 0 ) // wait 60 seconds (60000 msec):
     )
   {
      qDebug() << "Failed to setup SVN repository";
      qDebug() << process.readAllStandardError();
      exit(-1);
   }
   else
      qDebug() << " .... done";
}

void Test_Data_Model::cleanupTestCase()
{
   qDebug() << "Cleaning up test repository";
   QDir( TEST_TREE_PATH ).removeRecursively();
   QDir( TEST_TREE_REPO_PATH ).removeRecursively();
}

void Test_Data_Model::reads_correct_external_information1()
{
   QString key_path     = QDir( TEST_TREE_PATH + "/d3/external_lib1" ).absolutePath( );
   QString storage_path = QDir( TEST_TREE_PATH + "/d3"               ).absolutePath( );
   T_SP_External e = data_model->external_map[ key_path ];
   QCOMPARE( static_cast< bool >( e ), true );
   QCOMPARE( *e, External(
                     QString( "external_lib1" ),
                     QString( "^/d2/d2a"      ),
                     QString( "" ),
                     QString( "4" ),
                     storage_path ) );
}

void Test_Data_Model::reads_correct_external_information2()
{
   QString key_path     = QDir( TEST_TREE_PATH + "/d3/external_lib2" ).absolutePath( );
   QString storage_path = QDir( TEST_TREE_PATH + "/d3"               ).absolutePath( );
   T_SP_External e = data_model->external_map[ key_path ];
   QCOMPARE( static_cast< bool >( e ), true );
   QCOMPARE( *e, External(
                     QString( "external_lib2" ),
                     QString( "^/d2/d2b"      ),
                     QString( "2" ),
                     QString( "" ),
                     storage_path ) );
}


void Test_Data_Model::reads_correct_external_information3()
{

   QString key_path     = QDir( TEST_TREE_PATH + "/d4/external_lib3" ).absolutePath( );
   QString storage_path = QDir( TEST_TREE_PATH + "/d4"               ).absolutePath( );
   T_SP_External e = data_model->external_map[ key_path ];
   QCOMPARE( static_cast< bool >( e ), true );
   QCOMPARE( *e, External(
                     QString( "external_lib3" ),
                     QString( "^/d2/d2a"      ),
                     QString( "" ),
                     QString( "" ),
                     storage_path ) );
}




void Test_Data_Model::reads_correct_external_information4()
{

   QString key_path     = QDir( TEST_TREE_PATH + "/d1/d1b/external_lib4" ).absolutePath( );
   QString storage_path = QDir( TEST_TREE_PATH + "/d1"                   ).absolutePath( );
   T_SP_External e = data_model->external_map[ key_path ];
   QCOMPARE( static_cast< bool >( e ), true );
   QCOMPARE( *e, External(
                     QString( "d1b/external_lib4" ),
                     QString( "^/d2/d2b"      ),
                     QString( "" ),
                     QString( "" ),
                     storage_path ) );
}


void Test_Data_Model::reads_correct_external_information5()
{
   QString key_path     = QDir( TEST_TREE_PATH + "/d1/external_lib5" ).absolutePath( );
   QString storage_path = QDir( TEST_TREE_PATH + "/d1"               ).absolutePath( );
   T_SP_External e = data_model->external_map[ key_path ];
   QCOMPARE( static_cast< bool >( e ), true );
   QCOMPARE( *e, External(
                     QString( "external_lib5" ),
                     QString( "../d2/d2a"      ),
                     QString( "3" ),
                     QString( "3" ),
                     storage_path ) );
}


void Test_Data_Model::reads_correct_external_information6()
{
   QString key_path     = QDir( TEST_TREE_PATH + "/d1/an_external_file.xyz" ).absolutePath( );
   QString storage_path = QDir( TEST_TREE_PATH + "/d1"               ).absolutePath( );
   T_SP_External e = data_model->external_map[ key_path ];
   QCOMPARE( static_cast< bool >( e ), true );
   QCOMPARE( *e, External(
                     QString( "an_external_file.xyz" ),
                     QString( "^/d4/d4a/f1.txt"      ),
                     QString( "2" ),
                     QString( "1" ),
                     storage_path ) );
}


void Test_Data_Model::init()
{
   if( data_model != nullptr )
      delete data_model;

   data_model = new Data_Model();
   root_index = data_model->setRootPath( root_path );
}

void Test_Data_Model::cleanup()
{
   if( data_model != nullptr )
      delete data_model;
   data_model = nullptr; 
}

}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

