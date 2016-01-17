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
#include <QColor>

namespace SVN_EXTERNALS_DISPOSER
{

   /// @defgroup app_const  Application naming constants
   /// @{
   static const QString APP_VERSION          = _APP_VERSION;
   static const QString APP_NAME             = "SVN-Externals-Disposer";
   static const QString ORGANIZATION_NAME    = "SVN-Externals-Disposer";
   static const QString ORGANIZATION_DOMAIN  = "SVN.Externals.Disposer";
   /// @}

   /// @defgroup xml_const  XML string constants
   /// Used to extract data from the xml output of svn propget --xml
   /// @{
   static const QString XML_NAME_TARGET   = "target"; 
   static const QString XML_NAME_PROPERTY = "property";
   static const QString XML_NAME_PATH     = "path";
   static const QString XML_NAME_LOG      = "log";
   static const QString XML_NAME_LOGENTRY = "logentry";
   static const QString XML_NAME_MSG      = "msg";
   static const QString XML_NAME_REVISION = "revision";
   static const QString XML_NAME_DATE     = "date";
   static const QString XML_NAME_AUTHOR   = "author";
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
   static const QString SVN_LOG           = "log";
   static const QString SVN_LIMIT         = "-l";
   static const QString SVN_ALL_REVPROPS  = "--with-all-revprops";
   static const QString SVN_ERR_AUTH      = "E215004";
   static const QString SVN_USER          = "--username";
   static const QString SVN_PASS          = "--password";
   static const QString SVN_REVISION      = "-r";
   /// @}

   /// @brief Number of svn log entries 
   //         which are initially and by pressing the next button loaded.
   static const int SVN_N_LOAD            = 200;

   /// @brief Number of authentication trials
   static const int SVN_MAX_AUTH_TRIALS = 3;

   /// @defgroup sys_const  System constants
   /// 
   /// @{

   /// @brief The timeout, which is used in QProcess for system calls.
   static const qint32  SYS_PROCESS_TIMEOUT = 3000; 
   /// @}



   /// @defgroup table_cols Table Column constants
   /// Used to select and idendify columns
   /// @{
   static const quint32 LOGDIALOG_REVISION_COLUMN     = 0;
   /// @}


   /// @defgroup set_const  QSetting string constants
   /// Used to load/store QSettings.
   /// @{
   static const QString SET_FILE          = "/settings.ini";
   static const QString SET_CP_PATH       = "working_cp_path";
   static const QString SET_COLUMN        = "column_width";
   static const QString SET_COLUMN_W      = "column_width_val";
   static const QString SET_USERNAMES     = "usernames";
   static const QString SET_LASTNAME      = "lastname";
   static const QString SET_USERNAME      = "username";
   static const QString SET_SELECT        = "select_state";
   static const QString SET_WINDOW_SIZE   = "mainwindow_size";
   /// @}


   /// @defgroup gui_const  GUI string constants
   /// String constants used within the GUI.
   /// @{
   static const QString GUI_HEAD_TARGET       = QObject::tr( "Target"             );
   static const QString GUI_HEAD_EXTERNAL     = QObject::tr( "URL"                );
   static const QString GUI_HEAD_PEG          = QObject::tr( "Peg Revision"       );
   static const QString GUI_HEAD_OPERATIVE    = QObject::tr( "Operative Revision" );
   static const QString GUI_HEAD_PATH         = QObject::tr( "Defined at"         );
   static const QString GUI_HEAD_REVISION     = QObject::tr( "Revision"           );
   static const QString GUI_HEAD_AUTHOR       = QObject::tr( "Author"             );
   static const QString GUI_HEAD_MESSAGE      = QObject::tr( "Message"            );
   static const QString GUI_HEAD_DATE         = QObject::tr( "Date"               );
   /// @}

   /// @brief The background color for modified svn:externals entries
   static const QColor COL_MODIFIED          = Qt::yellow;

   /// @brief The background color for unmodified svn:externals entries
   static const QColor COL_NOT_MODIFIED      = Qt::white;

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

