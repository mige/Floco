#-------------------------------------------------
#
# Project created by QtCreator 2011-09-01T13:57:17
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Floco
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp

HEADERS  += mainwindow.h \
    databasemanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    db.sql
