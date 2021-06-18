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

val surfaceReader (string path,
    string type)
{
    int result;
    //string type = "pmd";
    const char* fpath = path.c_str();
    FILE* fp;
    fp = fopen(fpath, "rb");
    //fopen_s(&fp, fpath, "rb");
    if (type == "pmd") {
        meta data;
        vector<double> surf;
        if (!fp) {
            perror("File opening failed");
            return EXIT_FAILURE;
        }
        result = surf_im_petromod_bin(fp, &data, &surf);
        /*
        for (std::vector<double>::const_iterator i = surf.begin(); i != surf.end(); ++i)
            std::cout << *i << ' ';
        */
        //std::cout << surf[500] <<endl;
       }
    else if (type == "irapbin") {
        //not implemented
        result = 0;
    }
    else {
        result = 1;
    }

    int *a = &result;
    size_t bufferLength = sizeof(result);
    return emscripten::val(emscripten::typed_memory_view(bufferLength, a));
}

EMSCRIPTEN_BINDINGS(pmread) {
    emscripten::function("surfaceReader", &surfaceReader);
}
/*
int main(void) {
    int result = surfaceReader(filepath, surfType);
    std::cout << result;
    return result;
}

*/
