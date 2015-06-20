#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T19:21:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3d-graphics-engine
TEMPLATE = app

LIBS   += -lGL -lGLU -lglut -lIL
CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    openglwidget.cpp \
    model.cpp \
    framebuffer.cpp \
    lighting.cpp \
    rasterize.cpp \
    transform.cpp \
    texture.cpp \
    material.cpp


HEADERS  += mainwindow.h \
    openglwidget.h \
    model.h \
    framebuffer.h \
    lighting.h \
    rasterize.h \
    transform.h \
    texture.h \
    material.h

FORMS    += mainwindow.ui
