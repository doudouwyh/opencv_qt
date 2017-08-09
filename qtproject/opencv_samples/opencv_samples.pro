QT += core
QT -= gui

CONFIG += c++11

TARGET = opencv_samples
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    bagofwords_classification.cpp \
    bgfg_gmg.cpp \
    bgfg_segm.cpp \
    brief_match_test.cpp \
    build3dmodel.cpp \
    camshiftdemo.cpp \
    chamfer.cpp \
    connected_components.cpp \
    contours2.cpp \
    convexhull.cpp \
    delaunay2.cpp \
    demhist.cpp \
    descriptor_extractor_matcher.cpp \
    detector_descriptor_evaluation.cpp \
    dft.cpp \
    distrans.cpp \
    edge.cpp \
    em.cpp \
    fabmap_sample.cpp \
    facial_features.cpp \
    fback.cpp \
    ffilldemo.cpp \
    fitellipse.cpp \
    freak_demo.cpp \
    gencolors.cpp \
    generic_descriptor_match.cpp \
    grabcut.cpp \
    houghcircles.cpp \
    houghlines.cpp \
    hybridtrackingsample.cpp \
    inpaint.cpp \
    kalman.cpp \
    kmeans.cpp \
    laplace.cpp \
    latentsvm_multidetect.cpp \
    letter_recog.cpp \
    generatefeature.cpp

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
