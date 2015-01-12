#-------------------------------------------------
#
# Project created by QtCreator 2015-01-09T16:51:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ADRA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cameraconnectdialog.cpp \
    camerawindow.cpp \
    camerathread.cpp \
    videostats.cpp \
    imageprocessing.cpp

HEADERS  += mainwindow.h \
    cameraconnectdialog.h \
    camerawindow.h \
    camerathread.h \
    videostats.h \
    imageprocessing.h

FORMS    += mainwindow.ui \
    cameraconnectdialog.ui \
    camerawindow.ui

LIBS    += `pkg-config opencv --libs`

DISTFILES += \
    README.md
