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
#ifndef _SVN_EXTERNALS_DISPOSER_BROWSER_MODEL_H_ 
#define _SVN_EXTERNALS_DISPOSER_BROWSER_MODEL_H_
#include <QObject>
#include <QTextStream>
#include <QAbstractItemModel>

#include "browser_item.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Template class
class Browser_Model : public QAbstractItemModel
{

   Q_OBJECT
public:

   /// @brief  Initializes the model by creating the root-item.
   explicit Browser_Model( 
         const QString & path, 
         const QString & url, 
         const QString & revision,
         QObject *parent = nullptr );


   /// @brief Returns the data for a given index (and role).
   QVariant data( const QModelIndex & index, int role ) const Q_DECL_OVERRIDE;

   /// @brief Returns the flags for a given index.
   Qt::ItemFlags flags( const QModelIndex & index ) const Q_DECL_OVERRIDE;

   /// @brief Returns the header-data.
   QVariant headerData( int section, 
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole  ) const Q_DECL_OVERRIDE;

   /// @brief Returns the index for a given row and oclumn.
   QModelIndex index(   int row, 
                        int column, 
                        const QModelIndex & parent = QModelIndex() ) const Q_DECL_OVERRIDE;

   /// @brief Returns the corresponding index for a given url
   QModelIndex index( const QString & url);

   /// @brief Returns the parent for a given index.
   QModelIndex parent( const QModelIndex & index ) const Q_DECL_OVERRIDE;

   /// @brief Returns the number of rows.
   virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const;

   /// @brief Returns the number of columns.
   virtual int columnCount( const QModelIndex & parent = QModelIndex() ) const;


   /// @brief  Copy ctor: not implemented!
   Browser_Model(const Browser_Model & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Browser_Model& operator= (const Browser_Model & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Browser_Model( Browser_Model && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Browser_Model& operator=( Browser_Model && rhs ) = delete;

   /// @brief Returns the url at which the model is initialized.
   QString get_url( void );

   /// @brief Returns the root-url.
   QString get_root_url( void );

   /// @brief Deletes the root_item.
   ~Browser_Model();

private:


   /// @brief Returns the index for a given url (splitted into a QVector<QStringRef>).
   QModelIndex get_index_for_url( 
         const QVector<QStringRef> & list, 
         int index, 
         Browser_Item * parent );


   /// @brief Reads the root-url and url via svn info
   bool get_url_paths( const QString & url );


   /// @brief Pointer to the root item.
   Browser_Item *root_item;

   /// @brief The URL to the repository + folder.
   QString url;

   /// @brief The URL to the repository.
   QString root_url;

   /// @brief The revision which is browsed
   QString revision;

}; // class Browser_Model

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_BROWSER_MODEL_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

