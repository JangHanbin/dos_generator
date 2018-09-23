TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpcap
SOURCES += main.cpp \
    dosgenerator.cpp \
    jpcap/calchecksum.cpp \
    jpcap/jpcaplib.cpp \
    jpcap/printdata.cpp \
    jpcap/ip.cpp \
    jpcap/mac.cpp \
    jpcap/getmyinfo.cpp

HEADERS += \
    dosgenerator.h \
    jpcap/jpcaplib.h \
    jpcap/printdata.h \
    dosgenerator.h \
    jpcap/calchecksum.h \
    jpcap/ip.h \
    jpcap/mac.h \
    jpcap/getmyinfo.h
