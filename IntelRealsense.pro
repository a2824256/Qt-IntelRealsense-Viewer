QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cameraworker.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cameraworker.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += 'C:/Program Files (x86)/Intel RealSense SDK 2.0/lib/x64/realsense2.lib'
INCLUDEPATH += 'C:/Program Files (x86)/Intel RealSense SDK 2.0/include/'

LIBS += -LE:/opencv_lib/x64/vc16/lib/ -lopencv_world451

INCLUDEPATH += E:/opencv_lib/include
DEPENDPATH += E:/opencv_lib/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
