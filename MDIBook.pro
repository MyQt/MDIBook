#-------------------------------------------------
#
# Project created by QtCreator 2014-07-28T11:12:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MDIBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    notebook.cpp \
    highlighter.cpp

HEADERS  += mainwindow.h \
    notebook.h \
    highlighter.h

FORMS    += mainwindow.ui
