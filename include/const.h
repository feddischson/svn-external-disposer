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
#ifndef _SVN_EXTERNALS_DISPOSER_CONST_H 
#define _SVN_EXTERNALS_DISPOSER_CONST_H
#include <QObject>
#include <QString>

namespace SVN_EXTERNALS_DISPOSER
{

   /// @brief The name of this tool
   static const QString APP_VERSION          = _APP_VERSION;
   static const QString APP_NAME             = "SVN-Externals-Disposer";
   static const QString ORGANIZATION_NAME    = "SVN-Externals-Disposer";
   static const QString ORGANIZATION_DOMAIN  = "SVN.Externals.Disposer";

   /// @defgroup xml_const  XML string constants
   /// Used to extract data from the xml output of svn propget --xml
   /// @{
   static const QString XML_NAME_TARGET   = "target"; 
   static const QString XML_NAME_PROPERTY = "property";
   static const QString XML_NAME_PATH     = "path";
   /// @}

   /// @defgroup svn_const  SVN string constants
   /// Used to create 'svn propget ...' commands
   /// @{
   static const QString SVN_CMD           = "svn";
   static const QString SVN_PROPGET       = "propget";
   static const QString SVN_PROPSET       = "propset";
   static const QString SVN_INFO          = "info";
   static const QString SVN_EXTERNALS     = "svn:externals";
   static const QString SVN_XML           = "--xml";
   static const QString SVN_RECURSIVE     = "-R";
   static const QString SVN_DEPTH         = "--depth";
   static const QString SVN_FILES         = "files";
   static const QString SVN_EXTERNAL_SEP  = "\n";
   /// @}

   /// @defgroup sys_const  System constants
   /// 
   /// @{

   /// @brief The timeout, which is used in QProcess for system calls.
   static const qint32  SYS_PROCESS_TIMEOUT = 3000; 
   /// @}

   /// @defgroup set_const  QSetting string constants
   /// Used to load/store QSettings.
   /// @{
   static const QString SET_FILE          = "/settings.ini";
   static const QString SET_CP_PATH       = "working_cp_path";
   static const QString SET_COLUMN_W1     = "column_width1";
   static const QString SET_COLUMN_W2     = "column_width2";
   static const QString SET_COLUMN_W3     = "column_width3";
   static const QString SET_COLUMN_W4     = "column_width4";
   /// @}

   /// @defgroup gui_const  GUI string constants
   /// String constants used within the GUI.
   /// @{
   static const QString GUI_HEAD_TARGET       = QObject::tr( "Target"             );
   static const QString GUI_HEAD_EXTERNAL     = QObject::tr( "External Path"      );
   static const QString GUI_HEAD_PEG          = QObject::tr( "Peg Revision"       );
   static const QString GUI_HEAD_OPERATIVE    = QObject::tr( "Operative Revision" );
   static const QString GUI_HEAD_PATH         = QObject::tr( "Defined at"         );
   /// @}

   static const QColor COL_MODIFIED          = Qt::yellow;

   /// 
   /// @defgroup regex Regular Expressions
   /// @brief Two regular exressions to match the following examples:
   /// @verbatim
   // 
   //
   //  Examples for the current syntax:
   //
   //  -r 4 http://some-url/svn-xy@5 local-path
   //  ^/../some/other/path xyz
   //  https:/svn_url/xyz@554 abc_def
   //  ^/../some_project/xyz test1/some_lib 
   //
   //
   //
   //  Examples for the old syntax:
   //
   //  test1/some_lib http://192.168.222.222/svn/testproj3/xyz
   //  xyz/ab  http://192.168.222.222/svn/testproj3/xyz
   //  test1/some_lib   -r     4  http://192.168.222.222/svn/testproj3/xyz 
   //  test1/some_lib -r 124 http://192.168.222.222/svn/testproj3/xyz 
   //  dir http://192.168.123.123 
   //
   //
   //  Invalid examples for the old syntax:
   //
   //  test1/some_lib ^/../testproj3/xyz
   //
   //
   //
   //  @endverbatim
   /// 
   /// @{
   ///


   ///
   /// @brief Regular expression to match the current external syntax
   /// @ingroup regex
   /// @verbatim
   //   ^(\s*-r\s*(\d+))?\s*([^@\s]+)(@(\d+))?\s*(\S+)\s*$
   //  
   //  
   //   ^                        Start of the line
   //   (\s*-r\s*([0-9]+))?\s*   A optional operative revision, e.g. -r 4
   //   ([^@\s]+)                A URL (everything except @ and spaces)
   //   (@(\d+))?                A optional peg-revision, e.g. @456
   //   \s*                      Some spaces
   //   (\S+)                    The local path
   //   \s*$                     Spaces and end of th eline
   //  
   //  Group-result:
   //     - 2: operative revision
   //     - 3: source url
   //     - 5: peg revision
   //     - 6: local-path
   //  
   //   @endverbatim
   ///
   static const QString EXTERNAL_REGEX        = "^(\\s*-r\\s*(\\d+))?\\s*([^@\\s]+)(@(\\d+))?\\s*(\\S+)\\s*$";


   /// @brief Regular expression to match the old external syntax
   /// @ingroup regex
   /// @verbatim
   //
   //  ^\s*(\S+)\s+(-r\s+(\d+)\s*)?(http:\/\/\S*)\s*$
   // 
   //  ^\s*                   Start of the line and some spaces
   //  (\S+)                  The local path
   //  \s+                    At least one space
   //  (-r\s+(\d+)\s*)?       Optional operative revision, followed by spaces
   //  (http:\/\/\S*)         A URL starting with http://
   //  \s*$                   some spaces and the end of the line
   // 
   //  @endverbatim
   ///
   static const QString OLD_EXTERNAL_REGEX    = "^\\s*(\\S+)\\s+(-r\\s+(\\d+)\\s*)?(http:\\/\\/\\S*)\\s*$";
   /// @}


}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_CONST_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

