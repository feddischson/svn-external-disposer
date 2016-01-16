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
#include "external_command.h"
#include "data_model.h"
#include <QDebug>

namespace SVN_EXTERNALS_DISPOSER
{


External_Command::External_Command(
      Data_Model          *data_model,
      const QString      & path,
      int                  index,
      const QVariant     & new_value,
      const QVariant     & old_value,
      QUndoCommand *parent )
   : QUndoCommand ( parent     ),
     data_model   ( data_model ),
     path         ( path       ),
     index        ( index      ),
     new_value    ( new_value  ),
     old_value    ( old_value  ),
     called_once  ( false )
{
}


void External_Command::undo()
{
   data_model->change_external( path, old_value, index, false );
}

void External_Command::redo()
{
   if( called_once )
      data_model->change_external( path, new_value, index, false );
   else
      called_once = true; 
}

External_Command::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "External_Command ("  << reinterpret_cast< void* >( this ) << "): \n"
       << new_value.toString() << "\n"
       << old_value.toString();
   return s;
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

