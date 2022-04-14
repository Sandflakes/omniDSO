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
#include "util/webcamReader.h"

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
    int frameCount = 0;
    ImageAndExposure *img;
    Mat frame;
    WebcamReader* reader = new WebcamReader(calibration, 2);

    FullSystem *fullSystem = new FullSystem();
    // fullSystem->setGammaFunction(reader->getPhotometricGamma());
    fullSystem->linearizeOperation = true;

    while (1)
    {
        // webcam.read(frame);
        // if (frame.empty())
        //     break;

        // img = IOWrap::readWebcamBW_8U(&webcam);
        // img = readWebcamBW_8U(&webcam);

        fullSystem->addActiveFrame(img, frameCount);

        // imshow("Frame", frame);

        // Press  ESC on keyboard to exit
        if ((char)waitKey(25) == 27)
            break;

        frameCount++;
    }
    
    printf("DELETE FULLSYSTEM!\n");
    delete fullSystem;

    printf("DELETE READER!\n");
    delete reader;

    destroyAllWindows();

    return 0;
}
