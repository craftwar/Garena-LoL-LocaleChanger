#-------------------------------------------------
#
# Project created by QtCreator 2013-02-06T10:58:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = LoLTW_to_English
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:LIBS += -lKernel32
