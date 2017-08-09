#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QDir>

#include"cv.h"
#include"cxcore.h"
#include"highgui.h"

#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int test_opencv2();
void test_opencv();
void test();
void input_output_test();
int blend_test();
int brightness_constract_test();
int basicdraw_test( void );
int random_text_test( void );
void Sharpen(const Mat& myImage,Mat& Result);
int dft_test();
int xml_yaml_test();
int with_opencv1_test( );
int ippasync_test();
int smooth_test( void );
int morphology_1_test( );
int morphology_2_test( );
int morphology_3_test();
int pyramids_test( void );
int threshold_test( );
int threshold_with_inrange();
int VideoCapture_test();
int filter2D_test ();
int makeborder_test();
int sobel_test( );
int laplace_test();
int canny_test( );
int houghlines_test();
int houghcircle_test();
int remapping_test();
int geometrytransforms_test();
int equalize_hist_test();
int calc_hist_test();
int compare_hist_test();
int backprojection_test();
int backprojection_test2();
int matchtemplate_test();
int findcontours_test();
int hull_test();
int general_contours_test1();
int general_counter_test2();
int moments_test();
int point_polygon_test();
int segmentation_test();
int gdal_test();
int gdal_demo_test();
int video_input_psnr_ssim_test();
int video_write_test();
//int video_calibration_test();
int corner_harris_test();
int goodFeaturesToTrack_test();
int corner_detector_test();
int cornerSubPix_test();
int feature_detection_test();
int feature_description_test();
int surf_flannmatcher_test();
int SURF_Homography_test();
int objectDetection_test1();
int svm_test();
int svm_nonlinear_test();
int pca_test();
int gpu_test();
int retina_test();
void test_rect();
void myalgorithm_test();
int  kmeans_test();
int opengl_test(void);

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);


/**
*   book: Learning OpenCV
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();    

    //opengl_test();

    //kmeans_test();

    //retina_test();

    //gpu_test();  //opencv should be compiled with :WITH_CUDA and WITH_TBB

    //pca_test();

    //svm_nonlinear_test();

    //svm_test();

    //objectDetection_test1();

    //SURF_Homography_test();

    //surf_flannmatcher_test();

    //feature_description_test();

    //feature_detection_test();

    //cornerSubPix_test();

    //corner_detector_test();

    //goodFeaturesToTrack_test();

   // corner_harris_test();

    //video_calibration_test();

    //video_write_test();

    //video_input_psnr_ssim_test();

    //gdal_demo_test();
    //gdal_test();

    //segmentation_test();

    //point_polygon_test();

    //moments_test();

    //general_counter_test2();
    //general_contours_test1();

    //hull_test();

    //findcontours_test();

    //matchtemplate_test();
    //backprojection_test2();
    //backprojection_test();

    //compare_hist_test();
    //calc_hist_test();
    //equalize_hist_test();

    //geometrytransforms_test();
    //remapping_test();
    //houghcircle_test();
    //houghlines_test();

    //canny_test() ;

    //laplace_test();
    //sobel_test( );

    //makeborder_test();

    //filter2D_test ();

    //threshold_with_inrange();
    //threshold_test();

    //pyramids_test();

    //morphology_3_test();
    //morphology_2_test( );
    //morphology_1_test();
    //smooth_test();
    //ippasync_test();
    //with_opencv1_test();
    //xml_yaml_test();
    //dft_test();
    //random_text_test();
    //basicdraw_test();
    //brightness_constract_test();
    //blend_test();
    //input_output_test();
    test();
    //test_rect();
    //test_opencv2();
    //test_opencv();
    //VideoCapture_test();
    //myalgorithm_test();

#if 0
////////////////////////////////////////////////////////////
    QString path;
    QDir dir;
    path=dir.currentPath();
    qDebug() << "currentPath:" <<path<<endl;

    Mat I, J;
    //I = imread("./debug/lena.bmp", IMREAD_GRAYSCALE);
    I = imread("./debug/lena.bmp", IMREAD_COLOR);

    if (I.empty())
    {
        cout << "The image" << " lena.bmp" << " could not be loaded." << endl;
        return -1;
    }


    Mat K;
    Mat kern = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  5, -1,
                                    0, -1,  0);
    filter2D(I, K, I.depth(), kern );
     namedWindow( "filter2D");
    imshow("filter2D", K);

    Mat sharp;
    cout<<"depth:"<<I.depth()<<endl;
    Sharpen(I,sharp);
    imwrite( "./sharpen.jpg", sharp );
    namedWindow( "image");
    namedWindow( "sharpen");
    imshow( "image", I );
    imshow( "sharpen",sharp );



    int divideWith = 100;
    uchar table[256];
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));
    cout << "table:" <<table <<endl;


    const int times = 100;
    double t;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceIterator(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        ScanImageAndReduceRandomAccess(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;


    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];


    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)        
        LUT(I, lookUpTable, J);  //J[i] = lookUpTable[I[i]]

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the LUT function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;
////////////////////////////////////////////////////////////
#endif

    return a.exec();
}



