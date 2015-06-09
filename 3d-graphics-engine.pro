#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T19:21:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3d-graphics-engine
TEMPLATE = app

LIBS   += -lGL -lGLU
CONFIG += c++11

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/model/model.cpp \
    src/pipeline/framebuffer.cpp \
    src/pipeline/lighting.cpp \
    src/pipeline/rasterize.cpp \
    src/pipeline/transform.cpp \
    openglwidget.cpp

HEADERS  += mainwindow.h \
    src/model/model.h \
    src/pipeline/framebuffer.h \
    src/pipeline/lighting.h \
    src/pipeline/rasterize.h \
    src/pipeline/transform.h \
    openglwidget.h

FORMS    += src/ui/mainwindow.ui
