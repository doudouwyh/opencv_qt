/**
 * @file BackProject_Demo2.cpp
 * @brief Sample code for backproject function usage ( a bit more elaborated )
 * @author OpenCV team
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

/// Global Variables
Mat srcbp2; Mat hsvbp2;
Mat mask;

int lo = 20; int up = 20;
const char* window_image = "Source image2";

/// Function Headers
void Hist_and_Backproj( );
void pickPoint (int event, int x, int y, int, void* );

/**
 * @function main
 */
int backprojection_test2()
{
  /// Read the image
  srcbp2 = imread("./images/hand_sample2.jpg", 1 );
  /// Transform it to hsvbp2
  cvtColor( srcbp2, hsvbp2, COLOR_BGR2HSV );

  /// Show the image
  namedWindow( window_image, WINDOW_AUTOSIZE );
  imshow( window_image, srcbp2 );

  /// Set Trackbars for floodfill thresholds
  createTrackbar( "Low thresh", window_image, &lo, 255, 0 );
  createTrackbar( "High thresh", window_image, &up, 255, 0 );
  /// Set a Mouse Callback
  setMouseCallback( window_image, pickPoint, 0 );

  waitKey(0);
  return 0;
}

/**
 * @function pickPoint
 */
void pickPoint (int event, int x, int y, int, void* )
{
  if( event != CV_EVENT_LBUTTONDOWN )
    { return; }

  // Fill and get the mask
  Point seed = Point( x, y );

  int newMaskVal = 255;
  Scalar newVal = Scalar( 120, 120, 120 );

  int connectivity = 8;
  int flags = connectivity + (newMaskVal << 8 ) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

  Mat mask2 = Mat::zeros( srcbp2.rows + 2, srcbp2.cols + 2, CV_8UC1 );
  floodFill( srcbp2, mask2, seed, newVal, 0, Scalar( lo, lo, lo ), Scalar( up, up, up), flags );
  mask = mask2( Range( 1, mask2.rows - 1 ), Range( 1, mask2.cols - 1 ) );

  imshow( "Mask", mask );

  Hist_and_Backproj( );
}

/**
 * @function Hist_and_Backproj
 */
void Hist_and_Backproj( )
{
  MatND hist;
  int h_bins = 30; int s_bins = 32;
  int histSize[] = { h_bins, s_bins };

  float h_range[] = { 0, 179 };
  float s_range[] = { 0, 255 };
  const float* ranges[] = { h_range, s_range };

  int channels[] = { 0, 1 };

  /// Get the Histogram and normalize it
  calcHist( &hsvbp2, 1, channels, mask, hist, 2, histSize, ranges, true, false );

  normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

  /// Get Backprojection
  MatND backproj;
  calcBackProject( &hsvbp2, 1, channels, hist, backproj, ranges, 1, true );

  /// Draw the backproj
  imshow( "BackProj", backproj );

}
