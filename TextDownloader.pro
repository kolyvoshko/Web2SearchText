#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T22:26:10
#
#-------------------------------------------------

CONFIG   += c++11
QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -lcurl -std=c++11

LIBS += -lcurl

TARGET = TextDownloader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Logic/program_logic.cpp \
    Logic/urltree.cpp

HEADERS  += mainwindow.h \
    Logic/program_logic.h \
    Logic/t_ops.h \
    Logic/url_util.h \
    Logic/urltree.h \
    Logic/scan_task.h \
    sync_thread.h

FORMS    += mainwindow.ui
