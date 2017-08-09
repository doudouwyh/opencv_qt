#include <QDebug>
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;



int input_output_test()
{
    const char* imagename = "E:\\qtproject\\lena\\temp\\lena.jpg";
    Mat img = imread(imagename);
    if(img.empty())
    {
        qDebug("Can not load image %s\n",imagename);
        return -1;
    }

    cout<<"img type:"<<img.type()<<endl;

    Mat gray_image;
    cvtColor( img, gray_image, COLOR_BGR2GRAY );
   cout<<"gray_image type:"<<gray_image.type()<<endl;
    imwrite( "./Gray_Image.jpg", gray_image );

    Mat sobelx;
    Sobel(img, sobelx, CV_32F, 1, 0);



    double minVal, maxVal;
    minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
    Mat draw;
    sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));


    Mat black;
    black.create(img.size(),img.type());
    black = Scalar(0);

    Mat covertimg;
    img.convertTo(covertimg, CV_32F);

    namedWindow( "image");
    namedWindow( "Gray image");
    namedWindow( "sobel");
    namedWindow( "black");
    namedWindow( "covert");
    namedWindow( "draw");

    imshow( "image", img );
    imshow( "Gray image", gray_image );
    imshow( "sobel", sobelx );
    imshow( "black", black );
    imshow( "covert", covertimg );
    imshow("draw",draw);

    waitKey();
    return 0;
}
