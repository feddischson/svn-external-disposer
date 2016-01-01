TEMPLATE = app
TARGET = test_svn_externals_disposer
INCLUDEPATH += ./include ./test
DEPENDPATH += . include src test

QMAKE_CXXFLAGS += -Werror # set -werror
QMAKE_CXXFLAGS += -Wextra # set -wextra
CONFIG += warn_on         # 
CONFIG += c++11           # set -std=c++0x
CONFIG += testcase        # enable test-cases for make
CONFIG += debug


QT          += widgets
QT          += xml
QT          += core
QT          += testlib

DEFINES += TESTING

HEADERS     += include/const.h
HEADERS     += include/external.h
HEADERS     += test/test_external.h
SOURCES     += src/external.cpp
SOURCES     += test/test_external.cpp
SOURCES     += test/main.cpp

VERSION = "0.1.0"
DEFINES += _APP_VERSION=\\\"$$VERSION\\\"

