#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T14:37:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuroTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mmpi2.cpp

HEADERS  += mainwindow.h \
    mmpi2.hpp \
    _draft.hpp

FORMS    += mainwindow.ui


macx:INCLUDEPATH += /opt/local/include
macx:LIBS += -L/opt/local/lib
macx:LIBS += -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt -lboost_thread-mt

win32:INCLUDEPATH += "C:\Qt\Tools\boost_1_55_0"
win32:LIBS += "C:\Qt\Tools\boost_1_55_0\stage\lib\libboost_regex-mgw48-mt-1_55.a"

