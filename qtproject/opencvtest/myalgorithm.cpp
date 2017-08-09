#include <QDebug>
#include <QDir>
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

/**
*
1,Make a class and specify Algorithm as its base class.
2,The algorithm parameters should be the class members. See Algorithm::get() for the list of possible types of the parameters.
3,Add public virtual method AlgorithmInfo* info() const; to your class.
4,Add constructor function, AlgorithmInfo instance and implement the info() method.
5,Add some public function (e.g. initModule_<mymodule>()) that calls info() of your algorithm and put it into the same source file as info() implementation. This is to force C++ linker to include this object file into the target application. See Algorithm::create() for details.
************/

Algorithm* CreateMyOpencvAlgorithm();
AlgorithmInfo& MyOpencvAlgorithmInfo();

class MyOpencvAlgorithm : public cv::Algorithm
{
    public:
        virtual AlgorithmInfo* info() const;
        void Do() { cout<<"=== Do MyOpencv Algorithm! ==="<<endl; }
        void Do2() {cout<<"do2222222222222222..."<<endl;}
};

AlgorithmInfo* MyOpencvAlgorithm::info() const
{
    return &(MyOpencvAlgorithmInfo());
}


Algorithm* CreateMyOpencvAlgorithm()
{
    return new MyOpencvAlgorithm;
}

AlgorithmInfo& MyOpencvAlgorithmInfo()
{
    static AlgorithmInfo info("MyOpencvAlgorithm", CreateMyOpencvAlgorithm);
    return info;
}

bool initModule_MyOpencv()
{
    Ptr<Algorithm> p = CreateMyOpencvAlgorithm();
    return p->info() != NULL;
}


void myalgorithm_test()
{
    cout <<"myalgorithm_test"<<endl;
    initModule_MyOpencv();
    Ptr<MyOpencvAlgorithm> pm = Algorithm::create<MyOpencvAlgorithm>("MyOpencvAlgorithm.Do2");
    pm->Do();
    pm->Do2();
}



