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

# new shit begin
message(Copy $$PWD/runtimeFiles to $$OUT_PWD)
COPY_DIR = cp
copydata22.commands = $(COPY_DIR) $$PWD/Resources $$OUT_PWD
copydata.commands = $(COPY_DIR) $$PWD/runtimeFiles $$OUT_PWD
first.depends = $(first) copydata copydata22
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata copydata22

# new shit end
