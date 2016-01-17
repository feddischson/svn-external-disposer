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
//

#include <QDebug>
#include <QFileInfo>

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

    QString path = "";
    if( argc > 1 )
      path =  QFileInfo( argv[1] ).absoluteDir().absolutePath();

    Main_Window w(path);
    w.show();
    return app.exec();
}
