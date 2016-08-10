TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDEPATH += /usr/lib/

SOURCES += main.cpp

CONFIG += c++11

HEADERS += \
    Libs/bTreeView.h \
    Headers/Node.h \
    Headers/Tree.h \
    Libs/Player.h

