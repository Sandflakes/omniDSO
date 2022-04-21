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

bool showHelp = 0;
uint videoID = 0;
std::string calib = "";

void parseArgument(char *arg)
{
    int option;
    char buf[1000];

    if (strcmp(arg,"-h")==0)
    {
        showHelp = 1;
        printf("Usage:\n");
        printf("-h           = Display this help section\n");
        printf("-vid=0       = VideoID for the webcam (see <ls /dev/video*>)\n");
        printf("-c=\"/\"        = Calibration file location relative to the executable\n");
        return;
    }

    if (1 == sscanf(arg, "-vid=%d", &option))
    {
        videoID = option;
        printf("VideoID is set to %i!\n", videoID);
        return;
    }
    if (1 == sscanf(arg, "-c=%s", buf))
    {
        calib = buf;
        printf("loading calibration from %s!\n", calib.c_str());
        return;
    }
}


void camThread(uint id)
{
    printf("I am %i\n", id);
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
        parseArgument(argv[i]);

    if(showHelp)
        return 0;

    int frameCount = 0;
    ImageAndExposure *img;
    Mat frame;
    
    WebcamReader* reader = new WebcamReader(calib, videoID);

    FullSystem *fullSystem = new FullSystem();
    // fullSystem->setGammaFunction(reader->getPhotometricGamma());
    fullSystem->linearizeOperation = true;

    // list<boost::thread> threads = new list<boost::thread>();

    // for (int i = 0; i < 4; i++)
    //     boost::thread thread{camThread,i};


    printf("Entering loop\n");

    while (1)
    {
        // webcam.read(frame);
        // if (frame.empty())
        //     break;

        // img = IOWrap::readWebcamBW_8U(&webcam);
        // img = readWebcamBW_8U(&webcam);

        printf("Get Image\n");
        img = reader->getImage();

        printf("Add Frame\n");
        fullSystem->addActiveFrame(img, frameCount);

        if(fullSystem->initFailed)
            printf("Init Failed\n");

        if(fullSystem->isLost)
            printf("Lost\n");

        if(fullSystem->initialized)
            printf("Initialized\n");
            
        // imshow("Frame", frame);

        // Press  ESC on keyboard to exit
        // if ((char)waitKey(25) == 27)
        //     break;


        delete img;
        frameCount++;
    }
    
    printf("DELETE FULLSYSTEM!\n");
    delete fullSystem;

    printf("DELETE READER!\n");
    delete reader;

    destroyAllWindows();

    return 0;
}
