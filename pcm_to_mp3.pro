#-------------------------------------------------
#
# Project created by QtCreator 2018-08-02T13:38:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pcm_to_mp3
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
        dialog.cpp \
    lib/lameHelper.cpp \
    lib/wholeminute.cpp

HEADERS += \
        dialog.h \
    lib/lame.h \
    lib/lameHelper.h \
    lib/wholeminute.h

FORMS += \
        dialog.ui


#RC_FILE=main.rc

LIBS+= C:\Users\furunhao\Documents\FRH\Software\DGN_AC32_decode\pcm_to_mp3\lib\libmp3lame.lib

DISTFILES += \
    lib/libmp3lame.lib
