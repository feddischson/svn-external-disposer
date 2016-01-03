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
#include <QModelIndex>

#include "data_model.h"
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

   /// @brief Ctor: not implemented!
   External_Command(
         Data_Model *         data_model,
         const QString      & path,
         int                  index,
         const QVariant     & new_value,
         const QVariant     & old_value,
         QUndoCommand *parent = nullptr );


   /// @brief  Inserts old_external into the external_map
   virtual void undo() Q_DECL_OVERRIDE;

   /// @brief  Inserts new_external into the external map
   virtual void redo() Q_DECL_OVERRIDE;


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

   /// @brief The data-model, which holds/manages the externals
   Data_Model *         data_model;

   QString              path;

   /// @brief The index, which is chagned
   int                  index;

   /// @brief The new value
   const QVariant       new_value;

   /// @brief The old value
   const QVariant       old_value;

   /// @brief Flag to discard first redo call
   bool                 called_once;

}; // class External_Command

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_EXTERNAL_COMMAND_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

