#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>

#include "util/settings.h"
#include "util/globalFuncs.h"
#include "util/globalCalib.h"
#include "util/webcamReader.h"

namespace dso
{
    WebcamReader::WebcamReader(std::string calibPath, int videoID)
    {
        this->calibPath = calibPath;
        
        if (!this->webcam.open(videoID))
        {
            printf("Error opening video stream on device %i\n", videoID);
            return;
        }

        undistort = Undistort::getUndistorterForFile(calibPath + "camera.txt", calibPath + "pcalib.txt", calibPath + "vignette.png");

        this->widthOrg = undistort->getOriginalSize()[0];
        this->heightOrg = undistort->getOriginalSize()[1];
        this->width = undistort->getSize()[0];
        this->height = undistort->getSize()[1];
    }

    void WebcamReader::getCalibMono(Eigen::Matrix3f &K, int &w, int &h)
    {
        K = undistort->getK().cast<float>();
        w = undistort->getSize()[0];
        h = undistort->getSize()[1];
    }
    
    ImageAndExposure* WebcamReader::getImage_internal()
    {
        MinimalImageB *minimg = IOWrap::readWebcamBW_8U(&this->webcam);
        ImageAndExposure *ret2 = this->undistort->undistort<unsigned char>( minimg, 1, 0);
        delete minimg;
        return ret2;
    }

    ImageAndExposure* WebcamReader::getImage()
    {
        return getImage_internal();
    }

    float* WebcamReader::getPhotometricGamma()
    {
        if (undistort == 0 || undistort->photometricUndist == 0)
            return 0;
        return undistort->photometricUndist->getG();
    }

    void WebcamReader::setGlobalCalibration()
    {
        int w_out, h_out;
        Eigen::Matrix3f K;
        getCalibMono(K, w_out, h_out);
        setGlobalCalib(w_out, h_out, K);
    }

    WebcamReader::~WebcamReader()
    {
        this->webcam.release();
    }
}