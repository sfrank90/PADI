//local
#include "VideoThread.h"

VideoThread::VideoThread(VideoImageBuffer *videoImageBuffer, int deviceNumber, bool dropFrameIfBufferFull) : QThread(), videoImageBuffer(videoImageBuffer)
{
    // save passed params
	this->deviceNumber=deviceNumber;
	this->dropFrameIfBufferFull=dropFrameIfBufferFull;

	// Initialize variables(s)
    doStop=false;
}

void VideoThread::run()
{
    while(1)
    {
        ////////////////////////////////
        // Stop thread if doStop=TRUE //
        ////////////////////////////////
        doStopMutex.lock();
        if(doStop)
        {
            doStop=false;
            doStopMutex.unlock();
            break;
        }
        doStopMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        // Capture frame (if available)
        if (!cap.grab())
            continue;

        // Retrieve frame
        if(!cap.retrieve(grabbedFrame))
        {
            std::cout << "Fail reading images. Cam locked" << std::endl;
            continue;
        }

		// Add frame to buffer
        videoImageBuffer->getByDeviceNumber(deviceNumber)->add(grabbedFrame, dropFrameIfBufferFull);
    }
    std::cout << "Stopping capture thread..." << std::endl;
}

bool VideoThread::connectToCamera()
{
    // Open camera
    bool camOpenResult = cap.open(deviceNumber);
    if(!camOpenResult)
        std::cout << "Cam still locked" << std::endl;
 
    // Return result
    return camOpenResult;
}

bool VideoThread::disconnectCamera()
{
    // Camera is connected
    if(cap.isOpened())
    {
        std::cout << "release cam" << std::endl;
        // Disconnect camera
        cap.release();
        return true;
    }
    // Camera is NOT connected
    else
        return false;
}

void VideoThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;
}

bool VideoThread::isCameraConnected()
{
    return cap.isOpened();
}

int VideoThread::getInputSourceWidth()
{
    return cap.get(CV_CAP_PROP_FRAME_WIDTH);
}

int VideoThread::getInputSourceHeight()
{
    return cap.get(CV_CAP_PROP_FRAME_HEIGHT);
}
