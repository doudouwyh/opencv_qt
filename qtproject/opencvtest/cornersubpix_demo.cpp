/**
 * @function cornerSubPix_Demo.cpp
 * @brief Demo code for refining corner locations
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat srccsd, srccsd_gray;

int maxCornersscd = 10;
int maxTrackbarscd = 25;

RNG rngcsd(12345);
const char* source_window_csd = "Image";

/// Function header
void goodFeaturesToTrack_Demo2( int, void* );

/**
 * @function main
 */
int cornerSubPix_test()
{
  /// Load source image and convert it to gray
  srccsd = imread( "./images/building.jpg", 1 );
  cvtColor( srccsd, srccsd_gray, COLOR_BGR2GRAY );

  /// Create Window
  namedWindow( source_window_csd, WINDOW_AUTOSIZE );

  /// Create Trackbar to set the number of corners
  createTrackbar( "Max  corners:", source_window_csd, &maxCornersscd, maxTrackbarscd, goodFeaturesToTrack_Demo2 );

  imshow( source_window_csd, srccsd );

  goodFeaturesToTrack_Demo2( 0, 0 );

  waitKey(0);
  return(0);
}

/**
 * @function goodFeaturesToTrack_Demo.cpp
 * @brief Apply Shi-Tomasi corner detector
 */
void goodFeaturesToTrack_Demo2( int, void* )
{
  if( maxCornersscd < 1 ) { maxCornersscd = 1; }

  /// Parameters for Shi-Tomasi algorithm
  vector<Point2f> corners;
  double qualityLevel = 0.01;
  double minDistance = 10;
  int blockSize = 3;
  bool useHarrisDetector = false;
  double k = 0.04;

  /// Copy the source image
  Mat copy;
  copy = srccsd.clone();

  /// Apply corner detection
  goodFeaturesToTrack( srccsd_gray,
               corners,
               maxCornersscd,
               qualityLevel,
               minDistance,
               Mat(),
               blockSize,
               useHarrisDetector,
               k );


  /// Draw corners detected
  cout<<"** Number of corners detected: "<<corners.size()<<endl;
  int r = 4;
  for( size_t i = 0; i < corners.size(); i++ )
     { circle( copy, corners[i], r, Scalar(rngcsd.uniform(0,255), rngcsd.uniform(0,255), rngcsd.uniform(0,255)), -1, 8, 0 ); }

  /// Show what you got
  namedWindow( source_window_csd, WINDOW_AUTOSIZE );
  imshow( source_window_csd, copy );

  /// Set the neeed parameters to find the refined corners
  Size winSize = Size( 5, 5 );
  Size zeroZone = Size( -1, -1 );
  TermCriteria criteria = TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );

  /// Calculate the refined corner locations
  cornerSubPix( srccsd_gray, corners, winSize, zeroZone, criteria );

  /// Write them down
  for( size_t i = 0; i < corners.size(); i++ )
     { cout<<" -- Refined Corner ["<<i<<"]  ("<<corners[i].x<<","<<corners[i].y<<")"<<endl; }
}
