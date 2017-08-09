#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T14:44:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvtest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    test.cpp \
    mask.cpp \
    inoutput.cpp \
    blend.cpp \
    contrast.cpp \
    basicdraw.cpp \
    random_text.cpp \
    dft.cpp \
    xml_yaml.cpp \
    opencv1.cpp \
    ippasync.cpp \
    smooth.cpp \
    morphology_1.cpp \
    morphology_2.cpp \
    morphology_3.cpp \
    pyramids.cpp \
    threshold.cpp \
    threshold_2.cpp \
    videocapture.cpp \
    filter2d.cpp \
    copymakeborder.cpp \
    sobel.cpp \
    laplace.cpp \
    canny.cpp \
    houghlines.cpp \
    houghcircle.cpp \
    remapping.cpp \
    geometric_transforms.cpp \
    equalizehist.cpp \
    calchist.cpp \
    comparehist.cpp \
    calcbackproject1.cpp \
    backprojection2.cpp \
    matchtemplate.cpp \
    findcontours.cpp \
    hull.cpp \
    generalcontours1.cpp \
    generalcontour2.cpp \
    moments.cpp \
    pointpolygon.cpp \
    segmentation.cpp \
    gdal.cpp \
    gdal_test.cpp \
    video-input-psnr-ssim.cpp \
    video_write.cpp \
    camera_calibration.cpp \
    cornerharris.cpp \
    goodfeaturestotrack.cpp \
    cornerdetector_demo.cpp \
    cornersubpix_demo.cpp \
    feature_detection.cpp \
    feature_description.cpp \
    surf_flannmatcher.cpp \
    surf_homography.cpp \
    objectdetection.cpp \
    ml_svm.cpp \
    ml_svm_nonlinear.cpp \
    ml_pca.cpp \
    gpu.cpp \
    retina.cpp \
    test_rect.cpp \
    myalgorithm.cpp \
    kmeans.cpp \
    opengl.cpp

HEADERS  += mainwindow.h

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

RESOURCES += \
    res.qrc


