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
//

#include <QDebug>
#include <QFileInfo>
#include <QProcess>
#include <QMessageBox>

#include "mainwindow.h"
#include "const.h"

using namespace SVN_EXTERNALS_DISPOSER;
int main( int argc, char *argv[] )
{
   QCoreApplication::setOrganizationName( ORGANIZATION_NAME );
   QCoreApplication::setOrganizationDomain( ORGANIZATION_DOMAIN );
   QCoreApplication::setApplicationName( APP_NAME );
   QCoreApplication::setApplicationVersion( APP_VERSION );
   QApplication app(argc, argv);


   // ensure, that svn is available
   QProcess process;
   process.start( SVN_CMD, QStringList() << SVN_VERSION );
   if( process.waitForFinished( SYS_PROCESS_TIMEOUT ) && 
       process.exitCode() == 0 ) // wait 3 seconds
   {
      QString path = "";
      if( argc > 1 )
        path =  QFileInfo( argv[1] ).absoluteDir().absolutePath();

      Main_Window w(path);
      w.show();
      return app.exec();
   }
   else
   {
      QMessageBox * m = new QMessageBox( );
      m->setText( "Failed to start: no svn available in your system environment" );
      m->setDetailedText( "Please check your system environment and install \
                           the svn command-line too. You can test your environment \
                           by executing `svn --version`, which should give you the \
                           installed svn version." );

      m->show();
      return app.exec();
   }
}
