#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T22:07:22
#
#-------------------------------------------------

QT       += core opengl gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AttractorVisualizer
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
    src/main.cpp \
    src/GUI/Windows/mainwindow.cpp \
    src/Opengl/camera.cpp \
    src/GUI/Boxes/valueinputbox.cpp \
    src/GUI/Boxes/doublevalueinputbox.cpp \
    src/GUI/Boxes/flagsetbox.cpp \
    src/GUI/Boxes/valueslidebox.cpp \
    src/GUI/Boxes/doublevalueslidebox.cpp \
    src/GUI/Panels/trajpanel.cpp \
    src/GUI/Boxes/valueoutputbox.cpp \
    src/GUI/Boxes/openfilebox.cpp \
    src/GUI/Boxes/colorselectbox.cpp \
    src/Opengl/traj.cpp \
    src/Opengl/trajscene.cpp \
    src/GUI/Panels/trajsettingspanel.cpp \
    src/GUI/Windows/addtrajwindow.cpp

HEADERS += \
    src/GUI/Windows/mainwindow.hpp \
    src/Opengl/camera.hpp \
    src/GUI/Boxes/valueinputbox.hpp \
    src/GUI/Boxes/doublevalueinputbox.hpp \
    src/GUI/Boxes/flagsetbox.hpp \
    src/GUI/Boxes/valueslidebox.hpp \
    src/GUI/Boxes/doublevalueslidebox.hpp \
    src/GUI/Panels/trajpanel.hpp \
    src/GUI/Boxes/valueoutputbox.hpp \
    src/GUI/Boxes/openfilebox.hpp \
    src/GUI/Boxes/colorselectbox.hpp \
    src/Opengl/traj.hpp \
    src/Opengl/trajscene.hpp \
    src/GUI/Panels/trajsettingspanel.hpp \
    src/GUI/Windows/addtrajwindow.hpp

DISTFILES += \
    src/Opengl/Shaders/fragment_shader.glsl \
    src/Opengl/Shaders/vertex_shader.glsl

RESOURCES += \
    shaders.qrc
