#-------------------------------------------------
#
# Project created by QtCreator 2020-07-08T00:23:25
#
#-------------------------------------------------
QT       += core gui multimedia multimediawidgets
QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RLSB
TEMPLATE = app


SOURCES += main.cpp\
    info.cpp \
    loginwidget.cpp \
        mainwindow.cpp \
    kaoqin.cpp \
    teacher.cpp \
    JasonQt_Net.cpp \
    jasonqt_face.cpp

HEADERS  += mainwindow.h \
    info.h \
    kaoqin.h \
    loginwidget.h \
    teacher.h \
    JasonQt_Net.h \#链接百度AI相关函数封装
    jasonqt_face.h

FORMS    += mainwindow.ui \
    info.ui \
    kaoqin.ui \
    loginwidget.ui \
    teacher.ui

RESOURCES += \
    pic.qrc
    
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
