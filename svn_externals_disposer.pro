TEMPLATE = app
TARGET = svn_externals_disposer
INCLUDEPATH += ./include
DEPENDPATH += . forms include src


QMAKE_CXXFLAGS += -Werror # set -werror
QMAKE_CXXFLAGS += -Wextra # set -wextra
CONFIG += warn_on         # 
CONFIG += c++11           # set -std=c++0x

QT          += widgets
QT          += xml
QT          += core

FORMS += forms/MainWindow.ui
FORMS += forms/LogDialog.ui

HEADERS     += include/const.h
HEADERS     += include/mainwindow.h
HEADERS     += include/data_model.h
HEADERS     += include/external.h
HEADERS     += include/tree_view.h
HEADERS     += include/external_command.h
HEADERS     += include/log_dialog.h
SOURCES     += src/main.cpp
SOURCES     += src/mainwindow.cpp
SOURCES     += src/data_model.cpp
SOURCES     += src/external.cpp
SOURCES     += src/tree_view.cpp
SOURCES     += src/external_command.cpp
SOURCES     += src/log_dialog.cpp

VERSION = "0.1.0"
DEFINES += _APP_VERSION=\\\"$$VERSION\\\"

target.path = /usr/local/bin
INSTALLS += target
