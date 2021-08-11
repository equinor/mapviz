/*
 ***************************************************************************************
 *
 * NAME:
 *    surf_import_petromod_bin.c
 *
 *
 * DESCRIPTION:
 *    Imports a surface map on Petromod pdm binary format.
 *
 * ARGUMENTS:
 *    fhandle        i     Filehandle (steered from caller)
 *    mode           i     0 = scan mode to find mx, my, etc; 1 = normal mode
 *    undef          i     Undef value in file (evaluated from dsc after scan)
 *    dsc            o     The description field (will be parsed in Python)
 *    mx             i     Map dimension X (I) pointer
 *    my             i     Map dimension Y (J) pointer
 *    surfzv         o     1D pointer to map/surface values pointer array
 *    nsurf          i     No. of map nodes (for allocation from Python/SWIG)
 *
 * RETURNS:
 *    Void, pointer arrays are updated

 * TODO/ISSUES/BUGS/NOTES:
 *
 * LICENCE:
 *    See XTGeo licence
 ***************************************************************************************
 */

#include "libxtg_.h"
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


//floating point precision
float FLOATEPS{ 1.0E-05 };

//scan PMD
int surf_scan_petromod_bin(FILE* fc,
    vector<float>* arr)
{

    fseek(fc, 0, SEEK_SET);

    /* check endianess */
    int swap = 0;
    if (x_swap_check() == 1)
        swap = 1;

    float myfloat;
    if (fread(&myfloat, 4, 1, fc) != 1)
        //failed
    {
    }
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
    int ncol, nrow, undef;
    float Xstep, Ystep, origX, origY;
    while (stream.good()) {
        string substr;
        getline(stream, substr, '=');
        string subsubstr;
        istringstream substr_stream(substr);
        getline(substr_stream, subsubstr, ',');

        if (i == 4) {
            ncol = stoi(subsubstr);
            arr->push_back((float)ncol);
        }
        else if (i == 5) {
            nrow = stoi(subsubstr);
            arr->push_back((float)nrow);
        }
        else if (i == 6) {
            Xstep = stoi(subsubstr);
            arr->push_back((float)Xstep);
        }
        else if (i == 7) {
            Ystep = stoi(subsubstr);
            arr->push_back((float)Ystep);
        }
        else if (i == 9) {
            origX = stoi(subsubstr);
            arr->push_back((float)origX);
        }
        else if (i == 10) {
            origY = stoi(subsubstr);
            arr->push_back((float)origY);
        }
        else if (i == 14) {
            undef = stoi(subsubstr);
            arr->push_back((float)undef);
        }
        i++;
    }
    return 0;
}



//read PMD
int surf_im_petromod_bin(FILE *fc,
    vector<float> *arr)
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
    int ncol, nrow, undef;
    float Xstep, Ystep, origX, origY;
    while (stream.good()) {
        string substr;
        getline(stream, substr, '=');
        string subsubstr;
        istringstream substr_stream(substr);
        getline(substr_stream, subsubstr, ',');

        if (i == 4) {
            ncol = stoi(subsubstr);
            arr->push_back((float)ncol);
        }
        else if (i == 5) {
            nrow = stoi(subsubstr);
            arr->push_back((float)nrow);
        }
        else if (i == 6) {
            Xstep = stoi(subsubstr);
            arr->push_back((float)Xstep);
        }
        else if (i == 7) {
            Ystep = stoi(subsubstr);
            arr->push_back((float)Ystep);
        }
        else if (i == 9) {
            origX = stoi(subsubstr);
            arr->push_back((float)origX);
        }
        else if (i == 10) {
            origY = stoi(subsubstr);
            arr->push_back((float)origY);
        }
        else if (i == 14) {
            undef = stoi(subsubstr);
            arr->push_back((float)undef);
        }
        i++;
    }

    //Move pointer to the first data
    int nlen = strnlen(dsc, 500);   
    fseek(fc, nlen+5, SEEK_SET);


    int count = 0;
    //Parse data into vector
    int in{ 0 }, jn{ 0 };
    long ic{0};
    //ncol = no of X

    int nnode = 6;
    if (swap) {
        for (in = 0; in < ncol; in++) {
            for (jn = 0; jn < nrow; jn++) {
                fread(&myfloat, 4, 1, fc);
                SWAP_FLOAT(myfloat);
                if (fabs(myfloat - undef) < FLOATEPS) {
                    myfloat = std::nanf("");
                }
                arr->push_back(myfloat*-1);
                nnode += 1;
                count += 1;
            }
        }
    }
    else {
        for (in = 0; in < ncol; in++) {
            for (jn = 0; jn < nrow; jn++) {
                fread(&myfloat, 4, 1, fc);
                if (fabs(myfloat - undef) < FLOATEPS) {
                    myfloat = std::nanf("");
                }
                arr->push_back(myfloat*-1);
                nnode += 1;
                count += 1;
            }
        }
    }

    return 0;
}
