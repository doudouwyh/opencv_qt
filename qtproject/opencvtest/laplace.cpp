#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

/**
 * @function main
 */
int laplace_test()
{
  //![variables]
  Mat src, src_gray, dst;
  int kernel_size = 3;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;
  const char* window_name = "Laplace Demo";
  //![variables]

  //![load]
  src = imread( "./images/lena.png", IMREAD_COLOR ); // Load an image

  if( src.empty() )
    { return -1; }
  //![load]

  //![reduce_noise]
  /// Reduce noise by blurring with a Gaussian filter
  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
  //![reduce_noise]

  //![convert_to_gray]
  cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to grayscale
  //![convert_to_gray]

  /// Apply Laplace function
  Mat abs_dst;
  //![laplacian]
  Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  //![laplacian]

  //![convert]
  convertScaleAbs( dst, abs_dst );
  //![convert]

  //![display]
  imshow( window_name, abs_dst );
  waitKey(0);
  //![display]

  return 0;
}
