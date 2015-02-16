//local
#include "RecordVideoThread.h"

//std
#include <stdint.h>

RecordVideoThread::RecordVideoThread(QString filename, int height, int width) : QThread()
{
    // save passed params
    this->fn = filename;
    this->rec_height = height;
    this->rec_width = width;

    // Initialize variables(s)
    doStop=false;
}

void RecordVideoThread::run()
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
    }
}

bool RecordVideoThread::createVideoWriter()
{
    if(vid_writer.open(fn.toStdString(), CV_FOURCC('M', 'P', '4', '2'), 5.0, cvSize((int)rec_width,(int)rec_height), true))
        // After successfully created writer return true
        return true;
    else
        return false;
}

void RecordVideoThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;

    vid_writer.release();
}

void RecordVideoThread::addRecFrame(const Mat &frame)
{
    QMutexLocker locker(&recordingMutex);
    vid_writer.write(frame);
}




