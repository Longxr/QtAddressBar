#-------------------------------------------------
#
# Project created by QtCreator 2018-05-28T14:34:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAddressBar
TEMPLATE = app

include(./../../Path.pri)

SOURCES += main.cpp\
        MainWindow.cpp \
    FileSystemModel.cpp \
    QtAddressBar.cpp \
    AddressItem.cpp \
    MenuWidget.cpp

HEADERS  += MainWindow.h \
    NoFocusRectStyle.h \
    FileSystemModel.h \
    QtAddressBar.h \
    AddressItem.h \
    MenuWidget.h

FORMS    += MainWindow.ui \
    MenuWidget.ui

RESOURCES += \
    res.qrc
