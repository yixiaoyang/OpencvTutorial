#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T11:40:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGame
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CVTools.cpp \
    ObjDetectThread.cpp

HEADERS  += MainWindow.h \
    CVTools.h \
    ObjDetectThread.h

FORMS    += MainWindow.ui

# opencv
INCLUDEPATH += /usr/local/include/opencv2/
# -lopencv_ml -lopencv_photo -lopencv_shape  -lopencv_imgcodecs
LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_objdetect -lopencv_videoio -lopencv_imgcodecs
QMAKE_CXXFLAGS += -std=c++11 -g

