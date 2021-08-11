// pmread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "surf_import_petromod_bin.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;
using namespace std;
//string filepath = "D:/code/surface/8.pmd" ;
//string surfType = "pmd";

vector<float> surfaceScanner (string path,
    string type)
{

    const char* fpath = path.c_str();
    FILE* fp;
    vector<float> surf;
    fp = fopen(fpath, "rb");
    if (type == "pmd") {
        
        if (!fp) {
            perror("File opening failed");
        }
        surf_scan_petromod_bin(fp, &surf);
        fclose(fp);
       }
    else if (type == "irapbin") {
        //not implemented
        surf.push_back(1.0);
    }
    else {
        surf.push_back(1.0);
    }

    //size_t bufferLength = sizeof(result);
    return surf;//emscripten::val(emscripten::typed_memory_view(bufferLength, result));
}
vector<float> surfaceReader(string path,
    string type)
{

    const char* fpath = path.c_str();
    FILE* fp;
    vector<float> surf;
    fp = fopen(fpath, "rb");
    if (type == "pmd") {

        if (!fp) {
            perror("File opening failed");
        }
        surf_im_petromod_bin(fp, &surf);
        fclose(fp);
    }
    else if (type == "irapbin") {
        //not implemented
        surf.push_back(1.0);
    }
    else {
        surf.push_back(1.0);
    }

    //size_t bufferLength = sizeof(result);
    return surf;//emscripten::val(emscripten::typed_memory_view(bufferLength, result));
}
EMSCRIPTEN_BINDINGS(pmread) {
    emscripten::function("surfaceScanner", &surfaceScanner);
    emscripten::function("surfaceReader", &surfaceReader);
    register_vector<float>("vector<float>");
}

