#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

Mat srcc, srcc_gray;
Mat dstc, detected_edges;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name_c = "Edge Map";

static void CannyThreshold(int, void*)
{
    blur( srcc_gray, detected_edges, Size(5,5) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    dstc = Scalar::all(0);
    srcc.copyTo( dstc, detected_edges);
    imshow( window_name_c, dstc );
}

int canny_test( )
{
  srcc = imread( "./images/lena.png", IMREAD_COLOR ); // Load an image
  if( srcc.empty() )
    { return -1; }
  dstc.create( srcc.size(), srcc.type() );
  cvtColor( srcc, srcc_gray, COLOR_BGR2GRAY );
  namedWindow( window_name_c, WINDOW_AUTOSIZE );
  createTrackbar( "Min Threshold:", window_name_c, &lowThreshold, max_lowThreshold, CannyThreshold );
  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}
