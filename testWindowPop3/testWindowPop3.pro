#-------------------------------------------------
#
# Project created by QtCreator 2014-11-18T15:42:04
#
#-------------------------------------------------

QT       += core gui network webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testWindowPop3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    message.cpp \
    pop3.cpp \
    quotedprintable.cpp

HEADERS  += mainwindow.h \
    message.h \
    pop3.h \
    quotedprintable.h

FORMS    += mainwindow.ui
