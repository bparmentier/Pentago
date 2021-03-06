#-------------------------------------------------
#
# Project created by QtCreator 2015-11-26T21:52:19
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PentagoServer
TEMPLATE = app

CONFIG += console c++11

SOURCES += main.cpp \
    business/ball.cpp \
    business/board.cpp \
    business/gamemanager.cpp \
    business/hole.cpp \
    business/pentago.cpp \
    business/pentagoexception.cpp \
    business/player.cpp \
    Server/message.cpp \
    Server/pentagoserver.cpp \
    Server/threadmanager.cpp \
    Server/dialog.cpp

HEADERS  += \
    business/ball.h \
    business/ballcolor.h \
    business/board.h \
    business/direction.h \
    business/gamemanager.h \
    business/hole.h \
    business/pentago.h \
    business/pentagoexception.h \
    business/player.h \
    Server/message.h \
    Server/pentagoserver.h \
    Server/type.h \
    Server/threadmanager.h \
    Server/playercolor.h \
    business/actiongame.h \
    Server/dialog.h

FORMS += \
    Server/dialog.ui

