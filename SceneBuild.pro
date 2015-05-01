#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T18:03:02
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = SceneBuild
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    block/sphere.cpp \
    block/prism.cpp \
    block/plane.cpp \
    block/object.cpp \
    block/hemisphere.cpp \
    block/hbb.cpp \
    block/cylinder.cpp \
    block/cube.cpp \
    draw/draw.cpp \
    extra/material.cpp \
    extra/functions.cpp \
    interface/scene.cpp \
    interface/glwidget.cpp \
    interface/castingwidget.cpp \
    math/vec4.cpp \
    math/raytracing.cpp \
    math/rayintersection.cpp \
    math/raycasting.cpp \
    math/ray.cpp \
    math/quaternion.cpp \
    math/matrix4x4.cpp \
    structure/mesh.cpp \
    structure/light.cpp \
    block/cone.cpp \
    structure/ambientlight.cpp \
    structure/pontuallight.cpp \
    structure/directionallight.cpp \
    structure/spotlight.cpp \
    structure/arealight.cpp \
    extra/texture.cpp \
    extra/bump.cpp \
    structure/photon.cpp \
    structure/kdtree.cpp \
    interface/camera.cpp

HEADERS  += mainwindow.h \
    block/sphere.h \
    block/prism.h \
    block/plane.h \
    block/object.h \
    block/hemisphere.h \
    block/hbb.h \
    block/cylinder.h \
    block/cube.h \
    draw/draw.h \
    extra/material.h \
    extra/functions.h \
    interface/scene.h \
    interface/glwidget.h \
    interface/castingwidget.h \
    math/vec4.h \
    math/raytracing.h \
    math/rayintersection.h \
    math/raycasting.h \
    math/ray.h \
    math/quaternion.h \
    math/matrix4x4.h \
    structure/mesh.h \
    structure/light.h \
    block/cone.h \
    structure/ambientlight.h \
    structure/pontuallight.h \
    structure/directionallight.h \
    structure/spotlight.h \
    structure/arealight.h \
    extra/texture.h \
    extra/bump.h \
    structure/photon.h \
    structure/kdtree.h \
    structure/photon.h \
    interface/camera.h

FORMS    += mainwindow.ui

LIBS     += -lGLU -lglut -fopenmp

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

QT += xml #necessario colocar  para o xml funcionar
