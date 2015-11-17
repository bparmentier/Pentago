TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    plateau.cpp \
    bille.cpp \
    trou.cpp \
    gestionnairejoueur.cpp \
    joueur.cpp \
    pentago.cpp \
    pentagoexception.cpp \
    o_sdo/sujetdobservation.cpp

HEADERS += \
    plateau.h \
    bille.h \
    trou.h \
    gestionnairejoueur.h \
    joueur.h \
    pentago.h \
    type.h \
    pentagoexception.h \
    o_sdo/observateur.h \
    o_sdo/sujetdobservation.h

