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
#ifndef _SVN_EXTERNALS_DISPOSER_FILTER_H_ 
#define _SVN_EXTERNALS_DISPOSER_FILTER_H_
#include <QObject>
#include <QTextStream>
#include <QSortFilterProxyModel>

namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Template class
class Filter : public QSortFilterProxyModel
{

   Q_OBJECT
public:

   /// @brief Ctor: not implemented!
   explicit Filter( QObject *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Filter(const Filter & a_template_) = delete;


   /// @brief  Assignment operator: not implemented!
   Filter& operator= (const Filter & a_template_) = delete;


   /// @brief  Move constructor: not implemented!
   Filter( Filter && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Filter& operator=( Filter && rhs ) = delete;


   /// @brief Standard dtor
   ~Filter() = default;


   /// @brief QSTring operator, to print data to qDebug()
   virtual operator QString();

   /// @brief Returns true, if the row shall be shown, otherwise false.
   virtual bool filterAcceptsRow(int source_row,
        const QModelIndex &source_parent) const;


   /// @brief Sets the external-filter state.
   void set_filter_externals( bool state );

   /// @brief Returns the external-filter state.
   bool get_filter_externals( void );

private:

   /// @brief Internal flag: true = only externals are shown.
   bool show_only_externals;

}; // class Filter

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_FILTER_H_ 

// vim: filetype=cpp et ts=3 sw=3 sts=3

