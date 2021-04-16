#include "libxtg_.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//storing surface meta data
struct meta {
    string content{};
    int distanceUnit{};
    int dataUnit{};
    int ncol{};
    int nrow{};
    float Xstep{};
    float Ystep{};
    string mapType{};
    float origX{};
    float origY{};
    float rotation{};
    float rotationOrigX{};
    float rotationOrigY{};
    int undef{};
    float version{};
};

//floating point precision
float FLOATEPS{ 1.0E-05 };

//read PMD
int surf_im_petromod_bin(FILE *fc,
    struct meta *mdata,
    vector<double>*surfzv)
{
    
    fseek(fc, 0, SEEK_SET);

    /* check endianess */
    int swap = 0;
    if (x_swap_check() == 1)
        swap = 1;

    float myfloat;
    if (fread(&myfloat, 4, 1, fc) != 1)
        //failed
        { }
    if (swap)
     { //test read
        SWAP_FLOAT(myfloat);
    }
        
    //Find metadata
    char dsc[400];
    int ier = fscanf(fc, "%300s", dsc);
    string param(dsc);

    //parsing metadata
    istringstream stream(param);
    int i = 0;
    while (stream.good()) {
        string substr;
        getline(stream, substr, '=');
        string subsubstr;
        istringstream substr_stream(substr);
        getline(substr_stream, subsubstr, ',');
        if (i == 2) {
            int x = stoi(subsubstr);
            mdata->distanceUnit = x;
        }
        else if (i==3) {
            int x = stoi(subsubstr);
            mdata->dataUnit = x;
        }
        else if (i == 4) {
            int x = stoi(subsubstr);
            mdata->ncol = x;
        }
        else if (i == 5) {
            int x = stoi(subsubstr);
            mdata->nrow = x;
        }
        else if (i == 6) {
            float x = stoi(subsubstr);
            mdata->Xstep = x;
        }
        else if (i == 7) {
            float x = stoi(subsubstr);
            mdata->Ystep = x;
        }
        else if (i == 9) {
            float x = stoi(subsubstr);
            mdata->origX = x;
        }
        else if (i == 10) {
            float x = stoi(subsubstr);
            mdata->origY = x;
        }
        else if (i == 11) {
            float x = stoi(subsubstr);
            mdata->rotation = x;
        }
        else if (i == 14) {
            int x = stoi(subsubstr);
            mdata->undef = x;
        }
        i++;        
    }

    //Move pointer to the first data
    int nlen = strnlen(dsc, 500);   
    fseek(fc, nlen+5, SEEK_SET);

    /* Try to allocate memory
    surfzv->resize(mdata->nrow* mdata->ncol);
    */
    
    //Parse data into vector
    int in{ 0 }, jn{ 0 };
    long ic{0};
    if (swap) {
        for (in = 0; in < mdata->ncol; in++) {
            for (jn = 0; jn < mdata->nrow; jn++) {
                fread(&myfloat, 4, 1, fc);
                SWAP_FLOAT(myfloat);
                if (fabs(myfloat - mdata->undef) < FLOATEPS) {
                    myfloat = mdata->undef;
                }
                surfzv->push_back((double)myfloat);
            }
        }
    }
    else {
        for (in = 0; in < mdata->ncol; in++) {
            for (jn = 0; jn < mdata->nrow; jn++) {
                fread(&myfloat, 4, 1, fc);
                if (fabs(myfloat - mdata->undef) < FLOATEPS) {
                    myfloat = mdata->undef;
                }
                surfzv->push_back((double)myfloat);
            }
        }
    }

    return 0;
}
