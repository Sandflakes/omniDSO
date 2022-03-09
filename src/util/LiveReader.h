
#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "util/NumType.h"
#include "util/Undistort.h"

#include "IOWrapper/ImageRW.h"

using namespace std;

namespace dso
{
    class LiveReader
    {
    public:
        LiveReader(string calibPath);
        ~LiveReader();

        Undistort* undistort;
    private:
        string calibPath;
        
        int width, height;
        int widthOrg, heightOrg;
    };
}