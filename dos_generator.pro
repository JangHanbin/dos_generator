TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dosgenerator.cpp \
    jpcap/calchecksum.cpp \
    jpcap/jpcaplib.cpp \
    jpcap/printdata.cpp \
    dosgenerator.cpp \
    main.cpp

HEADERS += \
    dosgenerator.h \
    jpcap/jpcaplib.h \
    jpcap/printdata.h \
    dosgenerator.h
