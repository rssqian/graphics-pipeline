#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T19:21:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3d-graphics-engine
TEMPLATE = app

LIBS   += -lGL -lGLU -lglut
CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    openglwidget.cpp \
    model/model.cpp \
    pipeline/framebuffer.cpp \
    pipeline/lighting.cpp \
    pipeline/rasterize.cpp \
    pipeline/transform.cpp


HEADERS  += mainwindow.h \
    openglwidget.h \
    model/model.h \
    pipeline/framebuffer.h \
    pipeline/lighting.h \
    pipeline/rasterize.h \
    pipeline/transform.h \

FORMS    += ui/mainwindow.ui
