#-------------------------------------------------
#
# Project created by QtCreator 2023-12-24T22:44:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = planer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    secondwindow.cpp \
    thirdwindow.cpp \
    fourwindow.cpp

HEADERS += \
        mainwindow.h \
    secondwindow.h \
    thirdwindow.h \
    fourwindow.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui \
    secondwindow.ui \
    thirdwindow.ui \
    fourwindow.ui

RESOURCES += \
    img_res.qrc \
    qrs.qrc \
    recurse.qrc \
    res.qrc

DISTFILES += \
    style.css \
    stylesheet.css
