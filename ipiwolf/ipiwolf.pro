#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T11:36:31
#
#-------------------------------------------------

QT       += core gui printsupport widgets

TARGET = ipiwolf
TEMPLATE = app

LIBS += -lfftw3


SOURCES += main.cpp\
        mainwindow.cpp\
        point.cpp\
        resampler.cpp\
        datafile.cpp \
        qcustomplot.cpp \
    graph.cpp \
    frequencyfilter.cpp

HEADERS  += mainwindow.h\
        point.h\
        resampler.h\
        datafile.h \
        qcustomplot.h \
        graph.h \
    frequencyfilter.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
