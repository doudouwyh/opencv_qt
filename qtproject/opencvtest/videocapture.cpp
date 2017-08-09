#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int VideoCapture_test()
{
    //打开视频文件：其实就是建立一个VideoCapture结构
    VideoCapture capture("F:/dt.rmvb");
    //检测是否正常打开:成功打开时，isOpened返回ture
    if(!capture.isOpened()){
        cout<<"fail to open!"<<endl;
        return -1;
    }
    //获取整个帧数
    long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
    cout<<"total:"<<totalFrameNumber<<" frame"<<endl;


    //设置开始帧()
    long frameToStart = 300;
    capture.set( CV_CAP_PROP_POS_FRAMES,frameToStart);
    cout<<"start from the "<<frameToStart<<" frame"<<endl;


    //设置结束帧
    int frameToStop = 400;

    if(frameToStop < frameToStart)
    {
        cout<<"quit！"<<endl;
        return -1;
    }
    else
    {
        cout<<"end with the "<<frameToStop<<"frame"<<endl;
    }


    //获取帧率
    double rate = capture.get(CV_CAP_PROP_FPS);
    cout<<"frame rate:"<<rate<<endl;



    //定义一个用来控制读取视频循环结束的变量
    bool stop = false;
    //承载每一帧的图像
    Mat frame;
    //显示每一帧的窗口
    namedWindow("Extracted frame");
    //两帧间的间隔时间:
    //int delay = 1000/rate;
    int delay = 1000/rate;


    //利用while循环读取帧
    //currentFrame是在循环体中控制读取到指定的帧后循环结束的变量
    long currentFrame = frameToStart;


    //滤波器的核
    int kernel_size = 3;
    Mat kernel = Mat::ones(kernel_size,kernel_size,CV_32F)/(float)(kernel_size*kernel_size);

    while(!stop)
    {
        //读取下一帧
        if(!capture.read(frame))
        {
            cout<<"read failed"<<endl;
            return -1;
        }

        //这里加滤波程序
        imshow("Extracted frame",frame);
        filter2D(frame,frame,-1,kernel);

        imshow("after filter",frame);
        cout<<"reading the "<<currentFrame<<" frame"<<endl;



        int c = waitKey(delay);
        //按下ESC或者到达指定的结束帧后退出读取视频
        if((char) c == 27 || currentFrame > frameToStop)
        {
            stop = true;
        }
        //按下按键后会停留在当前帧，等待下一次按键
        if( c >= 0)
        {
            waitKey(0);
        }
        currentFrame++;

    }
    //关闭视频文件
    capture.release();
    waitKey(0);
    return 0;
}

