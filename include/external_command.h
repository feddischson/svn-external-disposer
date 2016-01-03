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
#ifndef _SVN_EXTERNALS_DISPOSER_EXTERNAL_COMMAND_H 
#define _SVN_EXTERNALS_DISPOSER_EXTERNAL_COMMAND_H
#include <QUndoCommand>
#include <QTextStream>

#include "external.h"


namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief  This class is used to support undoing / redping 
///         external modifications.
class External_Command : public QObject, public QUndoCommand
{
   Q_OBJECT
public:

#if 0 // not used at the moment

   enum External_Command_Id { Id = 1234 };
#endif

   /// @brief Ctor: not implemented!
   explicit External_Command(
         QHash< QString, T_SP_External > * external_map,
         const QString       & path,
         const T_SP_External & old_external, 
         QUndoCommand *parent = nullptr );


   /// @brief  Inserts old_external into the external_map
   virtual void undo() Q_DECL_OVERRIDE;

   /// @brief  Inserts new_external into the external map
   virtual void redo() Q_DECL_OVERRIDE;

#if 0  // we use the default behaviour which we disables merging
       // http://doc.qt.io/qt-5.5/qundocommand.html#mergeWith

   /// @brief  Overrides new_external 
   //          with the external provided by cmd->external_map.value( path )
   virtual bool mergeWith(const QUndoCommand *cmd ) Q_DECL_OVERRIDE;

   /// @brief  
   virtual int id() const Q_DECL_OVERRIDE;
#endif 

   /// @brief  Copy ctor: not implemented!
   External_Command(const External_Command & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   External_Command& operator= (const External_Command & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   External_Command( External_Command && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   External_Command& operator=( External_Command && rhs ) = delete;


   /// @brief Standard dtor
   virtual ~External_Command() = default;


   /// @brief QSTring operator, to print data to qDebug()
   virtual operator QString();

private:

   /// @brief  Pointer to the external_map, used by Data_Model
   QHash< QString, T_SP_External > * external_map;

   /// @brief  Path of the external (used as key of external_map)
   QString       path;

   /// @brief  The new external (after changing the content)
   T_SP_External new_external;

   /// @brief  The old external (before changing the content)
   T_SP_External old_external;

}; // class External_Command

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_EXTERNAL_COMMAND_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

