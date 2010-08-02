# -------------------------------------------------
# Project created by QtCreator 2009-05-13T07:23:53
# -------------------------------------------------
TARGET = finace-account
DESTDIR = $(HOME)/bin
DEFINES += DEBUG
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    ../account.cpp \
    ../record.cpp \
    ../basefunction.cpp \
    addrecorddlg.cpp \
    analysisDlg.cpp \
    createaccountdlg.cpp \
    accountuser.cpp
HEADERS += mainwindow.h \
    ../record.h \
    ../basefunction.h \
    ../account.h \
    addrecorddlg.h \
    analysisDlg.h \
    createaccountdlg.h \
    accountuser.h
FORMS += addrecorddlg.ui \
    createaccountdlg.ui
OTHER_FILES += 
CONFIG += debug \
    warn_on \
    qt
