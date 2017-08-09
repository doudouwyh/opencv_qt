#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <ctype.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout <<
            "\nThis program demonstrates Laplace point/edge detection using OpenCV function Laplacian()\n"
            "It captures from the camera of your choice: 0, 1, ... default 0\n"
            "Call:\n"
            "./laplace [camera #, default 0]\n" << endl;
}

int sigma = 3;
int smoothType = CV_GAUSSIAN;

int laplace_test()
{
    VideoCapture cap("./images/vtest.avi");
    help();

    if( !cap.isOpened() )
    {
        cout << "Could not initialize capturing...\n";
        return -1;
    }

    namedWindow( "Laplacian", 0 );
    createTrackbar( "Sigma", "Laplacian", &sigma, 15, 0 );

    Mat smoothed, laplace, result;

    for(;;)
    {
        Mat frame;
        cap >> frame;
        if( frame.empty() )
            break;

        int ksize = (sigma*5)|1;
        if(smoothType == CV_GAUSSIAN)
            GaussianBlur(frame, smoothed, Size(ksize, ksize), sigma, sigma);
        else if(smoothType == CV_BLUR)
            blur(frame, smoothed, Size(ksize, ksize));
        else
            medianBlur(frame, smoothed, ksize);

        Laplacian(smoothed, laplace, CV_16S, 5);
        convertScaleAbs(laplace, result, (sigma+1)*0.25);
        imshow("Laplacian", result);

        int c = waitKey(30);
        if( c == ' ' )
            smoothType = smoothType == CV_GAUSSIAN ? CV_BLUR : smoothType == CV_BLUR ? CV_MEDIAN : CV_GAUSSIAN;
        if( c == 'q' || c == 'Q' || (c & 255) == 27 )
            break;
    }

    return 0;
}
