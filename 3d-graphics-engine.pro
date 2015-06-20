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

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/openglwidget.cpp \
    src/model.cpp \
    src/framebuffer.cpp \
    src/lighting.cpp \
    src/rasterize.cpp \
    src/transform.cpp \
    src/texture.cpp \
    src/material.cpp


HEADERS  += src/mainwindow.h \
    src/openglwidget.h \
    src/model.h \
    src/framebuffer.h \
    src/lighting.h \
    src/rasterize.h \
    src/transform.h \
    src/texture.h \
    src/material.h

FORMS    += src/mainwindow.ui

UI_DIR = src
