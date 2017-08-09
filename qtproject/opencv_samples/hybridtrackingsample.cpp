/*
 *
 * Hybrid Tracking in OpenCV
 * Usage: ./hybridtrackingsample live
 *
 * For Benchmarking against the Bonn benchmark dataset
 * wget http://www.iai.uni-bonn.de/~kleind/tracking/datasets/seqG.zip
 * unzip seqG.zip -d ./seqG
 * ffmpeg -i seqG/Vid_G_rubikscube.avi seqG/%04d.png
 * ./hytrack seqG/Vid_G_rubikscube.txt
 *
 */

#include <stdio.h>
#include <time.h>
#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/hybridtracker.hpp"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

Mat frameht, imageht;
Rect selectionht;
Point originht;
bool selectObjectht = false;
int trackObjectht = 0;
int liveht = 1;

static void drawRectangle(Mat* img, Rect win) {
    rectangle(*img, Point(win.x, win.y), Point(win.x + win.width, win.y
            + win.height), Scalar(0, 255, 0), 2, CV_AA);
}

static void onMouse(int event, int x, int y, int, void*) {
    if (selectObjectht) {
        selectionht.x = MIN(x, originht.x);
        selectionht.y = MIN(y, originht.y);
        selectionht.width = std::abs(x - originht.x);
        selectionht.height = std::abs(y - originht.y);
        selectionht &= Rect(0, 0, imageht.cols, imageht.rows);
    }

    switch (event) {
    case CV_EVENT_LBUTTONDOWN:
        originht = Point(x, y);
        selectionht = Rect(x, y, 0, 0);
        selectObjectht = true;
        break;
    case CV_EVENT_LBUTTONUP:
        selectObjectht = false;
        trackObjectht = -1;
        break;
    }
}

static void help()
{
    printf("Usage: ./hytrack live or ./hytrack <test_file> \n\
For Live View or Benchmarking. Read documentation is source code.\n\n");
}


int hybridtracking_test()
{
   help();

    FILE* f = 0;
    VideoCapture cap;
//    char test_file[20] = "";

//    if (strcmp(argv[1], "live") != 0)
//    {
//        sprintf(test_file, "%s", argv[1]);
//        f = fopen(test_file, "r");
//        char vid[20];
//        int values_read = fscanf(f, "%s\n", vid);
//        CV_Assert(values_read == 1);
//        cout << "Benchmarking against " << vid << endl;
//        live = 0;
//    }
//    else
    {
        cap.open("./images/vtree.avi");
        if (!cap.isOpened())
        {
            cout << "Failed to open camera" << endl;
            return 0;
        }
        cout << "Opened camera" << endl;
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        cap >> frameht;
    }

    HybridTrackerParams params;
    // motion model params
    params.motion_model = CvMotionModel::LOW_PASS_FILTER;
    params.low_pass_gain = 0.1f;
    // mean shift params
    params.ms_tracker_weight = 0.8f;
    params.ms_params.tracking_type = CvMeanShiftTrackerParams::HS;
    // feature tracking params
    params.ft_tracker_weight = 0.2f;
    params.ft_params.feature_type = CvFeatureTrackerParams::OPTICAL_FLOW;
    params.ft_params.window_size = 0;

    HybridTracker tracker(params);
    char img_file[20] = "seqG/0001.png";
    char img_file_num[10];
    namedWindow("Win", 1);

    setMouseCallback("Win", onMouse, 0);

    int i = 0;
    float w[4];
    for(;;)
    {
        i++;
        if (liveht)
        {
            cap >> frameht;
            if( frameht.empty() )
                break;
            frameht.copyTo(imageht);
        }
        else
        {
            int values_read = fscanf(f, "%d %f %f %f %f\n", &i, &w[0], &w[1], &w[2], &w[3]);
            CV_Assert(values_read == 5);
            sprintf(img_file, "seqG/%04d.png", i);
            imageht = imread(img_file, CV_LOAD_IMAGE_COLOR);
            if (imageht.empty())
                break;
            selectionht = Rect(cvRound(w[0]*imageht.cols), cvRound(w[1]*imageht.rows),
                             cvRound(w[2]*imageht.cols), cvRound(w[3]*imageht.rows));
        }

        sprintf(img_file_num, "Frame: %d", i);
        putText(imageht, img_file_num, Point(10, imageht.rows-20), FONT_HERSHEY_PLAIN, 0.75, Scalar(255, 255, 255));
        if (!imageht.empty())
        {

            if (trackObjectht < 0)
            {
                tracker.newTracker(imageht, selectionht);
                trackObjectht = 1;
            }

            if (trackObjectht)
            {
                tracker.updateTracker(imageht);
                drawRectangle(&imageht, tracker.getTrackingWindow());
            }

            if (selectObjectht && selectionht.width > 0 && selectionht.height > 0)
            {
                Mat roi(imageht, selectionht);
                bitwise_not(roi, roi);
            }

            drawRectangle(&imageht, Rect(cvRound(w[0]*imageht.cols), cvRound(w[1]*imageht.rows),
                                       cvRound(w[2]*imageht.cols), cvRound(w[3]*imageht.rows)));
            imshow("Win", imageht);

            waitKey(100);
        }
        else
            i = 0;
    }

    fclose(f);
    return 0;
}
