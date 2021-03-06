
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int filter2D_test ()
{
  /// Declare variables
  Mat src, dst;

  Mat kernel;
  Point anchor;
  double delta;
  int ddepth;
  int kernel_size;
  const char* window_name = "filter2D Demo";

  int c;

  /// Load an image
  src = imread("./images/lena.png");

  if( !src.data )
    { return -1; }

  /// Create window
  namedWindow( window_name, WINDOW_AUTOSIZE );

  /// Initialize arguments for the filter
  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;

  /// Loop - Will filter the image with different kernel sizes each 0.5 seconds
  int ind = 0;
  for(;;)
       {
         c = waitKey(500);
         /// Press 'ESC' to exit the program
         if( (char)c == 27 )
           { break; }

         /// Update kernel size for a normalized box filter
         kernel_size = 3 + 2*( ind%10 );
         kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

         cout<<"kernel:"<<kernel<<endl;

         /// Apply filter
         filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
         imshow( window_name, dst );
         ind++;
       }

  return 0;
}
