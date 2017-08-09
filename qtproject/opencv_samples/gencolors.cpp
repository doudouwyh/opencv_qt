#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>
#include <ctime>

using namespace cv;
using namespace std;

int gencolor_test()
{

    int colorsCount = 100;
    vector<Scalar> colors;
    theRNG() = (uint64)time(0);
    generateColors( colors, colorsCount );

    int stripWidth = 2;
    Mat strips(300, colorsCount*stripWidth, CV_8UC3);
    for( int i = 0; i < colorsCount; i++ )
    {
        strips.colRange(i*stripWidth, (i+1)*stripWidth) = colors[i];
    }

    imshow( "strips", strips );
    waitKey();

    return 0;
}
