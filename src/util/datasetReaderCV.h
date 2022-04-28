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
    class DatasetReaderCV
    {
    private:
        string calibPath;
        std::vector<std::string> files;
        clock_t started;

        vector<cv::String> fn;

        int width, height;
        int widthOrg, heightOrg;

        int frameCount;
        int currFrame = 0;

        ImageAndExposure* getImage_internal();

    public:
        Undistort *undistort;

        DatasetReaderCV(string calibPath, String path);
        ~DatasetReaderCV();

        void setGlobalCalibration();
        ImageAndExposure* getImage();
        void getCalibMono(Eigen::Matrix3f &K, int &w, int &h);
        float* getPhotometricGamma();
    };
}