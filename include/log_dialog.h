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
#ifndef _SVN_EXTERNALS_DISPOSER_LOG_DIALOG_H 
#define _SVN_EXTERNALS_DISPOSER_LOG_DIALOG_H
#include <QObject>
#include <QTextStream>
#include <QDialog>
#include <QProcess>

#include "const.h"
#include "ui_LogDialog.h"

namespace SVN_EXTERNALS_DISPOSER
{


/// @author feddischson
/// @brief Template class
class Log_Dialog : public QDialog
{

   Q_OBJECT
public:

   /// @brief Ctor: not implemented!
   explicit Log_Dialog( 
         const QString & working_cp_path, 
         QWidget *parent = nullptr );


   /// @brief  Copy ctor: not implemented!
   Log_Dialog(const Log_Dialog & aLog_Dialog) = delete;


   /// @brief  Assignment operator: not implemented!
   Log_Dialog& operator= (const Log_Dialog & aLog_Dialog) = delete;


   /// @brief  Move constructor: not implemented!
   Log_Dialog( Log_Dialog && rhs ) = delete;


   /// @brief  Move assignment operator: not implemented!
   Log_Dialog& operator=( Log_Dialog && rhs ) = delete;


   /// @brief Standard dtor
   ~Log_Dialog() = default;


   /// @brief QSTring operator, to print data to qDebug()
   virtual operator QString();

   // @brief Returns the selected revision.
   QVariant get_revision( void );


   // @brief loads the initial log via `load_svn_log`.
   bool load( void );

private:

   /// @brief Runs `svn log --xml .... `, extracts the XML result and
   //         adds SVN_Log entries into log_list.
   /// 
   bool load_svn_log(
         quint64 to        = std::numeric_limits< quint64 >::max(),
         quint64 n_or_from = SVN_N_LOAD,
         bool    is_range  = false,
         bool    append    = true );


   /// @brief Checks if there are new entries in the log-list.
   ///         If there are new entries, they are added to the table widget.
   ///
   void update_table( bool clear = false );


   /// @brief Log entry containing all necessary elements of a log entry.
   /// @details
   ///      This includes
   ///         - Revision
   ///         - Author
   ///         - Commit Message
   ///         - Date
   struct SVN_Log
   {
      SVN_Log( 
            const QString revision, 
            const QString & author,
            const QString & message,
            const QString & date ) :
         rev( revision.toULong() ),
         revision( revision ),
         author( author ),
         message( message ),
         date( date )
      {}
      quint64 rev;
      QString revision;
      QString author;
      QString message;
      QString date;
      operator QString()
      {
         return author + ";" + date + ";" + revision + ";" + message;
      }
   };

   /// @brief Internal storage to store the `svn log --xml .... ` result.
   QList< SVN_Log > log_list;

   /// @brief The path where `svn log --xml ...` is executed.
   QString working_cp_path;

   /// @brief UI instance, created from forms/LogDialog.ui.
   Ui::LogDialog ui;

   /// @brief Falg to remember, if there was already once selected a row.
   bool was_selected;

private slots:

   /// @brief Handler for the next_PB push button.
   void on_next_PB_clicked( void );

   /// @brief Handler for the load_PB push button.
   void on_load_PB_clicked( void );


}; // class Log_Dialog

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_LOG_DIALOG_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

