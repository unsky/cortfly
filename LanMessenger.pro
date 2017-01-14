#-------------------------------------------------
#
# Project created by QtCreator 2012-07-11T20:58:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LanMessenger
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
    faces001/images.qrc

DISTFILES += \
    faces001/20071126092635267.png \
    faces001/20071126092635745.png \
    faces001/20071126092636691.png \
    faces001/20071126092636914.png \
    faces001/20071126092636958.png \
    faces001/20071126092637709.png \
    faces001/20071126092639637.png \
    faces001/20071126092642100.png \
    faces001/20071126092642908.png \
    faces001/20071126092643334.png \
    faces001/20071126092644738.png \
    faces001/20071126092645904.png \
    faces001/20071126092646545.png \
    faces001/20071126092647149.png \
    faces001/20071126092648288.png \
    faces001/20071126092648777.png \
    faces001/20071126092649207.png \
    faces001/20071126092651140.png \
    faces001/20071126092651678.png \
    faces001/20071126092653829.png \
    faces001/20071126092654570.png \
    faces001/20071126092654893.png \
    faces001/20071126092655547.png \
    faces001/20071126092655712.png \
    faces001/20071126092655974.png \
    faces001/20071126092656321.png \
    faces001/20071126092657386.png \
    faces001/20071126092658492.png \
    faces001/20071126092700127.png \
    faces001/20071126092700309.png \
    faces001/20071126092700381.png \
    faces001/20071126092701735.png \
    faces001/20071126092703421.png \
    faces001/20071126092703504.png \
    faces001/20071126092704237.png \
    faces001/20071126092704327.png \
    faces001/20071126092705355.png \
    faces001/20071126092705806.png \
    faces001/20071126092706446.png \
    faces001/20071126092708354.png \
    faces001/20071126092709291.png \
    faces001/20071126092709683.png \
    faces001/20071126092709701.png \
    faces001/20071126092709917.png \
    faces001/20071126092710323.png \
    faces001/20071126092711431.png \
    faces001/20071126092712143.png \
    faces001/20071126092713539.png \
    faces001/20071126092713907.png \
    faces001/20071126092713995.png \
    faces001/20071126092715908.png
