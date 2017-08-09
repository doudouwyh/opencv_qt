#include <QDebug>
#include <QDir>
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


//OpenCV里貌似没有判断rect1是否在rect2里面的功能，所以自己写一个吧
bool isInside(Rect rect1, Rect rect2)
{
    return (rect1 == (rect1&rect2));
}

//OpenCV貌似也没有获取矩形中心点的功能，还是自己写一个
Point getCenterPoint(Rect rect)
{
    Point cpt;
    cpt.x = rect.x + cvRound(rect.width/2.0);
    cpt.y = rect.y + cvRound(rect.height/2.0);
    return cpt;
}

//围绕矩形中心缩放
Rect rectCenterScale(Rect rect, Size size)
{
    rect = rect + size;
    Point pt;
    pt.x = cvRound(size.width/2.0);
    pt.y = cvRound(size.height/2.0);
    return (rect-pt);
}


void test_rect()
{
    Rect rect(100, 50, 50, 100);//x,y,width,height
    cout <<"area:"<<rect.area()<<endl;     //返回rect的面积 5000
    cout<<"szie:"<<rect.size()<<endl;     //返回rect的尺寸 [50 × 100]
    cout<<"topleft:"<<rect.tl()<<endl;       //返回rect的左上顶点的坐标 [100, 50]
    cout<<"x:"<<rect.x<<endl;
    cout<<"y:"<<rect.y<<endl;
    cout<<"bottomright:"<<rect.br()<<endl;       //返回rect的右下顶点的坐标 [150, 150]
    cout<<"width:"<<rect.width<<endl;    //返回rect的宽度 50
    cout<<"height:"<<rect.height<<endl;   //返回rect的高度 100
    cout<<"iscontain:"<<rect.contains(Point(110, 40))<<endl;  //返回布尔变量，判断rect是否包含Point(x, y)点

    Rect rect1(0,0,100,100);
    Rect rect2(50,50,150,150);
    Rect  rectint;
    Rect  rectuno;
    rectint = rect1 & rect2;
    cout <<"intersection:"<<endl<<rectint<<endl;
    rectuno = rect1 | rect2;
    cout <<"union:"<<endl<<rectuno<<endl;

    rect = rect + Point(-100, 100); //平移，也就是左上顶点的x坐标-100，y坐标+100
    rect = rect + Size(-100, 100);  //缩放，左上顶点不变，宽度-100，高度+100

    cout <<"iseqaual:"<<(rect1 == rect2)<<endl;
    cout <<"isnotequal:"<<(rect1 != rect2)<<endl;


    Mat bg(200,200,CV_8UC3,Scalar(0));
    imshow("",bg);
    RotatedRect rRect(Point2f(100,100),Size(100,100),40);
    Point2f vertices[4];
    rRect.points(vertices);
    for(int i = 0; i < 4;++i)
        line(bg,vertices[i],vertices[(i+1)%4],Scalar(0,255,0));
    Rect brect = rRect.boundingRect();
    rectangle(bg,brect,Scalar(255,0,0));
    imshow("",bg);
    waitKey();
}
