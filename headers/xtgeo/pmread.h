// pmread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "surf_import_petromod_bin.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QSurfaceDataProxy>


using namespace std;
string filepath = "D:/code/surface/8.pmd" ;
string surfType = "pmd";

vector<double> surfaceReader (string path,
                    string type)
{   
    const char* fpath = path.c_str();
    FILE* fp;
    fp = fopen(fpath, "rb");
    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    if (type == "pmd") {
        meta data;
        vector<double> surf(1);
        if (!fp) {
            perror("File opening failed");

        }
        surf_im_petromod_bin(fp, &data, &surf);
        for (std::vector<double>::const_iterator i = surf.begin(); i != surf.end(); ++i)
            std::cout << *i << ' ';
        return surf;
       }
}


