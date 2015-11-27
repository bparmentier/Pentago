#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T23:18:00
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PentagoClient
TEMPLATE = app

CONFIG += console c++11

SOURCES += main.cpp\
        pentagogui.cpp \
    message.cpp \
    o_sdo/sujetdobservation.cpp

HEADERS  += pentagogui.h \
    message.h \
    type.h \
    o_sdo/observateur.h \
    o_sdo/sujetdobservation.h

FORMS    += pentagogui.ui
