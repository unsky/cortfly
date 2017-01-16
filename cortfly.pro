#-------------------------------------------------
#
# Project created by QtCreator 2012-07-11T20:58:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cortfly
TEMPLATE = app

CONFIG += release
QMAKE_CXXFLAGS += -std=c++0x

# STATIC LINKING
CONFIG += static
QMAKE_CXXFLAGS += -static -static-libgcc -static-libstdc++
QMAKE_LFLAGS   += -static -static-libgcc -static-libstdc++

SOURCES += main.cpp\
        mainwindow.cpp \
    dialognickname.cpp \
    messenger.cpp \
    peer.cpp \
    pmwindow.cpp \
    tcpclient.cpp \
    tcpserver.cpp

HEADERS  += mainwindow.h \
    dialognickname.h \
    messenger.h \
    peer.h \
    pmwindow.h \
    tcpclient.h \
    tcpserver.h

FORMS    += mainwindow.ui \
    dialognickname.ui \
    pmwindow.ui \
    tcpclient.ui \
    tcpserver.ui

RESOURCES += \
    images/image.qrc
