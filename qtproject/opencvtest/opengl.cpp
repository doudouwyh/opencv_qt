#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// callback function
void onDraw(void* param)
{
    // Draw something using OpenGL here
    cout <<"onDraw......"<<endl;
}

int opengl_test(void)
{
    string openGLWindowName = "OpenGL Test";
    namedWindow(openGLWindowName, WINDOW_OPENGL);
    resizeWindow(openGLWindowName, 640, 480);
    setOpenGlContext(openGLWindowName);
    setOpenGlDrawCallback(openGLWindowName, onDraw, NULL);

    updateWindow(openGLWindowName);
    return 0;
}
