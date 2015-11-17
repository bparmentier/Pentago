TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pentago.cpp \
    pentagoexception.cpp \
    o_sdo/sujetdobservation.cpp \
    board.cpp \
    gamemanager.cpp \
    player.cpp \
    hole.cpp \
    ball.cpp

HEADERS += \
    pentago.h \
    type.h \
    pentagoexception.h \
    o_sdo/observateur.h \
    o_sdo/sujetdobservation.h \
    board.h \
    gamemanager.h \
    player.h \
    hole.h \
    ball.h

