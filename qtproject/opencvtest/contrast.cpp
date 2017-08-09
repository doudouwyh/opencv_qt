#include <QDebug>
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//g(i,j)=α*f(i,j)+β
int brightness_constract_test()
{
    Mat image = imread("./lena.jpg" );
    Mat new_image = Mat::zeros( image.size(), image.type() );
    double alpha=2.2; /*< Simple contrast control */
    int beta=50;  /*< Simple brightness control */

    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < 3; c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
            }
        }
    }
    namedWindow("Original Image", 1);
    namedWindow("New Image", 1);
    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
    return 0;
}
