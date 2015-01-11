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
    imageconversion.cpp \
    cameraconnectdialog.cpp

HEADERS  += mainwindow.h \
    imageconversion.h \
    cameraconnectdialog.h

FORMS    += mainwindow.ui \
    cameraconnectdialog.ui

LIBS    += `pkg-config opencv --libs`

DISTFILES += \
    README.md
