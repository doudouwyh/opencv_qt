
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

/// Global variables
Mat srcremap, dstremap;
Mat map_x, map_y;
const char* remap_window = "Remap demo";
int ind = 0;

/// Function Headers
void update_map( void );

/**
 * @function main
 */
int remapping_test()
{
  /// Load the image
  srcremap = imread( "./images/Remap_Tutorial_Original_Image.jpg", IMREAD_COLOR );

  /// Create dstremap, map_x and map_y with the same size as srcremap:
  dstremap.create( srcremap.size(), srcremap.type() );
  map_x.create( srcremap.size(), CV_32FC1 );
  map_y.create( srcremap.size(), CV_32FC1 );

  /// Create window
  namedWindow( remap_window, WINDOW_AUTOSIZE );

  /// Loop
  for(;;)
  {
    /// Each 1 sec. Press ESC to exit the program
    char c = (char)waitKey( 1000 );

    if( c == 27 )
      { break; }

    /// Update map_x & map_y. Then apply remap
    update_map();
    remap( srcremap, dstremap, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

    // Display results
    imshow( remap_window, dstremap );
  }
  return 0;
}

/**
 * @function update_map
 * @brief Fill the map_x and map_y matrices with 4 types of mappings
 */
void update_map( void )
{
  ind = ind%4;

  for( int j = 0; j < srcremap.rows; j++ )
    { for( int i = 0; i < srcremap.cols; i++ )
     {
           switch( ind )
         {
         case 0:
           if( i > srcremap.cols*0.25 && i < srcremap.cols*0.75 && j > srcremap.rows*0.25 && j < srcremap.rows*0.75 )
                 {
               map_x.at<float>(j,i) = 2*( i - srcremap.cols*0.25f ) + 0.5f ;
               map_y.at<float>(j,i) = 2*( j - srcremap.rows*0.25f ) + 0.5f ;
              }
           else
         { map_x.at<float>(j,i) = 0 ;
               map_y.at<float>(j,i) = 0 ;
                 }
                   break;
         case 1:
               map_x.at<float>(j,i) = (float)i ;
               map_y.at<float>(j,i) = (float)(srcremap.rows - j) ;
           break;
             case 2:
               map_x.at<float>(j,i) = (float)(srcremap.cols - i) ;
               map_y.at<float>(j,i) = (float)j ;
           break;
             case 3:
               map_x.at<float>(j,i) = (float)(srcremap.cols - i) ;
               map_y.at<float>(j,i) = (float)(srcremap.rows - j) ;
           break;
             } // end of switch
     }
    }
  ind++;
}
