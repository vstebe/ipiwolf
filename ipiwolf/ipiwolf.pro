#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T11:36:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ipiwolf
TEMPLATE = app

LIBS += -lfftw3


SOURCES += main.cpp\
        mainwindow.cpp\
        point.cpp\
        resampler.cpp\
        datafile.cpp

HEADERS  += mainwindow.h\
        point.h\
        resampler.h\
        datafile.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
