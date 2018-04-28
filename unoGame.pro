TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    deck.cpp \
    hand.cpp \
    player.cpp

HEADERS += \
    deck.hh \
    hand.hh \
    card.hh \
    player.hh
