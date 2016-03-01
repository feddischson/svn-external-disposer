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

#include "test_browser_item.h"
#include "browser_item.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{

const QString Test_Browser_Item::TEST_TREE_PATH      = "./test/test_tree";
const QString Test_Browser_Item::TEST_TREE_REPO_PATH = "./test/test_tree_repo";

Test_Browser_Item::Test_Browser_Item( QObject *parent )
   : QObject( parent )
{

}


void Test_Browser_Item::initTestCase()
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

void Test_Browser_Item::cleanupTestCase()
{
   qDebug() << "Cleaning up test repository";
   QDir( TEST_TREE_PATH ).removeRecursively();
   QDir( TEST_TREE_REPO_PATH ).removeRecursively();
}



void Test_Browser_Item::test_01_n_columns()
{
   Browser_Item * b = new Browser_Item( "file://" + QDir( TEST_TREE_REPO_PATH ).absolutePath(),
         QList< QVariant> () 
         << GUI_HEAD_NAME
         << GUI_HEAD_KIND 
         << GUI_HEAD_REVISION
         << GUI_HEAD_AUTHOR
         << GUI_HEAD_DATE
         << GUI_HEAD_SIZE
         );
   QCOMPARE( b->column_count(),  BROWSER_N_COL );
}


void Test_Browser_Item::test_02_children()
{
   Browser_Item * b = new Browser_Item( "file://" + QDir( TEST_TREE_REPO_PATH ).absolutePath(),
         QList< QVariant> () 
         << GUI_HEAD_NAME
         << GUI_HEAD_KIND 
         << GUI_HEAD_REVISION
         << GUI_HEAD_AUTHOR
         << GUI_HEAD_DATE
         << GUI_HEAD_SIZE
         );
   QCOMPARE( b->child_count(), 4 );

   QCOMPARE( b->child( 0 )->data(0).toString(), QString( "d1" ) );
   QCOMPARE( b->child( 1 )->data(0).toString(), QString( "d2" ) );
   QCOMPARE( b->child( 2 )->data(0).toString(), QString( "d3" ) );
   QCOMPARE( b->child( 3 )->data(0).toString(), QString( "d4" ) );
}



}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

