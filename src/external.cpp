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
#include "external.h"
#include "const.h"

namespace SVN_EXTERNALS_DISPOSER
{


External::External( 
 const QString & local_path,
 const QString & url,
 const QString & peg_revision,
 const QString & operative_revision,
 const QString & storage_path
      ) : 
   local_path         ( local_path         ),
   url                ( url                ),
   peg_revision       ( peg_revision       ),
   operative_revision ( operative_revision ),
   storage_path       ( storage_path       ),
   valid( true ),
   modified( false ){ }


External::External( const QString & prop_entry, const QString & path ) 
   : storage_path( path ), 
     modified( false )
{
   int pos;

   // first: try the old syntax
   pos = External::old_external_matcher.indexIn( prop_entry );
   if( pos > -1 )
   {
      local_path         = old_external_matcher.cap(1), // local path
      url                = old_external_matcher.cap(4), // url
      peg_revision       = QString(""),                 // peg-revision
      operative_revision = old_external_matcher.cap(3), // operative-revision
      valid              = true;
   }
   else
   {
      // second: try the current syntax
      pos = External::external_matcher.indexIn( prop_entry );
      if( pos > -1 )
      {
         local_path         = external_matcher.cap(6), // local path
         url                = external_matcher.cap(3), // url
         peg_revision       = external_matcher.cap(5), // peg
         operative_revision = external_matcher.cap(2), // operative
         valid              = true;
      }
      else
         valid = false;
   }

}



External::operator QString()
{
   QString s;
   QTextStream ts(&s);
   if( operative_revision.toString().length() > 0 )
      ts << "-r" << operative_revision.toString() << " ";
   ts << url.toString();
   if( peg_revision.toString().length() > 0 )
      ts << "@" << peg_revision.toString();
   ts << " " << local_path.toString();
   return s;
}


bool operator== ( const T_SP_External & e1, const T_SP_External & e2 )
{
   return (*e1) == (*e2);
}

bool operator== ( const External & e1, const External & e2 )
{
   return e1.local_path          == e2.local_path   && 
          e1.url                 == e2.url          &&
          e1.peg_revision        == e2.peg_revision &&
          e1.operative_revision  == e2.operative_revision &&
          e1.storage_path        == e2.storage_path;
}

bool operator!= ( const External & e1, const External & e2 )
{
   return !( e1 == e2 );
}

bool operator!= ( const T_SP_External & e1, const T_SP_External & e2 )
{
   return !( e1 == e2 );
}



const QRegExp External::external_matcher( EXTERNAL_REGEX );
const QRegExp External::old_external_matcher( OLD_EXTERNAL_REGEX );



}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

