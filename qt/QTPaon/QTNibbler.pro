#-------------------------------------------------
#
# Project created by QtCreator 2011-03-16T14:56:36
#
#-------------------------------------------------

QT       += core gui

TARGET = QT
TEMPLATE = lib
DEFINES += QT_LIB
INCLUDEPATH += ../../nibbler/include ./include
DESTDIR = ../../exec

SOURCES += mainwindow.cpp \
    ../../nibbler/Nibbler.cpp \
    ../../nibbler/Item.cpp \
    libqt.cpp \
    graphic.cpp \
    optionwindow.cpp

DEFINES += QT_LIB

HEADERS  += mainwindow.h \
    libqt.h \
    graphic.h \
    optionwindow.h
