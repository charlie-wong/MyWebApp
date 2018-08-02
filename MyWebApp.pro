# Dependent on 'QtWebApp'
#
# http://www.stefanfrings.de/qtwebapp/

QT  += core
QT  -= gui
QT  += network

TARGET = MyWebApp

CONFIG += debug

CONFIG   += console c++11

TEMPLATE = app

SOURCES += src/main.cpp \
    src/helloworldcontroller.cpp \
    src/listdatacontroller.cpp \
    src/requestmapper.cpp \
    src/logincontroller.cpp \
    src/cookietestcontroller.cpp \
    src/unicodecontroller.cpp \
    src/datatemplatecontroller.cpp

HEADERS += \
    src/helloworldcontroller.h \
    src/listdatacontroller.h \
    src/requestmapper.h \
    src/logincontroller.h \
    src/cookietestcontroller.h \
    src/unicodecontroller.h \
    src/datatemplatecontroller.h

OTHER_FILES += etc/webapp.ini

include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)
include(../QtWebApp/QtWebApp/templateengine/templateengine.pri)
include(../QtWebApp/QtWebApp/logging/logging.pri)
