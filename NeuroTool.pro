#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T14:37:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuroTool
TEMPLATE = app

SOURCES +=  main.cpp\
            mainwindow.cpp \
            mmpi2.cpp \
            mmpi2_window.cpp \
            waisr.cpp \
            waisr_window.cpp

HEADERS +=  mainwindow.h \
            mmpi2.hpp \
            _draft.hpp \
            waisr.hpp

FORMS    += mainwindow.ui

macx:ICON = $${PWD}/ico.icns
macx:QMAKE_INFO_PLIST = info.plist
macx:OTHER_FILES += info.plist
macx:INCLUDEPATH += /opt/local/include
macx:LIBS += -L/opt/local/lib
macx:LIBS += -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt -lboost_thread-mt

win32:RC_FILE = app.rc
win32:INCLUDEPATH += "C:\Qt\Tools\boost_1_55_0"
win32:LIBS += "C:\Qt\Tools\boost_1_55_0\stage\lib\libboost_regex-mgw48-mt-1_55.a"

# unix: ICON = $${PWD}/ico.icns
unix: INCLUDEPATH += -I/usr/include
unix: LIBS += -L/usr/lib64
unix: LIBS += -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt -lboost_thread-mt

# other way:
# unix {
# INCLUDEPATH += ./fwefwef
# }


# hdiutil create -format UDBZ -quiet -srcfolder NeuroTool.app NeuroTool.dmg
