#include <QDebug>
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//dst = alpha*src1 + beta*src2 + gammar
int blend_test(  )
{
   double alpha = 0.9; double beta;
   Mat src1, src2, blend;

   src1 = imread("./images/LinuxLogo.jpg");
   src2 = imread("./images/WindowsLogo.jpg");
   if( src1.empty() ) { std::cout<< "Error loading src1"<<std::endl; return -1; }
   if( src2.empty() ) { std::cout<< "Error loading src2"<<std::endl; return -1; }
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 1.0, blend); //blend

   namedWindow( "src1");
   namedWindow( "src2");
   namedWindow( "blend");

   imshow( "src1", src1 );
   imshow( "src2", src2 );
   imshow( "blend", blend );
   waitKey(0);
   return 0;
}

