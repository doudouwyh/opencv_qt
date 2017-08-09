#include"gdal.h"
#include"gdal_priv.h"

#include <iostream>
using namespace std;

int gdal_demo_test()
{
    cout <<"gdal_demo_test..."<<endl;

    const char* fileName = "./images/N37W123.hgt";
    GDALDataset *poDataset;
    GDALAllRegister();
    poDataset = (GDALDataset*)GDALOpen(fileName, GA_ReadOnly);
    if (poDataset == NULL){
        cout << "open failed" << endl;
    }
    else{
        cout << "open successed" << endl;
    }

    int tmpCols = poDataset->GetRasterXSize();
    int tmpRows = poDataset->GetRasterYSize();
    int tmpBandSize = poDataset->GetRasterCount();

    cout<<"cols:"<<tmpCols<<endl;
    cout<<"rows:"<<tmpRows<<endl;
    cout<<"bandsize:"<<tmpBandSize<<endl;

    return 0;
}
