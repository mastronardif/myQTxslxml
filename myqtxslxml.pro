#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T17:59:29
#
#-------------------------------------------------

QT       += core
QT       += xml
QT += xmlpatterns
QT       -= gui



TARGET = myqtxslxml
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myxml.cpp \
    myxslttemplates.cpp


HEADERS += \
    myxml.h \
    myxslttemplates.h

RESOURCES += \
    Resources/Resources.qrc
