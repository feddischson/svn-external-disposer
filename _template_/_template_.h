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
#ifndef _SVN_EXTERNALS_DISPOSER_TEMPLATE__H 
#define _SVN_EXTERNALS_DISPOSER_TEMPLATE__H
#include <QObject>
#include <QTextStream>

namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Template class
class _Template_ : public QObject
{

   Q_OBJECT
public:

   /// @author feddischson
   /// @brief Ctor: not implemented!
   explicit _Template_( QObject *parent = nullptr ) = delete;


   /// @author feddischson
   /// @brief  Copy ctor: not implemented!
   _Template_(const _Template_ & a_template_) = delete;


   /// @author feddischson
   /// @brief  Assignment operator: not implemented!
   _Template_& operator= (const _Template_ & a_template_) = delete;


   /// @author feddischson
   /// @brief  Move constructor: not implemented!
   _Template_( _Template_ && rhs ) = delete;


   /// @author feddischson
   /// @brief  Move assignment operator: not implemented!
   _Template_& operator=( _Template_ && rhs ) = delete;


   /// @author feddischson
   /// @brief Standard dtor
   ~_Template_() = default;


   /// @author feddischson
   /// @brief QSTring operator, to print data to qDebug()
   virtual operator QString();

private:


}; // class _Template_

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_TEMPLATE__H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

