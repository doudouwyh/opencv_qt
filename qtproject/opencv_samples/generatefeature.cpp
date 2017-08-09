#define GenerateImageFeature __declspec(dllexport)

//#include "GenerateImageFeature.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <iterator>
#include <algorithm>
#include <sstream>

using cv::imread;
using cv::namedWindow;
using cv::imshow;
using cv::waitKey;
using cv::Mat;
using cv::resize;
using cv::Size;
using cv::cvtColor;
using cv::GoodFeaturesToTrackDetector;
using cv::FeatureDetector;
using cv::KeyPoint;
using cv::Ptr;
using cv::drawKeypoints;
using cv::DrawMatchesFlags;
using cv::Range;
using cv::bitwise_and;
using cv::split;
using cv::calcHist;

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::minmax_element;
using std::min;
using std::sort;
#include <map>
using std::pair;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cout;
using std::endl;
#include <numeric>
using std::accumulate;

using namespace std;


class FeatureInfo
{
public:
    FeatureInfo(double freq) :m_freq(freq){}
    FeatureInfo(size_t hsLocation, double freq) :m_hsLocation(hsLocation), m_freq(freq){}
    void setFreq(double freq){
        m_freq = freq;
    }
    size_t getHSLocation()const{
        return m_hsLocation;
    }

    double getFreq()const{
        return m_freq;
    }
private:
    size_t m_hsLocation; // h-s组合位置
    double m_freq; // 频率
};

// 输出特征到缓冲buffer
int outputToBuffer(const vector<FeatureInfo>& feas, char* buffer, int fea_str_max_len);

// 获取图像特征 留作对外接口
// img_path-输入图像路径 img_name-输入图像名称 fea_str-特征存储区 fea_str_max_len-特征存储区最大容量
// 返回正数表示特征个数 返回-1表示特征存储区空间不够 返回-2表示图像路径错误
int getSimilarityFeature(char* img_path, char* img_name, char* feas_str, int feas_str_max_len)
{
    // 读入图像
    Mat img = imread((string(img_path) + "\\" + string(img_name)).c_str());
    /*Mat img = imread("E:\\YuFeiShare\\图像相似性检测Python版\\corpus\\ukbench\\full\\ukbench00000.jpg");*/
    if (img.empty())
    {
        return -2;
    }

    // 将图像缩放到128*128像素，以便确定最大兴趣点数量。
    resize(img, img, Size(128, 128), 0, 0, CV_INTER_CUBIC);
    // 图像从rgb空间转灰度图像，用于兴趣点检测，进而确定兴趣区域
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);
    // 图像从rgb转hsv空间图像,用于彩色直方图计算
    Mat hsv;
    cvtColor(img, hsv, CV_BGR2HSV);
    // 显示预处理后的图像 （测试用）
    imshow("原图像", img);
    imshow("gray", gray);
    imshow("hsv", hsv);
    //waitKey(0);

    // 检测兴趣点
    vector<KeyPoint> keypoints;
    Ptr<FeatureDetector> gfft = new GoodFeaturesToTrackDetector(200, 0.01, 10);
    gfft->detect(gray, keypoints);
    // 在灰度图像上描述兴趣点 （测试用）
    drawKeypoints(gray, keypoints, gray, cv::Scalar(255, 255, 255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
    imshow("ROI", gray);
    waitKey(0);


    // 确定兴趣区域
    float min_x = 0;
    float max_x = static_cast<float>(img.rows);
    float min_y = 0;
    float max_y = static_cast<float>(img.cols);
    if (!keypoints.empty())
    {
        auto minmax_x = minmax_element(keypoints.begin(), keypoints.end(), [](KeyPoint a, KeyPoint b){return a.pt.x < b.pt.x; });
        auto minmax_y = minmax_element(keypoints.begin(), keypoints.end(), [](KeyPoint a, KeyPoint b){return a.pt.y < b.pt.y; });
        min_x = minmax_x.first->pt.x;
        max_x = minmax_x.second->pt.x;
        min_y = minmax_y.first->pt.y;
        max_y = minmax_y.second->pt.y;
    }
    float a = max_x - min_x;
    float b = max_y - min_y;
    float c = (max_x + min_x) / 2;
    float d = (max_y + min_y) / 2;
    float e = min(a, b) / 2;
    // 显示兴趣区域（测试用）
    /*Mat roiImage(img.rows, img.cols, CV_8UC3);
    cout << img.rows << " " << img.cols << endl;
    cout << e << endl;
    img(Range(int(c - e / 2), int(c + e / 2)), Range(int(d - e / 2), int(d + e / 2))).copyTo(roiImage);
    imshow("ROI", roiImage);
    waitKey(0);*/

    // 计算直方图
    Mat roiMask = Mat::zeros(hsv.rows, hsv.cols, CV_8U);
    roiMask(Range(int(c - e / 2), int(c + e / 2)), Range(int(d - e / 2), int(d + e / 2))) = 255;
    // 显示掩模区域 （测试用）
    /*imshow("roiMask",roiMask);
    waitKey(0);*/

    Mat hist;
    int histSize[3] = { 180, 4 }; // 箱子大小
    float hranges0[2] = { 0.0, 180.0 }; // 色调取值范围
    float hranges1[2] = { 0.0, 256.0 }; // 饱和度取值范围
    const float* ranges[2] = { hranges0, hranges1 };
    int channels[2] = { 0, 1 }; // 两通道
    calcHist(&hsv, 1, channels, roiMask, hist, 2, histSize, ranges);

    // 特征抽取
    size_t h_s_location = 0;
    vector<FeatureInfo> one_dim_hist; // 转为一维向量并存储为特征信息形式
    for (int i = 0; i < 180; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            one_dim_hist.push_back(FeatureInfo(h_s_location, double(hist.at<float>(i, j))));
            h_s_location++;
        }
    }
    double total_pixels = accumulate(one_dim_hist.begin(), one_dim_hist.end(),
        double(0), [](FeatureInfo x, FeatureInfo y)->double{return x.getFreq() + y.getFreq(); }); // 计算像素总数
    vector<FeatureInfo>::iterator it_one_dim_hist = one_dim_hist.begin();// 计算各(s,i)的比率
    while (it_one_dim_hist != one_dim_hist.end())
    {
        it_one_dim_hist->setFreq(it_one_dim_hist->getFreq() / total_pixels);
        it_one_dim_hist++;
    }
    sort(one_dim_hist.begin(), one_dim_hist.end(),
        [](const FeatureInfo& x, const FeatureInfo& y)->bool{return x.getFreq() > y.getFreq(); }); // 按(s,i)频率降序排列

    // 特征降维并输出
    //return outputToBuffer(one_dim_hist, feas_str, feas_str_max_len);
    return 0;

}

// 输出特征到缓冲buffer。返回特征串所占字节数。返回-1表示缓冲区长度不够。
int outputToBuffer(const vector<FeatureInfo>& feas, char* buffer, int fea_str_max_len)
{
    stringstream outstream;
    size_t feas_count = 0;
    double total_ratio = 0;
    vector<FeatureInfo>::const_iterator it_feas = feas.begin();
    while (it_feas < feas.end() && total_ratio < 0.8 && feas_count < 100) // 截取到占像素总数80%的特征位置作为图像特征,且特征个数最多100个
    {
        outstream << it_feas->getHSLocation() << '\t';
        total_ratio += it_feas->getFreq();
        feas_count++;
        it_feas++;
    }
    if (feas_count < 69) // 如果截取后特征数量<69,则返回最多100个特征
    {
        while (it_feas < feas.end() && feas_count < 100)
        {
            outstream << it_feas->getHSLocation() << '\t';
            it_feas++;
            feas_count++;
        }
    }


    if (outstream.str().size() <= static_cast<unsigned int>(fea_str_max_len))
    {
        strcpy(buffer, outstream.str().c_str());
        buffer[outstream.str().size()] = '\0';
        return outstream.str().size();
    }
    else
    {
        return -1;
    }
}



void generate_feature_test()
{
    getSimilarityFeature("./images", "lena.jpg", "test", 10);
}

