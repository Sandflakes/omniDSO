#include "util/LiveReader.h"

namespace dso
{
    LiveReader::LiveReader(std::string calibPath)
    {
        this->calibPath = calibPath;

        this->widthOrg = undistort->getOriginalSize()[0];
        this->heightOrg = undistort->getOriginalSize()[1];
        this->width = undistort->getSize()[0];
        this->height = undistort->getSize()[1];
        
    }
}
