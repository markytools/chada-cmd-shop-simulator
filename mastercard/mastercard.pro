#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T11:56:33
#
#-------------------------------------------------

QT       -= core gui

TARGET = mastercard
TEMPLATE = lib

DEFINES += MASTERCARD_LIBRARY

SOURCES += mastercard.cpp

HEADERS += mastercard.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
