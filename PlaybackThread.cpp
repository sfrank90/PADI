//local
#include "PlaybackThread.h"

//std
#include <stdint.h>

PlaybackThread::PlaybackThread(QString filename) : QThread()
{
    // save passed params
    this->fn = filename;

    // Initialize variables(s)
    doStop=false;
    faceDetection = new FaceDetection();
}

void PlaybackThread::run()
{
    counter = 0;
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
        //processingMutex.lock();

        // Grab frame from file
        //cap >> grabbedFrame;
        bool bSuccess = cap.read(grabbedFrame);

        // stop after finishing video file
        if(grabbedFrame.empty())
            return;

        if(!bSuccess)
            std::cout << "Failed on reading frame" << std::endl;

        // Check settings and flags cout
        //std::cout << "Flags: Detection - " << imgProcFlags.showDetectionOn << " | Overlay - " << imgProcFlags.showOverlaysOn << std::endl;
        //std::cout << "Settings: Param1 - " << imgProcSettings.overlayParam1 << " | Param2 - " << imgProcSettings.overlayParam2 << " | Param3 - " << imgProcSettings.overlayParam3 << std::endl;

        // Detect objects in frame
        if(detectionState)
            grabbedFrame = faceDetection->detectObjects(grabbedFrame, imgProcSettings, imgProcFlags);
        if(!detectionState)
            usleep((1000 * 1000) / fps);

        // Convert frame to QPixmap
        frame=cvMatToQPixmap(grabbedFrame);

        processingMutex.unlock();

        // emit converted frame
        emit nextFrame(frame);

    }
}

bool PlaybackThread::loadPlayback()
{
    // load file for read out
    cap.open(this->fn.toStdString());
    if(!cap.isOpened())
        return false;

    fps = (int)cap.get(CV_CAP_PROP_FPS);

    // After successfully loaded return true
    return true;
}

void PlaybackThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;

    cap.release();

    // delete facedetection pointer if playback thread stopped
    std::cout << "Delete FaceDetection reference" << std::endl;
    delete faceDetection;
}

void PlaybackThread::updateImageProcessingFlags(struct ImageProcessingFlags imgProcFlags)
{
    QMutexLocker locker(&processingMutex);
    this->imgProcFlags.showDetectionOn=imgProcFlags.showDetectionOn;
    this->imgProcFlags.showOverlaysOn=imgProcFlags.showOverlaysOn;
}

void PlaybackThread::updateImageProcessingSettings(struct ImageProcessingSettings imgProcSettings)
{
    QMutexLocker locker(&processingMutex);
    this->imgProcSettings.overlayParam1=imgProcSettings.overlayParam1;
    this->imgProcSettings.overlayParam2=imgProcSettings.overlayParam2;
    this->imgProcSettings.overlayParam3=imgProcSettings.overlayParam3;
}

void PlaybackThread::updateDetState(bool flag)
{
    this->detectionState = flag;
}

