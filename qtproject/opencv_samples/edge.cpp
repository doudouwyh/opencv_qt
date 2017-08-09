#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh2 = 1;
Mat imageedg, grayedge, edge, cedge;

// define a trackbar callback
static void onTrackbar(int, void*)
{
    blur(grayedge, edge, Size(3,3));

    // Run the edge detector on grayedgescale
    Canny(edge, edge, edgeThresh2, edgeThresh2*3, 3);
    cedge = Scalar::all(0);

    imageedg.copyTo(cedge, edge);
    imshow("Edge map", cedge);
}

static void help()
{
    printf("\nThis sample demonstrates Canny edge detection\n"
           "Call:\n"
           "    /.edge [imageedg_name -- Default is fruits.jpg]\n\n");
}

const static char* keys =
{
    "{1| |fruits.jpg|input imageedg name}"
};

int edge_test()
{
    help();

    //CommandLineParser parser(argc, argv, keys);
    string filename = "./images/fruits.jpg";

    imageedg = imread(filename, 1);
    if(imageedg.empty())
    {
        printf("Cannot read imageedg file: %s\n", filename.c_str());
        help();
        return -1;
    }
    cedge.create(imageedg.size(), imageedg.type());
    cvtColor(imageedg, grayedge, COLOR_BGR2GRAY);

    // Create a window
    namedWindow("Edge map", 1);

    // create a toolbar
    createTrackbar("Canny threshold", "Edge map", &edgeThresh2, 100, onTrackbar);

    // Show the imageedg
    onTrackbar(0, 0);

    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);

    return 0;
}
