#include "boost/thread.hpp"
#include "util/MinimalImage.h"
#include "IOWrapper/Output3DWrapper.h"

#include "FullSystem/HessianBlocks.h"
#include "util/FrameShell.h"

#include "IOWrapper/OutputWrapper/multiOutputWrapper.h"
namespace dso
{
    class FrameHessian;
    class CalibHessian;
    class FrameShell;

    namespace IOWrap
    {

        MultiOutputWrapper::MultiOutputWrapper()
        {
            printf("OUT: Created MultiOutputWrapper\n");
        }

        MultiOutputWrapper::~MultiOutputWrapper()
        {
            printf("OUT: Destroyed MultiOutputWrapper\n");
        }

        void MultiOutputWrapper::publishGraph(const std::map<uint64_t, Eigen::Vector2i, std::less<uint64_t>, Eigen::aligned_allocator<std::pair<const uint64_t, Eigen::Vector2i>>> &connectivity)
        {
            // printf("OUT: got graph with %d edges\n", (int)connectivity.size());

            for (const std::pair<uint64_t, Eigen::Vector2i> &p : connectivity)
            {
                // int idHost = p.first >> 32;
                // int idTarget = p.first & ((uint64_t)0xFFFFFFFF);
                // printf("OUT: Example Edge %d -> %d has %d active and %d marg residuals\n", idHost, idTarget, p.second[0], p.second[1]);
            }
        }

        void MultiOutputWrapper::publishKeyframes(std::vector<FrameHessian *> &frames, bool final, CalibHessian *HCalib)
        {
            // printf("Frames: %lu\n", frames.size());
            for (FrameHessian *f : frames)
            {
                // printf("OUT: KF %d (%s) (id %d, tme %f): %d active, %d marginalized, %d immature points. CameraToWorld:\n",
                //        f->frameID,
                //        final ? "final" : "non-final",
                //        f->shell->incoming_id,
                //        f->shell->timestamp,
                //        (int)f->pointHessians.size(), (int)f->pointHessiansMarginalized.size(), (int)f->immaturePoints.size());
                // std::cout << f->shell->camToWorld.matrix3x4() << "\n";

                // Perform action on all points in the pointcloud
                for (PointHessian *p : f->pointHessians)
                {
                    
                }
            }
        }

        void MultiOutputWrapper::publishCamPose(FrameShell *frame, CalibHessian *HCalib)
        {
            printf("OUT: Current Frame %d (time %f, internal ID %d camera ID: %d). CameraToWorld:\n",
                   frame->incoming_id,
                   frame->timestamp,
                   frame->id,
                   frame->camId);
            std::cout << frame->camToWorld.matrix3x4() << "\n";
        }

        void MultiOutputWrapper::pushLiveFrame(FrameHessian *image)
        {
            // can be used to get the raw image / intensity pyramid.
        }

        void MultiOutputWrapper::pushDepthImage(MinimalImageB3 *image)
        {
            // can be used to get the raw image with depth overlay.
        }
        bool MultiOutputWrapper::needPushDepthImage()
        {
            return false;
        }

        void MultiOutputWrapper::pushDepthImageFloat(MinimalImageF *image, FrameHessian *KF)
        {
            // printf("OUT: Predicted depth for KF %d (id %d, time %f, internal frame ID %d, camera ID %d). CameraToWorld:\n",
            //        KF->frameID,
            //        KF->shell->incoming_id,
            //        KF->shell->timestamp,
            //        KF->shell->id,
            //        KF->shell->camId);
            // std::cout << KF->shell->camToWorld.matrix3x4() << "\n";

            for (int y = 0; y < image->h; y++)
            {
                // for (int x = 0; x < image->w; x++)
                // {
                //     if (image->at(x, y) <= 0)
                //         continue;

                //     printf("OUT: Example Idepth at pixel (%d,%d): %f.\n", x, y, image->at(x, y));
                //     maxWrite--;
                //     if (maxWrite == 0)
                //         break;
                // }
            }
        }
    }
}
