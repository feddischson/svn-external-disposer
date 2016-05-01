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

#include <QProcess>
#include <QDebug>
#include <QDir>

#include "test_browser_model.h"
#include "browser_model.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{

const QString Test_Browser_Model::TEST_TREE_PATH      = "./test/test_tree";
const QString Test_Browser_Model::TEST_TREE_REPO_PATH = "./test/test_tree_repo";

Test_Browser_Model::Test_Browser_Model( QObject *parent )
   : QObject( parent )
{

}

void Test_Browser_Model::test_01_correct_root_url( void )
{
   QString root = "file://" + QDir( TEST_TREE_REPO_PATH ).absolutePath();

   // initiate with a non-root url -> should lookup the root url
   Browser_Model * m = new Browser_Model( TEST_TREE_PATH + "/d1/d1c", "HEAD" );
   QModelIndex i = m->index( 0, 0 );
   QCOMPARE( i.isValid(), true );
   Browser_Item * item = static_cast< Browser_Item * >( i.internalPointer() );
   QCOMPARE( item->parent()->url(), root );
}

void Test_Browser_Model::initTestCase()
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

void Test_Browser_Model::cleanupTestCase()
{
   qDebug() << "Cleaning up test repository";
   QDir( TEST_TREE_PATH ).removeRecursively();
   QDir( TEST_TREE_REPO_PATH ).removeRecursively();
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

