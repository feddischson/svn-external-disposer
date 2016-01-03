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
#ifndef _SVN_EXTERNALS_DISPOSER_DATA_MODEL_H_ 
#define _SVN_EXTERNALS_DISPOSER_DATA_MODEL_H_
#include <QObject>
#include <QTextStream>
#include <QFileSystemModel>
#include <QHash>
#include <QRegExp>
#include <QUndoStack>

#include "external.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @brief The data-model class.
///
/// This class inherits QFileSystemModel to provide a file-system based access to a local
/// SVN repository. This calls futher extends QFileSystemModel by some svn:external information.
/// 
/// @author feddischson
class Data_Model : public QFileSystemModel
{

   #ifdef TESTING
   friend class Test_Data_Model;
   #endif

   Q_OBJECT
public:

   /// @brief Ctor: Initializes the header information
   ///              
   ///
   explicit Data_Model( 
         /*const QString  & path = "", */
         QObject *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Data_Model(const Data_Model & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Data_Model& operator= (const Data_Model & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Data_Model( Data_Model && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Data_Model& operator=( Data_Model && rhs ) = delete;


   /// @brief Default dtor
   virtual ~Data_Model() = default;


   /// @brief  Provides access to a column of an entry.
   /// @return The content of one cell
   QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

   /// @brief  Sets data to an entry
   bool setData(const QModelIndex & index, const QVariant & value, int role) Q_DECL_OVERRIDE;

   /// @brief  Provides flags for an entry
   Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;


   /// @brief  Provides access the header 
   QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

   /// @brief  Returns the number of columns
   int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;


   /// @brief  Sets the root path (for this and fpr the super class)
   QModelIndex setRootPath( const QString & new_path );


   /// @brief  Saves the modified externals
   bool save_externals( void );


   /// @brief  Provides an undo action (from QUndoStack)
   QAction * create_undo_action(QObject * parent, const QString & prefix = QString()) const;


   /// @brief  Provides a redo action (from QUndoStack)
   QAction * create_redo_action(QObject * parent, const QString & prefix = QString()) const;


private:


   /// @brief Provide External_Command access to private data
   friend class External_Command;


   /// @brief Changes an external in external_map
   /// @param path
   ///         The path which is used to find the external in external_map
   /// @param new_value
   ///         The new value
   /// @param index
   ///         The column index (starting from 0)
   /// @param modified [out]
   ///         Is set to true, if the data is modified, otherwise to false
   QVariant change_external(
      const QString & path,
      QVariant new_value,
      int index,
      bool * modified );


   /// @brief Creates a backup of the external information
   void backup( void );


   /// @brief Returns true for a giben external path, if the externals is modified.
   bool is_external_modified( const QString & path ) const;


   /// @brief  Function to find an external entry in our internal map
   T_SP_External get_external( const QModelIndex & index ) const;


   /// @brief  Initializes the svn:externals map external_map
   ///         by scanning the given directory.
   /// @param path
   ///         Path to the directory, which is scanned.
   ///         
   void setup_model_data( 
      const QString                  & path );


   /// @brief  Calls 'svn propget svn:externals ...' via QProcess 
   ///         and extracts the data from the XML output.
   bool read_externals( 
      const QString & path );



   /// @brief  Extracts svn:externals entries from a set of svn:externals (the whole property),
   ///         and calles parse_external to extract the svn:externals information.
   ///         The result is stored in external_map.
   void extract_externals( 
      const QString       & path,
      const QString       & property );


   /// @brief  List for our header extension
   QList< QVariant > header;

   /// @brief  Holds all externals (via QSharedDataPointer).
   ///         The absolute local path is used as key
   QHash< QString, T_SP_External > external_map;

   /// @brief  Maps the paths (where the property is defined) to the external items
   QMultiMap< QString, T_SP_External > property_map;



   /// @brief  Backup of external_map
   QHash< QString, T_SP_External > external_map_backup;

   /// @brief  Backup of property_map
   QMultiMap< QString, T_SP_External > property_map_backup;

   /// @brief The root path which points to a local SVN working copy
   QString root_path;

   /// @brief An undo stack to support undo/redo.
   QUndoStack undo_stack;

}; // class Data_Model


}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_DATA_MODEL_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

