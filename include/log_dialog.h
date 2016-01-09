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
   explicit Log_Dialog( QWidget *parent = nullptr );


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

private:

   /// @brief UI instance, created from forms/LogDialog.ui.
   Ui::Dialog ui;



private slots:

   /// @brief
   void on_load_more_PB_clicked( void );


}; // class Log_Dialog

}; // namespace SVN_EXTERNALS_DISPOSER

#endif // _SVN_EXTERNALS_DISPOSER_LOG_DIALOG_H 

// vim: filetype=cpp et ts=3 sw=3 sts=3

