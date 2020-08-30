QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

unix:INCLUDEPATH += /usr/local/lib
unix:INCLUDEPATH += /usr/lib

unix:LIBS += `pkg-config opencv4 --cflags --libs`
unix:LIBS += -L/usr/lib
unix:LIBS += -L/usr/local/lib

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

SOURCES += main.cpp \
    diff_and_error.cpp \
    histogram.cpp \
    sgbm.cpp \
    stereoalgo.cpp

SUBDIRS += \
    Test_No_GUI.pro

DISTFILES += \
    Test_No_GUI.pro.user

HEADERS += \
    diff_and_error.h \
    histogram.h \
    sgbm.h \
    stereoalgo.h
