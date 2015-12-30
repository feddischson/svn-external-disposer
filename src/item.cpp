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
#include "item.h"
#include <QTextStream>

namespace SVN_EXTERNALS_DISPOSER
{

Item::Item( 
   const QList< QVariant > & data, 
   bool is_external,
   Item * parent )
   : item_data( data ),
     is_external( is_external ),
     parent_item( parent )
{

}


void Item::append_child( Item * child )
{
   child_items.append( child );
}

Item * Item::child( int row )
{
   return child_items.value( row );
}


int Item::child_count() const
{
   return child_items.count();
}


int Item::column_count() const
{
   return item_data.count();
}


QVariant Item::data(int column) const
{
   return item_data.value(column);
}

void Item::set_data( int column, const QVariant & data )
{
   item_data.replace( column, data );
}

int Item::row() const
{
    if ( parent_item != nullptr )
        return parent_item->child_items.indexOf(const_cast<Item*>(this));

    return 0;
}


Item * Item::get_parent_item()
{
   return parent_item;
}


Item::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Item ("  << reinterpret_cast< void* >( this ) << "): ";
   for( auto item : item_data )
       ts << item.toString() << " ";
   return s;
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

