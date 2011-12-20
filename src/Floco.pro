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
    databasemanager.cpp \
    addplayerdlg.cpp \
    playerstab.cpp

HEADERS  += mainwindow.h \
    databasemanager.h \
    addplayerdlg.h \
    playerstab.h

FORMS    += ui/mainwindow.ui \
    ui/addplayerdlg.ui \
    ui/playerstab.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    db.sql
