TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QMAKE_CXXFLAGS += -lcurl -std=c++11

LIBS += -lcurl

SOURCES += main.cpp \
    urltree.cpp \
    program_logic.cpp \
    programstatus.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    urltree.h \
    url_util.h \
    program_logic.h \
    t_ops.h \
    scan_task.h

