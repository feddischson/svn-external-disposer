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
#include <QDebug>

#include "filter.h"

namespace SVN_EXTERNALS_DISPOSER
{

Filter::Filter( QObject * parent ) 
   : QSortFilterProxyModel( parent ),
     show_only_externals( false )
{

}


Filter::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Filter ("  << reinterpret_cast< void* >( this ) << "): "
       << "TODO=" << "Add more content of this instance here @ " 
       << __FILE__ << ":" << __LINE__;
   return s;
}

bool Filter::filterAcceptsRow(int source_row,
        const QModelIndex & parentIndex ) const
{
   if( this->show_only_externals  == true )
   {
      qDebug() << source_row;
      if( parentIndex.isValid() )
         qDebug() << parentIndex;
      // @todo add real implementation here
      return ( source_row%2 == 0 ); 
   }
   else
      return true;
}


bool Filter::get_filter_externals( void )
{
   return this->show_only_externals;
}

void Filter::set_filter_externals( bool state )
{
   this->show_only_externals = state;
}

}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

