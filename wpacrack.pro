#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T19:58:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wpacrack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calchash.cpp \
    calcproc.cpp \
    keybox.cpp

HEADERS  += mainwindow.h \
    calchash.h \
    calcproc.h \
    keybox.h \
    common.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/../../../../../OpenSSL-Win32/lib/MinGW/ -leay32

INCLUDEPATH += $$PWD/../../../../../OpenSSL-Win32/include
DEPENDPATH += $$PWD/../../../../../OpenSSL-Win32/include
