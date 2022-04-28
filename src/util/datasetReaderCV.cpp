#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>

#include "util/settings.h"
#include "util/globalFuncs.h"
#include "util/globalCalib.h"
#include "util/datasetReaderCV.h"

namespace dso
{
    DatasetReaderCV::DatasetReaderCV(std::string calibPath, String imagePath)
    {
        this->calibPath = calibPath;
        cv::glob(imagePath,this->fn,true);
        // this->frameCount = fn.size();
        this->frameCount = 500;
        this->currFrame = 0;

        undistort = Undistort::getUndistorterForFile(calibPath + "camera.txt", calibPath + "pcalib.txt", calibPath + "vignette.png");

        this->widthOrg = undistort->getOriginalSize()[0];
        this->heightOrg = undistort->getOriginalSize()[1];
        this->width = undistort->getSize()[0];
        this->height = undistort->getSize()[1];

        this->started = clock();
    }

    void DatasetReaderCV::getCalibMono(Eigen::Matrix3f &K, int &w, int &h)
    {
        K = undistort->getK().cast<float>();
        w = undistort->getSize()[0];
        h = undistort->getSize()[1];
    }
    
    ImageAndExposure* DatasetReaderCV::getImage_internal()
    {   
        MinimalImageB* minimg;
        cv::Mat img;
        do
        {
            if(currFrame >= this->frameCount)
                return NULL;

            img = cv::imread(fn[this->currFrame]);
            currFrame++;
        } while (img.empty());

        printf("Frame %d\n", currFrame);

        minimg = IOWrap::mat2MinimalBW_8U(img);

        double timestamp = 1000.0f * (clock() - this->started) / (float)(CLOCKS_PER_SEC);
        ImageAndExposure *ret2 = this->undistort->undistort<unsigned char>( minimg, 1, timestamp);
        
        delete minimg;
        return ret2;
    }

    ImageAndExposure* DatasetReaderCV::getImage()
    {
        return getImage_internal();
    }

    float* DatasetReaderCV::getPhotometricGamma()
    {
        if (undistort == 0 || undistort->photometricUndist == 0)
            return 0;
        return undistort->photometricUndist->getG();
    }

    void DatasetReaderCV::setGlobalCalibration()
    {
        int w_out, h_out;
        Eigen::Matrix3f K;
        getCalibMono(K, w_out, h_out);
        setGlobalCalib(w_out, h_out, K);
    }

    DatasetReaderCV::~DatasetReaderCV()
    {

    }
}