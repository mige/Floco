#-------------------------------------------------
#
# Project created by QtCreator 2011-09-01T13:57:17
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Floco
TEMPLATE = app

TRANSLATIONS = ts/cs_CZ.ts
CODECFORTR = UTF-8

SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp \
    addplayerdlg.cpp \
    playerstab.cpp \
    teamstab.cpp \
    addteamdlg.cpp \
    trainingstab.cpp \
    attendancetab.cpp

HEADERS  += mainwindow.h \
    databasemanager.h \
    addplayerdlg.h \
    playerstab.h \
    teamstab.h \
    addteamdlg.h \
    trainingstab.h \
    attendancetab.h

FORMS    += ui/mainwindow.ui \
    ui/addplayerdlg.ui \
    ui/playerstab.ui \
    ui/teamstab.ui \
    ui/addteamdlg.ui \
    ui/trainingstab.ui \
    ui/attendancetab.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    db.sql
