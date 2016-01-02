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
#ifndef _SVN_EXTERNALS_DISPOSER_EXTERNAL_H 
#define _SVN_EXTERNALS_DISPOSER_EXTERNAL_H
#include <QObject>
#include <QTextStream>
#include <QSharedPointer>

namespace SVN_EXTERNALS_DISPOSER
{

/// @brief Represents a external entry. The content is stored in QVariant 
///        attributes
class External 
{  
   public:
   /// @brief Create a valid instance with all necessary information.
   External( 
    const QString & local_path,
    const QString & url,
    const QString & peg_revision,
    const QString & operative_revision,
    const QString & storage_path
         );

   /// @brief Try to crate create a valid instance by parsing a property entry.
   External( const QString & prop_entry, const QString & path );

   /// @brief In case of no data is provided, we create an invalid instance.
   External( ) : valid( false ), modified( false ) { }


   /// @defgroup external_default Default Ctors, Dtor and operators
   /// The defult implementation of (move) copy-ctors, (move) assignment 
   /// operators and destructor is used.
   /// @{
   External( const External & e )              = default;
   External& operator= (const External & rhs ) = default;
   External & operator=( External  && rhs )    = default;
   External ( External  && rhs )               = default;
   ~External ()                                = default;
   /// @}

   /// @brief QString operator: The resulting string is a svn:externals property 
   /// @remark The new syntax (>= svn version 1.5) is returned, even if the
   ///         instance is parsed via old syntax (prior svn version 1.5).
   virtual operator QString();

   /// @defgroup external_data External content
   /// @{
   QVariant local_path;
   QVariant url;
   QVariant peg_revision;
   QVariant operative_revision;
   QVariant storage_path;
   /// @}

   /// @brief valid-flag
   bool valid;

   /// @brief modified-flag
   bool modified;

   private:

   /// @brief  Regular expression matcher for the current svn:externals syntax
   static const QRegExp external_matcher;

   /// @brief  Regular expression matcher for the old svn:externals syntax
   static const QRegExp old_external_matcher;

};

/// @brief  An alias for shared pointers of External
using T_SP_External = QSharedPointer< External >;

/// @defgroup external_comp Comparison Operators
/// @{
bool operator== ( const T_SP_External & e1, const T_SP_External & e2 );
bool operator!= ( const T_SP_External & e1, const T_SP_External & e2 );
/// @}


}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_EXTERNAL_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

