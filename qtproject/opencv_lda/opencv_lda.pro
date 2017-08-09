#-------------------------------------------------
#
# Project created by QtCreator 2017-03-06T15:03:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv_lda
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fisherfaces.cpp \
    helper.cpp \
    subspace.cpp \
    lda.cpp

HEADERS  += mainwindow.h \
    decomposition.hpp \
    fisherfaces.hpp \
    helper.hpp \
    subspace.hpp

FORMS    += mainwindow.ui

INCLUDEPATH+=D:\opencv\myinstall\include\opencv2 \
             D:\opencv\myinstall\include\opencv \
             D:\opencv\myinstall\include \
             D:\MinGW_GDAL200\GDAL200\include



LIBS+=  D:\opencv\myinstall\lib\libopencv_calib3d2412.dll.a \
D:\opencv\myinstall\lib\libopencv_contrib2412.dll.a \
D:\opencv\myinstall\lib\libopencv_core2412.dll.a \
D:\opencv\myinstall\lib\libopencv_features2d2412.dll.a \
D:\opencv\myinstall\lib\libopencv_flann2412.dll.a \
D:\opencv\myinstall\lib\libopencv_gpu2412.dll.a \
D:\opencv\myinstall\lib\libopencv_highgui2412.dll.a \
D:\opencv\myinstall\lib\libopencv_imgproc2412.dll.a \
D:\opencv\myinstall\lib\libopencv_legacy2412.dll.a \
D:\opencv\myinstall\lib\libopencv_ml2412.dll.a \
D:\opencv\myinstall\lib\libopencv_nonfree2412.dll.a \
D:\opencv\myinstall\lib\libopencv_objdetect2412.dll.a \
D:\opencv\myinstall\lib\libopencv_ocl2412.dll.a \
D:\opencv\myinstall\lib\libopencv_photo2412.dll.a \
D:\opencv\myinstall\lib\libopencv_stitching2412.dll.a \
D:\opencv\myinstall\lib\libopencv_superres2412.dll.a \
D:\opencv\myinstall\lib\libopencv_ts2412.a \
D:\opencv\myinstall\lib\libopencv_video2412.dll.a \
D:\opencv\myinstall\lib\libopencv_videostab2412.dll.a \
D:\MinGW_GDAL200\GDAL200\lib\libgdal.dll.a
