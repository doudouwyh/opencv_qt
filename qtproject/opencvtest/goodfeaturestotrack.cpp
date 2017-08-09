/**
 * @function goodFeaturesToTrack_Demo.cpp
 * @brief Demo code for detecting corners using Shi-Tomasi method
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
Mat srctrack, src_gray_track;

int maxCorners = 23;
int maxTrackbar = 100;

RNG rngtrack(12345);
const char* source_window_track = "Image";

/// Function header
void goodFeaturesToTrack_Demo( int, void* );

/**
 * @function main
 */
//the Shi-Tomasi method
int goodFeaturesToTrack_test()
{
  /// Load source image and convert it to gray
  srctrack = imread("./images/box.png", 1 );
  cvtColor( srctrack, src_gray_track, COLOR_BGR2GRAY );

  /// Create Window
  namedWindow( source_window_track, WINDOW_AUTOSIZE );

  /// Create Trackbar to set the number of corners
  createTrackbar( "Max  corners:", source_window_track, &maxCorners, maxTrackbar, goodFeaturesToTrack_Demo );

  imshow( source_window_track, srctrack );

  goodFeaturesToTrack_Demo( 0, 0 );

  waitKey(0);
  return(0);
}

/**
 * @function goodFeaturesToTrack_Demo.cpp
 * @brief Apply Shi-Tomasi corner detector
 */
void goodFeaturesToTrack_Demo( int, void* )
{
  if( maxCorners < 1 ) { maxCorners = 1; }

  /// Parameters for Shi-Tomasi algorithm
  vector<Point2f> corners;
  double qualityLevel = 0.01;
  double minDistance = 10;
  int blockSize = 3;
  bool useHarrisDetector = false;
  double k = 0.04;

  /// Copy the source image
  Mat copy;
  copy = srctrack.clone();

  /// Apply corner detection
  goodFeaturesToTrack( src_gray_track,
               corners,
               maxCorners,
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
     { circle( copy, corners[i], r, Scalar(rngtrack.uniform(0,255), rngtrack.uniform(0,255), rngtrack.uniform(0,255)), -1, 8, 0 ); }

  /// Show what you got
  namedWindow( source_window_track, WINDOW_AUTOSIZE );
  imshow( source_window_track, copy );
}
