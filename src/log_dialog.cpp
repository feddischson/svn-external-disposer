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
#include <QDebug>

#include "log_dialog.h"

namespace SVN_EXTERNALS_DISPOSER
{

Log_Dialog::Log_Dialog( QWidget *parent  ) : QDialog( parent )
{
   ui.setupUi(this);
   ui.log_TW->setRowCount(10);
   ui.log_TW->setColumnCount(3);
   ui.log_TW->setItem(0, 1, new QTableWidgetItem("Hello"));
   QHeaderView * view = ui.log_TW->horizontalHeader();
   view->setSectionResizeMode(QHeaderView::Stretch);
}



void Log_Dialog::on_load_more_PB_clicked( void )
{
   qDebug() << "should load more";
}



Log_Dialog::operator QString()
{
   QString s;
   QTextStream ts(&s);
   ts  << "Log_Dialog ("  << reinterpret_cast< void* >( this ) << "): "
       << "TODO=" << "Add more content of this instance here @ " 
       << __FILE__ << ":" << __LINE__;
   return s;
}


}; // namespace SVN_EXTERNALS_DISPOSER

// vim: filetype=cpp et ts=3 sw=3 sts=3

