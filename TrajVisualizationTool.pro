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

CONFIG += exception

SOURCES += \
    src/main.cpp \
    src/gui/boxes/doublevalueinputbox.cpp \
    src/gui/boxes/doublevalueslidebox.cpp \
    src/gui/boxes/openfilebox.cpp \
    src/gui/boxes/colorselectbox.cpp \
    src/gui/boxes/textinputbox.cpp \
    src/gui/boxes/outputbox.cpp \
    src/gui/boxes/abstractbox.cpp \
    src/gui/boxes/simpleabstractbox.cpp \
    src/gui/boxes/vectorinputbox.cpp \
    src/gui/panels/scenepanel.cpp \
    src/gui/panels/trajcontrolpanel.cpp \
    src/gui/panels/trajpanel.cpp \
    src/gui/panels/lightpanel.cpp \
    src/gui/windows/mainwindow.cpp \
    src/gui/windows/addtrajwindow.cpp \
    src/scene/camera.cpp \
    src/scene/trajscene.cpp \
    src/sceneobj/traj.cpp \
    src/sceneobj/section.cpp \
    src/sceneobj/geometry.cpp \
    src/scene/trajbuffer.cpp \
    src/sceneobj/trajsegment.cpp \
    src/sceneobj/face.cpp

HEADERS += \
    src/gui/boxes/doublevalueinputbox.hpp \
    src/gui/boxes/doublevalueslidebox.hpp \
    src/gui/boxes/openfilebox.hpp \
    src/gui/boxes/colorselectbox.hpp \
    src/gui/boxes/textinputbox.hpp \
    src/gui/boxes/outputbox.hpp \
    src/gui/boxes/abstractbox.hpp \
    src/gui/boxes/simpleabstractbox.hpp \
    src/gui/boxes/vectorinputbox.hpp \
    src/gui/panels/scenepanel.hpp \
    src/gui/panels/trajcontrolpanel.hpp \
    src/gui/panels/trajpanel.hpp \
    src/gui/panels/lightpanel.hpp\
    src/gui/windows/mainwindow.hpp \
    src/gui/windows/addtrajwindow.hpp \
    src/scene/camera.hpp \
    src/scene/trajscene.hpp \
    src/sceneobj/traj.hpp \
    src/sceneobj/section.hpp \
    src/sceneobj/geometry.hpp \
    src/scene/trajbuffer.hpp \
    src/sceneobj/trajsegment.hpp \
    src/sceneobj/face.hpp

DISTFILES += \
    shaders/fragment_shader.glsl \
    shaders/vertex_shader.glsl

RESOURCES += \
    shaders/shaders.qrc
