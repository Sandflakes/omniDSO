#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "util/NumType.h"
#include "util/Undistort.h"

#include "IOWrapper/ImageRW.h"

using namespace std;
using namespace cv;

namespace dso
{
    class WebcamReader
    {
    private:
        VideoCapture webcam;
        string calibPath;
        std::vector<std::string> files;

        int width, height;
        int widthOrg, heightOrg;


        ImageAndExposure* getImage_internal();

    public:
        Undistort *undistort;

        WebcamReader(string calibPath, int videoID);
        ~WebcamReader();

        void setGlobalCalibration();
        ImageAndExposure* getImage();
        void getCalibMono(Eigen::Matrix3f &K, int &w, int &h);
        float* getPhotometricGamma();
    };
}