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
#include <QAbstractItemModel>
#include <QMap>
#include <QRegExp>

#include <item.h>

namespace SVN_EXTERNALS_DISPOSER
{


/// @brief The data-model class.
///
/// This class realizes QAbstractItemModel and provides access to instances of Item.
/// Moreover, the function setup_model_data scans a given directory, uses 'svn propget' 
/// to extract the svn:externals information and creates these instances of Item.
/// 
/// @author feddischson
class Data_Model : public QAbstractItemModel
{

   #ifdef TESTING
   friend class Test_Data_Model;
   #endif

   Q_OBJECT
public:

   /// @brief Ctor: scans recusively the directory defined by path
   ///              via setup_model_data.
   ///
   explicit Data_Model( 
         const QString  & path = "", 
         QObject *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Data_Model(const Data_Model & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Data_Model& operator= (const Data_Model & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Data_Model( Data_Model && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Data_Model& operator=( Data_Model && rhs ) = delete;


   /// @brief Standard dtor
   ~Data_Model();


   /// @brief  Provides access to a column of an Item Item.
   /// @return The content of one cell
   QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;


   /// @brief  Provides flags for an column of an Item
   Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;


   /// @brief  Provides access the header (the root item)
   QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;


   /// @brief  Creates and returns an index of a child item, 
   //          if the parent index is valid.
   QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;


   /// @brief  Crestes and returns an index of a parent item.
   QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;


   /// @brief  Returns the number of rows 
   int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;


   /// @brief  Returns the number of columns 
   int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;


   /// @brief  Sets the data to a specific Item.
   bool setData( const QModelIndex & index,
                              const QVariant & value, int role ) Q_DECL_OVERRIDE;


private:

   /// @brief  Initializes the model data by scanning the given directory.
   /// @param path
   ///         Path to the directory, which is scanned.
   /// @param parent
   ///         The parent item, to which the new Items are added. 
   ///         
   void setup_model_data( 
      const QString                  & path, 
      Item *parent );


   /// @brief  Calls 'svn propget svn:externals ...' via QProcess 
   ///         and extracts the data from the XML output.
   bool read_externals( 
      const QString & path,
      QMap< QString, QString > * external_map );



   /// @brief  Extracts svn:externals entries from a set of svn:externals (the whole property).
   /// @return A QMap with paths as key and Item as values.
   QMap< QString, Item* > extract_externals( 
            Item * parent, 
      const QString       & external_property );



   /// @brief  Parses svn:external entries via regular expressions
   QList< QVariant > parse_external( const QString & entry );



   /// @brief  Regular expression matcher for the current svn:externals syntax
   QRegExp external_matcher;

   /// @brief  Regular expression matcher for the old svn:externals syntax
   QRegExp old_external_matcher;


   /// @brief  The root item.
   Item *root_item;

}; // class Data_Model

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_DATA_MODEL_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

