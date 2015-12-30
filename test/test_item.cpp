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
#include "test_item.h"
#include "item.h"
namespace SVN_EXTERNALS_DISPOSER
{

Test_Item::Test_Item( QObject *parent )
  : QObject( parent )
{

}


void  Test_Item::test_column_count()
{
  QList<QVariant> column_data;
  column_data << "r1";
  column_data << "r2";
  column_data << "r3";

  Item * root = new Item( column_data, false );
  QCOMPARE( root->column_count(), 3 );
}


void  Test_Item::test_empty_column_count()
{
  QList<QVariant> column_data;
  Item * root = new Item( column_data, false );
  QCOMPARE( root->column_count(), 0 );
}


void Test_Item::test_empty_child_count()
{
  QList<QVariant> column_data;
  Item * root = new Item( column_data, false );
  QCOMPARE( root->child_count(), 0 );
}

void Test_Item::test_child_count()
{
  QList<QVariant> column_data;
  Item * root = new Item( column_data, false );
  Item * c1   = new Item( column_data, false, root );
  Item * c2   = new Item( column_data, false, root );

  root->append_child( c1 );
  root->append_child( c2 );

  QCOMPARE( root->child_count(), 2 );
}

void Test_Item::test_child_access()
{
  QList<QVariant> column_data;
  Item * root = new Item( column_data, false );
  Item * c1   = new Item( column_data, false, root );
  Item * c2   = new Item( column_data, false, root );

  root->append_child( c1 );
  root->append_child( c2 );

  QCOMPARE( root->child( 0 ), c1 );
  QCOMPARE( root->child( 1 ), c2 );
}


void  Test_Item::test_data_access_default_variant()
{
  QList<QVariant> column_data;

  Item * root = new Item( column_data, false );
  QCOMPARE( root->data( 2 ), QVariant() );
}


void  Test_Item::test_data_access()
{
  QList<QVariant> column_data;
  column_data << "r1";
  column_data << "r2";
  column_data << "r3";

  Item * root = new Item( column_data, false );
  QCOMPARE( root->data( 0 ), column_data[ 0 ] );
  QCOMPARE( root->data( 1 ), column_data[ 1 ] );
  QCOMPARE( root->data( 2 ), column_data[ 2 ] );
}


void  Test_Item::test_replace()
{
  QList<QVariant> column_data;
  column_data << "r1";
  column_data << "r2";
  column_data << "r3";

  Item * root = new Item( column_data, false );

  QVariant r = "test";
  root->set_data( 1, r );
  QCOMPARE( root->data( 1 ), r );
}

void  Test_Item::test_row()
{
  QList<QVariant> column_data;
  Item * root = new Item( column_data, false );
  Item * c1   = new Item( column_data, false, root );
  Item * c2   = new Item( column_data, false, root );
  Item * c1a  = new Item( column_data, false, c1 );
  Item * c1b  = new Item( column_data, false, c1 );
  Item * c1c  = new Item( column_data, false, c1 );

  root->append_child( c1 );
  root->append_child( c2 );
  c1->append_child( c1a );
  c1->append_child( c1b );
  c1->append_child( c1c );

  QCOMPARE( root->row( ), 0 );
  QCOMPARE( c1->row( ), 0 );
  QCOMPARE( c2->row( ), 1 );
  QCOMPARE( c1a->row( ), 0 );
  QCOMPARE( c1b->row( ), 1 );
  QCOMPARE( c1c->row( ), 2 );
}



void  Test_Item::test_parent_item()
{
  Item * nullitem = nullptr;
  QList<QVariant> column_data;
  Item * root = new Item( column_data, false );
  Item * c1   = new Item( column_data, false, root );
  Item * c2   = new Item( column_data, false, root );

  root->append_child( c1 );
  root->append_child( c2 );
  QCOMPARE( root->get_parent_item(), nullitem );
  QCOMPARE( c1->get_parent_item(), root );
  QCOMPARE( c2->get_parent_item(), root );
}



}; // namespace SVN_EXTERNALS_DISPOSER


//QTEST_MAIN(SVN_EXTERNALS_DISPOSER::Test_Item)

// vim: filetype=cpp et ts=3 sw=3 sts=3

