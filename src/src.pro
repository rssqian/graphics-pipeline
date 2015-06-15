######################################################################
# Automatically generated by qmake (3.0) Sat Jun 13 21:12:15 2015
######################################################################

TEMPLATE = app
TARGET = src
INCLUDEPATH += . model pipeline ui

# Input
HEADERS += mainwindow.h \
           openglwidget.h \
           ui_mainwindow.h \
           model/model.h \
           pipeline/framebuffer.h \
           pipeline/lighting.h \
           pipeline/rasterize.h \
           pipeline/transform.h \
           ui/ui.h
FORMS += ui/mainwindow.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           openglwidget.cpp \
           model/model.cpp \
           pipeline/framebuffer.cpp \
           pipeline/lighting.cpp \
           pipeline/rasterize.cpp \
           pipeline/transform.cpp \
           ui/ui.cpp
