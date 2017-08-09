#include <QDebug>
#include <QDir>
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

template<typename T>
void alphaBlendRGBA(const Mat& src1, const Mat& src2, Mat& dst);

void algorithm_test();

//! [scan-c]
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels; //cols * channels

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}


//! [scan-iterator]
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}


//! [scan-random]
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
    case 3:
        {
         Mat_<Vec3b> _I = I;

         for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j )
               {
                   _I(i,j)[0] = table[_I(i,j)[0]];
                   _I(i,j)[1] = table[_I(i,j)[1]];
                   _I(i,j)[2] = table[_I(i,j)[2]];
            }
         I = _I;
         break;
        }
    }

    return I;
}

int cvAlign( int size, int align )
{
    assert( (align & (align-1)) == 0 && size < INT_MAX );
    return (size + align - 1) & -align;
}



void test()
{

    cout<<"CV_8UC1:"<<CV_8UC1<<endl;
    cout<<"CV_8UC2:"<<CV_8UC2<<endl;
    cout<<"CV_8UC3:"<<CV_8UC3<<endl;
    cout<<"CV_8UC4:"<<CV_8UC4<<endl;

    Mat M(2,2, CV_8UC3, Scalar(1,1,255));
    cout << "M = " << endl << " " << M << endl << endl;
    cout<<"M.Transpose:"<<M.t()<<endl;

//    SVD svdm(M);
//    Mat pinvM = svdm.vt.t()*Mat::diag(1./svdm.w)*svdm.u.t();
//    cout <<"M.pInv:"<<endl<<pinvM<<endl;

    int sz[2] = {2,3};
    Mat L(2,sz, CV_8UC(1), Scalar::all(0));
    cout << "L = " << endl << " " << L << endl << endl;

    Mat M2;
    M2.create(4,4, CV_8UC(2));
    cout << "M2 = "<< endl << " "  << M2 << endl << endl;

    Mat E = Mat::eye(4, 5, CV_64F);
    cout << "E = " << endl << " " << E << endl << endl;
    Mat O = Mat::ones(2, 3, CV_32F);
    cout << "O = " << endl << " " << O << endl << endl;
    Mat Z = Mat::zeros(3,3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl << endl;

    Mat C = (Mat_<double>(4,4) << 0, -1, 0, -1, 5, -1, 0, -1, 0,1,1,1,2,2,2,2);
    cout << "C = " << endl << " " << C << endl << endl;
    Mat CD0 = C.diag();
    cout << "CD0 = " << endl << " " << CD0 << endl << endl;

    Mat CD1 = C.diag(1);
    cout << "CD1 = " << endl << " " << CD1 << endl << endl;

    Mat CDN1 = C.diag(-1);
    cout << "CDN1 = " << endl << " " << CDN1 << endl << endl;

    vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);

    Mat D = Mat::diag(Mat(vi));
    cout << "D = " << endl << " " << D << endl << endl;

    Mat RANGE(D,Range(0,2),Range(1,4));//[m,n)
    cout << "RANGE = " << endl << " " << RANGE << endl << endl;

    Range ranges[2]={Range(0,2),Range(1,4)};
    Mat RANGE2(D,ranges);
    cout << "RANGE2 = " << endl << " " << RANGE2 << endl << endl;



    Rect rect(0,0,3,3);//[m,n)
    Mat RECT(D,rect);
    cout << "RECT = " << endl << " " << RECT << endl << endl;


    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;

    Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255));

    cout << "R (default) = " << endl <<        R           << endl << endl;
    cout << "R (matlab)  = " << endl << format(R, "MATLAB") << endl << endl;
    cout << "R (python)  = " << endl << format(R, "PYTHON") << endl << endl;
    cout << "R (numpy)   = " << endl << format(R, "NUMPY" ) << endl << endl;
    cout << "R (c)       = " << endl << format(R, "C") << endl << endl;

    Point2f P(5, 1);
    cout << "Point (2D) = " << P << endl << endl;

    Point3f P3f(2, 6, 7);
    cout << "Point (3D) = " << P3f << endl << endl;

    vector<float> v;
    v.push_back( (float)CV_PI);   v.push_back(2);    v.push_back(3.01f);
    cout << "Vector of floats via Mat = " << Mat(v) << endl << endl;

    vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i)
        vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
    cout << "A vector of 2D Points = " << vPoints << endl << endl;

    Vec<int,4> vec(1,2,3,4);
    Mat V(vec);
    cout <<"V:"<<V<<endl;

    int sz3[]={4,5,6};
    Mat img(3,sz3,CV_8U);//3维数组
    cout<<img.dims<<endl;
    cout<<img.size[0]<<endl;
    cout<<img.size[1]<<endl;
    cout<<img.size[2]<<endl;

    cout<<img.step[0]<<endl;
    cout<<img.step[1]<<endl;
    cout<<img.step[2]<<endl;
    //遍历每个元素
    for(int i = 0; i < 4;++i)
    {
        for(int j = 0; j < 5;++j)
        {
            for(int k = 0; k < 6;++k)
            {
                cout<<(int)*(img.data + img.step[0]*i + img.step[1]*j + img.step[2]*k)<<endl;
            }
        }
    }

    // 方式一
    Mat matrix1 = (Mat_<int>(2, 3) << 0, 1, 2,
                                      3, 4, 5);
    cout <<"matrix1:"<< matrix1 << endl << endl;

    // 方式二
    Mat matrix2 = *(Mat_<int>(2, 3) << 0, 1, 2,
                                       3, 4, 5);
    cout <<"matrix2:"<< matrix2 << endl;

    cout <<"round:"<<cvRound(3.5)<<endl;

    int ui =saturate_cast<int>(4.5);

    cout <<"saturate_cast:"<<ui<<endl;

    try
    {
        cv::Exception e;
        e.msg = "just a test!";
        throw e;
    }
    catch( cv::Exception& e )
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }

    Mat M1(2,2, CV_8UC1, Scalar(5,1,255));
    cout << "M1 = " << endl << " " << M1 << endl << endl;


    /*basic type test*/
    Point2f a(3.4,5.6),b(7,8);
    cout <<"a:"<<a<<",b:"<<b<<endl;

    Point3f a3(3,4,5),b3(4,5,6);
    cout<<"a3:"<<a3<<",b3:"<<b3<<endl;

    Size s(100,200);
    cout <<"width:"<<s.width<<",height:"<<s.height<<",s:"<<s<<endl;

#if 0
    Mat imager(200, 200, CV_8UC3, Scalar(0));
    RotatedRect rRect = RotatedRect(Point2f(100,100), Size2f(100,50), 45);
    Point2f vertices[4];
    rRect.points(vertices);  //4 points of the rect
    for (int i = 0; i < 4; i++)
        line(imager, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));

    Rect brect = rRect.boundingRect();//the bounded rect of the rrect
    rectangle(imager, brect, Scalar(255,0,0));
    imshow("rectangles", imager);
    waitKey(50);
#endif

    TermCriteria tc(TermCriteria::COUNT,10,0.6);
    cout <<tc.COUNT<<endl;

    Matx33f m(1, 2, 3,
                     4, 5, 6,
                     7, 8, 9);
    cout << sum(Mat(m*m.t())) << endl;

    SVD svd(C);
    Mat pinvA = svd.vt.t()*Mat::diag(1./svd.w)*svd.u.t();
    cout <<"pinvA:"<<endl<<pinvA<<endl;

    cout <<"total:"<<pinvA.total()<<endl;

    //alphaBlendRGBA<double>(C,C,C);
    cout <<"C:"<<C<<endl;
    cout <<"at:"<<C.at<double>(0)<<endl;
    cout <<"at:"<<C.at<double>(1)<<endl;
    cout <<"at:"<<C.at<double>(1,2)<<endl;
    cout <<"at:"<<C.at<double>(Point(1,0))<<endl;  //!!!!
    cout <<"at:"<<C.at<double>(Point(0,1))<<endl;  // !!!!


    std::vector<Point2f> vec2;
    // points or a circle
    for( int i = 0; i < 30; i++ )
        vec2.push_back(Point2f((float)(100 + 30*cos(i*CV_PI*2/5)),
                              (float)(100 - 30*sin(i*CV_PI*2/5))));
    cv::transform(vec2, vec2, cv::Matx23f(0.707, -0.707, 10, 0.707, 0.707, 20));


    //algorithm_test();

    Mat absc = abs(C);
    cout <<"C:"<<endl<<C<<endl;
    cout <<"absc:"<<endl<<absc<<endl;

    Mat absdif;
    absdiff(C,absc,absdif);
    cout <<"absdiff:"<<endl<<absdif<<endl;

    Mat addm;
    add(C,absc,addm);
    cout <<"addm:"<<endl<<addm<<endl;

    Mat addw;
    addWeighted(C, 0.5, absc, 0.5, 1, addw,C.depth());
    cout <<"addw:"<<endl<<addw<<endl;

    Mat bitwiseand;
    bitwise_and(C,absc,bitwiseand);
    cout <<"bitwiseand:"<<endl<<bitwiseand<<endl;

    Mat bitwiseor;
    bitwise_or(C,absc,bitwiseor);
    cout <<"bitwiseor:"<<endl<<bitwiseor<<endl;

    Mat bitwisenot;
    bitwise_not(C,absc,bitwisenot);
    cout <<"bitwisenot:"<<endl<<bitwisenot<<endl;

    Mat bitwisexor;
    bitwise_xor(C,absc,bitwisexor);
    cout <<"bitwisexor:"<<endl<<bitwisexor<<endl;


    Mat_<float> samples[3];
    for (int i = 0; i < 3; i++)
    {
       samples[i].create(1, 3);  //1x3
       samples[i](0, 0) = i*3 + 1;
       samples[i](0, 1) = i*3 + 2;
       samples[i](0, 2) = i*3 + 3;
    }
    Mat_<double> covMat;
    Mat_<double> meanMat;
    calcCovarMatrix(samples, 3, covMat, meanMat, CV_COVAR_NORMAL);

    string fileName = "test.txt";
    FileStorage fs(fileName, FileStorage::WRITE);
    fs << "meanMat" << meanMat;
    fs << "covMat" << covMat;
    fs.release();


    Mat magnitude;
    Mat angle;
    cartToPolar(C, C, magnitude,angle);
    cout<<"magnitude:"<<magnitude<<endl;
    cout<<"angle:"<<angle<<endl;

    Mat X;
    Mat Y;
    polarToCart(magnitude,angle,X,Y);
    cout<<"X:"<<X<<endl;
    cout<<"Y:"<<Y<<endl;

    cout<<"checkRange:"<<checkRange(C)<<endl;

    cout<<"C"<<C<<endl;
    completeSymm(C);
    cout<<"C:"<<C<<endl;

    Mat Cabs;
    convertScaleAbs(C, Cabs);
    cout<<"Cabs:"<<Cabs<<endl;

    Mat mdct,mdft;
    dct(C,mdct);
    dft(C,mdft);
    cout <<"mdct:"<<mdct<<endl;
    cout <<"mdft:"<<mdft<<endl;
    cout<<"determinant:"<<determinant(C)<<endl;

    Mat midct,midft;
    idct(mdct,midct);
    idft(mdft,midft);
    cout<<"midct:"<<midct<<endl;
    cout<<"midft:"<<midft<<endl;



    Mat eigenvalues;
    Mat eigenvactors;
    eigen(C,eigenvalues,eigenvactors);
    cout <<"eigenvalues:"<<eigenvalues<<endl;
    cout <<"eigenvactors:"<<eigenvactors<<endl;

    Mat mexp;
    exp(C,mexp);
    cout<<"mexp:"<<mexp<<endl;

    Mat mflip;
    flip(C,mflip,0);
    cout<<"mflip:"<<mflip<<endl;

    Mat minverse;
    invert(C,minverse);
    cout<<"minverse:"<<minverse<<endl;

    Mat m1=(Mat_<int>(1,3)<<1,2,3);
    Mat m2=(Mat_<int>(1,3)<<4,5,6);
    Mat ma;
    cout<<"m1:"<<m1<<endl;
    cout<<"m2:"<<m2<<endl;
    //Mahalanobis(m1,m2,ma);
    cout<<"ma:"<<ma<<endl;


    Vec<int,10> v10;
    v10 << 1,2,3,4,5,6,7,8,9,0;
    cout <<"v10:"<<v10<<endl;

    Vec<double,5> v5(1,2,3,4,5);
    cout<<"v5:"<<v5<<endl;


    Mat rgba( 3, 3, CV_8UC4, Scalar(1,2,3,4) );
    Mat bgr( rgba.rows, rgba.cols, CV_8UC3 );
    Mat alpha( rgba.rows, rgba.cols, CV_8UC1 );

    // forming an array of matrices is a quite efficient operation,
    // because the matrix data is not copied, only the headers
    Mat out[] = { bgr, alpha };//4channals:{ bgr[0],bgr[1],bgr[2],alpha[0]}
    // rgba[0] -> bgr[2], rgba[1] -> bgr[1],
    // rgba[2] -> bgr[0], rgba[3] -> alpha[0]
    int from_to[] = { 0,2, 1,1, 2,0, 3,3 ,2,2};
    mixChannels( &rgba, 1, out, 2, from_to, 5 );

    cout<<"rgba:"<<endl<<rgba<<endl;
    cout<<"bgr:"<<endl<<bgr<<endl;
    cout<<"alpha:"<<endl<<alpha<<endl;

    Mat mt1 = (Mat_<int>(1,3) << 1,2,3);
    Mat mt2 = (Mat_<int>(1,3) << 3,4,5);
    Mat mmulty;
    multiply(mt1,mt2,mmulty);
    cout<<"multiply:"<<endl<<mmulty<<endl;

    cout<<"norm_L2:"<<cv::norm(C)<<endl;//NORM_L2

    Mat mtest (3,1,CV_8U);
    mtest.at<unsigned int>(0,0) = CV_VAR_NUMERICAL;
    mtest.at<unsigned int>(0,1) = CV_VAR_NUMERICAL;//row:1,col:0
    mtest.at<unsigned int>(0,2) = CV_VAR_NUMERICAL;
    cout <<"mtest:"<<mtest<<endl;
    cout<<"mtest.step:"<<mtest.step<<endl;
    CvMat cvmtest = mtest;
    int macroi = (CV_ELEM_SIZE(cvmtest.type));
    cout <<"elemtype:"<<macroi<<endl;

      int tm_size, tm_step;
      tm_size = cvmtest.rows+cvmtest.cols-1;
      tm_step = cvmtest.rows == 1 ? 1 : cvmtest.step/CV_ELEM_SIZE(cvmtest.type);

      cout <<"tm_szie:"<<tm_size<<endl;
      cout <<"tm_step:"<<tm_step<<endl;


      int var_count = 2;
      CvMat* out_var_type;
      out_var_type = cvCreateMat( 1, var_count, CV_8UC1 );

      uchar* src = cvmtest.data.ptr;
      uchar* dst = out_var_type->data.ptr;

      for(int  i = 0; i < var_count; i++ )
      {
          dst[i] = (uchar)(src[i*tm_step] != 0);
      }

      Mat mout(out_var_type,true);
      cout<<"mout:"<<mout<<endl;


    Mat mempty;
    cout<<"cols:"<<mempty.cols<<",rows:"<<mempty.rows<<endl;
    CvMat cm = mempty;
    if (cm.data.ptr == NULL){
        cout <<"null"<<endl;
    }else{
        cout <<"not null!"<<endl;
    }

    Mat mtemp(2,3,CV_8UC3);
    cout<<"elemsize:"<<mtemp.elemSize()<<",elemsize1:"<<mtemp.elemSize1()<<",dims:"<<mtemp.dims<<",channals:"<<mtemp.channels()<<",depth:"<<mtemp.depth()
       <<",type:"<<mtemp.type()<<",step:"<<mtemp.step<<",step1:"<<mtemp.step1()<<endl;

    int sample_count = 200;
    int max_split_size = cvAlign(sizeof(CvDTreeSplit) +
        (MAX(0,sample_count - 33)/32)*sizeof(int),sizeof(void*));
    cout <<"max_split_size:"<<max_split_size<<endl;

    CvSeq *seq;
    CvMemStorage* storage;
    float el_ptr[10] = {1,2,3,4,5,6,7,8,9,10};
    storage = cvCreateMemStorage();
    seq = cvCreateSeq( 0, sizeof(*seq), 10*sizeof(float), storage );
    cvSeqPush(seq,el_ptr);
    cout<<"sizeof CvSeq:"<<sizeof(CvSeq)<<endl;
    cout<<"seq.total:"<<seq->total<<endl;

    CvMat *cmtemp = cvCreateMat(seq->total,10,CV_32F);
    CvSeqReader reader;
    cvStartReadSeq( seq, &reader);

    for (int i=0; i< seq->total; i++)
    {
        const float* sdata = (float*)reader.ptr;
        cout <<"minus:"<<sdata[-1]<<endl;
        for (int j=0; j<10; j++)
        {
            cout<<sdata[j]<<" ";
        }
        cout<<endl;
    }

    Mat mseqtest(cmtemp,true);
    cout <<"mseqtest:"<<mseqtest<<endl;

    cout <<"epsilon:"<<FLT_EPSILON<<endl;

}


int test_opencv2()
{
     qDebug() << "test_opencv2...";
     const char* imagename = "E:\\qtproject\\lena\\temp\\lena.jpg";
     Mat img = imread(imagename);
     if(img.empty())
     {
         qDebug("Can not load image %s\n",imagename);
         return -1;
     }   

     Mat gray_image;
     cvtColor( img, gray_image, COLOR_BGR2GRAY );

     imwrite( "./Gray_Image.jpg", gray_image );
     namedWindow( "image");
     namedWindow( "Gray image");
     imshow( "image", img );
     imshow( "Gray image", gray_image );

     waitKey();

     return 0;

}

void test_opencv()
{
        qDebug() << "test_opencv...";
        //声明IplImage指针
        IplImage*pImg;

        IplImage* img = cvLoadImage("./images/lena.jpg", 1);
        Mat mtx(img); // convert IplImage* -> Mat
        CvMat oldmat = mtx; // convert Mat -> CvMat

        //载入图片
        pImg=cvLoadImage("E:\\qtproject\\lena\\temp\\lena.bmp",1);
        //创建窗口
        cvNamedWindow("Image",1);
        //显示图像
        cvShowImage("Image",pImg);
        //等待按键
        cvWaitKey(0);
        //销毁窗口
        cvDestroyWindow("Image");
        //释放图像
        cvReleaseImage(&pImg);
}



template<typename T>
void alphaBlendRGBA(const Mat& src1, const Mat& src2, Mat& dst)
{
    const float alpha_scale = (float)std::numeric_limits<T>::max(),
                inv_scale = 1.f/alpha_scale;

    CV_Assert( src1.type() == src2.type() &&
               src1.type() == CV_MAKETYPE(DataType<T>::depth, 4) &&
               src1.size() == src2.size());
    Size size = src1.size();
    dst.create(size, src1.type());

    // here is the idiom: check the arrays for continuity and,
    // if this is the case,
    // treat the arrays as 1D vectors
    if( src1.isContinuous() && src2.isContinuous() && dst.isContinuous() )
    {
        size.width *= size.height;
        size.height = 1;
    }
    size.width *= 4;

    for( int i = 0; i < size.height; i++ )
    {
        // when the arrays are continuous,
        // the outer loop is executed only once
        const T* ptr1 = src1.ptr<T>(i);
        const T* ptr2 = src2.ptr<T>(i);
        T* dptr = dst.ptr<T>(i);

        for( int j = 0; j < size.width; j += 4 )
        {
            float alpha = ptr1[j+3]*inv_scale, beta = ptr2[j+3]*inv_scale;
            dptr[j] = saturate_cast<T>(ptr1[j]*alpha + ptr2[j]*beta);
            dptr[j+1] = saturate_cast<T>(ptr1[j+1]*alpha + ptr2[j+1]*beta);
            dptr[j+2] = saturate_cast<T>(ptr1[j+2]*alpha + ptr2[j+2]*beta);
            dptr[j+3] = saturate_cast<T>((1 - (1-alpha)*(1-beta))*alpha_scale);
        }
    }
}

void algorithm_test(){
    cout <<"algorithm_test"<<endl;
    Mat image = imread("./images/lena.jpg");
    Mat imageGray = imread("./images/lena.jpg", 0);
    Mat descriptors;
    vector<KeyPoint> keypoints;

    initModule_features2d();

    Ptr<Feature2D> sift1 = Algorithm::create<Feature2D>("Feature2D.SIFT");
    sift1->set("contrastThreshold", 0.01f);
    (*sift1)(imageGray, noArray(), keypoints, descriptors);

    drawKeypoints(image, keypoints, image, Scalar(255,0,0));

    namedWindow("test");
    imshow("test", image);
    waitKey();
    destroyWindow("test");

    vector<string> algorithms;
    Algorithm::getList(algorithms);
    cout << "Algorithms: " << algorithms.size() << endl;
    for (size_t i=0; i < algorithms.size(); i++)
        cout << algorithms[i] << endl;
}
