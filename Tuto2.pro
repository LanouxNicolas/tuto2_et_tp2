QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    rvbody.cpp \
    rvcamera.cpp \
    rvpyramid.cpp \
    rvwidget.cpp

HEADERS += \
    rvbody.h \
    rvcamera.h \
    rvpyramid.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Instruction de compilation complémentaire pour Windows
windows:LIBS += -lopengl32

DISTFILES += \
    FS_simple.fsh \
    VS_simple.vsh

RESOURCES += \
    RVResources.qrc
