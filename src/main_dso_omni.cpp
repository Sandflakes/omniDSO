#include <thread>
#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "IOWrapper/Output3DWrapper.h"
#include "IOWrapper/ImageDisplay.h"

#include <boost/thread.hpp>
#include "util/settings.h"
#include "util/globalFuncs.h"
#include "util/globalCalib.h"
#include "util/LiveReader.h"

#include "util/NumType.h"
#include "FullSystem/FullSystem.h"
#include "OptimizationBackend/MatrixAccumulators.h"
#include "FullSystem/PixelSelector2.h"

#include "IOWrapper/OutputWrapper/SampleOutputWrapper.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace dso;

std::string calibration = "";

int main(int argc, char **argv)
{
    MinimalImageB *img;
    VideoCapture webcam(2);
    // Check if camera opened successfully

    if (!webcam.isOpened())
    {
        printf("Error opening video stream or file");
        return -1;
    }

    while (1)
    {

        // webcam >> frame;
        // if (frame.empty())
        //     break;
        
        img = IOWrap::readWebcamBW_8U(&webcam);
        // imshow("Frame", frame);

        // Press  ESC on keyboard to exit
        if ((char)waitKey(25) == 27)
            break;
    }

    webcam.release();

    destroyAllWindows();

    return 0;
}
