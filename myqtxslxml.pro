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
    myxslttemplates.cpp \
    mylist.cpp \
    mycoursexml.cpp


HEADERS += \
    myxml.h \
    myxslttemplates.h \
    mylist.h \
    mycoursexml.h

RESOURCES += \
    Resources/Resources.qrc

# new shit begin
message(Copy $$PWD/runtimeFiles to $$OUT_PWD)

win32{
PWD_WIN = $${PWD}
DESTDIR_WIN = $${OUT_PWD}\\debug
PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

copydata.commands   = $$quote(cmd /c xcopy /y /f /i /E $${PWD_WIN}\\runtimeFiles $${DESTDIR_WIN}\\runtimeFiles)
copydata22.commands = $$quote(cmd /c xcopy /y /f /i /E $${PWD_WIN}\\runtimeFiles $${DESTDIR_WIN}\\Resources)

message(XCopy /E /Y  $$PWD_WIN\\runtimeFiles to $$DESTDIR_WIN)

first.depends = $(first)  copydata copydata22
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += copydata copydata22
POST_TARGETDEPS += copydata copydata22
}

THISWORKDS_win32{
#COPY_DIR=xcopy
# xcopy /E \"..\i-clicker-7\resources\Deployment\CommonFiles\*\" \"..\Deploy\\$$FOLDERNAME\.\"

#COPY_DIR="XCOPY /E"
 #"xcopy /E"
 #xcopy /E  $$PWD/Resources    $$OUT_PWD

PWD_WIN = $${PWD}
DESTDIR_WIN = $${OUT_PWD}\\debug
PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

#copydata22.commands =system($$COPY_DIR $$PWD/Resources $$OUT_PWD)
#copydataFUCK.commands = $(COPY_DIR)  \"$${PWD_WIN}\\runtimeFiles\" \"$${DESTDIR_WIN}"
copyfiles.commands = $$quote(cmd /c xcopy /y /f /i /E $${PWD_WIN}\\runtimeFiles $${DESTDIR_WIN}\\runtimeFiles)

message(XCopy /E /Y  $$PWD_WIN\\runtimeFiles to $$DESTDIR_WIN)

#first.depends = $(first) copydataFUCK
#export(first.depends)
#export(copydataFUCK.commands)
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
}


COPY_DIR=cp
unix{
copydata22.commands = $(COPY_DIR) $$PWD/Resources $$OUT_PWD
copydata.commands = $(COPY_DIR) $$PWD/runtimeFiles $$OUT_PWD
first.depends = $(first) copydata copydata22
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata copydata22
}
# new shit end

OTHER_FILES += \
    runtimeFiles/bobo.txt \
    runtimeFiles/ListManifest.xslt \
    runtimeFiles/maniifest.xml \
    runtimeFiles/manifest.xml \
    runtimeFiles/xml2csv101.xsl \
    runtimeFiles/listxml2csv101.xsl
