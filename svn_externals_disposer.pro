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

HEADERS     += include/const.h
HEADERS     += include/mainwindow.h
HEADERS     += include/data_model.h
SOURCES     += src/main.cpp
SOURCES     += src/mainwindow.cpp
SOURCES     += src/data_model.cpp


target.path = /usr/local/bin
INSTALLS += target
