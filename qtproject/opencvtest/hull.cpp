/**
 * @function hull_demo.cpp
 * @brief Demo code to find contours in an image
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat srchull; Mat srchull_gray;
int thresh_hull = 100;
int max_thresh_hull = 255;
RNG rnghull(12345);

/// Function header
void thresh_hull_callback(int, void* );

/**
 * @function main
 */
int hull_test()
{
  /// Load source image and convert it to gray
  srchull = imread("./images/hand_sample2.jpg", 1 );

  /// Convert image to gray and blur it
  cvtColor( srchull, srchull_gray, COLOR_BGR2GRAY );
  blur( srchull_gray, srchull_gray, Size(3,3) );

  /// Create Window
  const char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, srchull );

  createTrackbar( " thresh_hullold:", "Source", &thresh_hull, max_thresh_hull, thresh_hull_callback );
  thresh_hull_callback( 0, 0 );

  waitKey(0);
  return(0);
}

/**
 * @function thresh_hull_callback
 */
void thresh_hull_callback(int, void* )
{
  Mat srchull_copy = srchull.clone();
  Mat thresh_hullold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using thresh_hullold
  threshold( srchull_gray, thresh_hullold_output, thresh_hull, 255,THRESH_BINARY );

  /// Find contours
  findContours( thresh_hullold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Find the convex hull object for each contour
  vector<vector<Point> >hull( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     {   convexHull( Mat(contours[i]), hull[i], false ); }

  /// Draw contours + hull results
  Mat drawing = Mat::zeros( thresh_hullold_output.size(), CV_8UC3 );
  for( size_t i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rnghull.uniform(0, 255), rnghull.uniform(0,255), rnghull.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       drawContours( drawing, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
     }

  /// Show in a window
  namedWindow( "Hull demo", WINDOW_AUTOSIZE );
  imshow( "Hull demo", drawing );
}
