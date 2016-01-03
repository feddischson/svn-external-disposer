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


namespace SVN_EXTERNALS_DISPOSER
{


External_Command::External_Command( 
         QHash< QString, T_SP_External > * external_map,
         const QString       & path,
         const T_SP_External & external, 
         QUndoCommand *parent  ) 
   : QUndoCommand ( parent       ),
     external_map ( external_map ),
     path         ( path         ),
     new_external( new External( *external_map->value( path ) ) ),
     old_external( new External( *external ) )
{
}


void External_Command::undo()
{
   *(external_map->value( path )) = *(old_external);
}

void External_Command::redo()
{
   *(external_map->value( path )) = *(new_external);
}


#if 0
bool External_Command::mergeWith(const QUndoCommand * cmd )
{
   const External_Command *external_command 
      = static_cast< const External_Command* >( cmd );

   if( external_command->external_map != external_map || 
       external_command->path         != path             )
      return false;

   // this is not correct
   *(new_external) = *(external_map->value( path ) );

   return true;
}


int External_Command::id() const
{ 
   return External_Command_Id::Id; 
}
#endif


External_Command::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "External_Command ("  << reinterpret_cast< void* >( this ) << "): \n"
       << *old_external << "\n"
       << *new_external;
   return s;
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

