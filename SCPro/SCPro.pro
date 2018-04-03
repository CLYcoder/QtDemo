#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T09:28:59
#
#-------------------------------------------------

QT       += core gui network
CONFIG += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = SCProEmbedded

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    define.cpp \
    frmmain.cpp \
    clientwidget.cpp \
    formtimesource.cpp \
    formclients.cpp \
    formcard.cpp \
    cardinfogroup.cpp \
    timesourcegroup.cpp \
    shutdownbutton.cpp \
    scrolltextshow.cpp \
    formstartup.cpp \
    analogclock.cpp

HEADERS  += frmmain.h \
    define.h \
    clientwidget.h \
    formtimesource.h \
    formclients.h \
    formcard.h \
    cardinfogroup.h \
    timesourcegroup.h \
    shutdownbutton.h \
    scrolltextshow.h \
    formstartup.h \
    analogclock.h \
    packmanage.h \
    data.h

FORMS    += frmmain.ui \
    clientwidget.ui \
    formtimesource.ui \
    formcard.ui \
    formstartup.ui

# 添加qwt控件支持
#INCLUDEPATH += $$PWD/qwt/include

#CONFIG(debug,debug|release ){
#LIBS += $$PWD/qwt/libqwtd.a
#}else{
#LIBS += $$PWD/qwt/libqwt.a
#}

RESOURCES += \
    resource.qrc

DISTFILES +=

# 程序图标
RC_FILE +=
