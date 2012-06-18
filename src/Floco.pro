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
    attendancetab.cpp \
    editcategoriesdlg.cpp \
    addcategorydlg.cpp \
    models/categorymodel.cpp \
    models/playermodel.cpp \
    widget/filtredit.cpp \
    addtrainingdlg.cpp \
    models/teammodel.cpp \
    models/trainingmodel.cpp \
    playerdetails.cpp \
    recordattendancedlg.cpp \
    models/attendancemodel.cpp \
    models/attendancematrixmodel.cpp \
    tournamentstab.cpp \
    addtournamentdlg.cpp \
    models/tournamentmodel.cpp

HEADERS  += mainwindow.h \
    databasemanager.h \
    addplayerdlg.h \
    playerstab.h \
    teamstab.h \
    addteamdlg.h \
    trainingstab.h \
    attendancetab.h \
    editcategoriesdlg.h \
    addcategorydlg.h \
    models/categorymodel.h \
    models/playermodel.h \
    widget/filtredit.h \
    addtrainingdlg.h \
    models/teammodel.h \
    models/trainingmodel.h \
    playerdetails.h \
    recordattendancedlg.h \
    models/attendancemodel.h \
    models/attendancematrixmodel.h \
    tournamentstab.h \
    addtournamentdlg.h \
    models/tournamentmodel.h

FORMS    += ui/mainwindow.ui \
    ui/addplayerdlg.ui \
    ui/playerstab.ui \
    ui/teamstab.ui \
    ui/addteamdlg.ui \
    ui/trainingstab.ui \
    ui/attendancetab.ui \
    ui/editcategoriesdlg.ui \
    ui/addcategorydlg.ui \
    ui/addtrainingdlg.ui \
    ui/playerdetails.ui \
    ui/recordattendancedlg.ui \
    ui/tournamentstab.ui \
    ui/addtournamentdlg.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    db.sql
