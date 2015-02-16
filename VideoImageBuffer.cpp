#include "VideoImageBuffer.h"

VideoImageBuffer::VideoImageBuffer()
{
}

void VideoImageBuffer::add(int deviceNumber, Buffer<Mat>* imageBuffer)
{
    // Add image buffer to map
    imageBufferMap[deviceNumber]=imageBuffer;
}

Buffer<Mat>* VideoImageBuffer::getByDeviceNumber(int deviceNumber)
{
    return imageBufferMap[deviceNumber];
}

void VideoImageBuffer::removeByDeviceNumber(int deviceNumber)
{
    // Remove buffer for device from imageBufferMap
    imageBufferMap.remove(deviceNumber);

    // Also remove from syncSet (if present)
    mutex.lock();
    if(syncSet.contains(deviceNumber))
    {
        syncSet.remove(deviceNumber);
        wc.wakeAll();
    }
    mutex.unlock();
}

void VideoImageBuffer::wakeAll()
{
    QMutexLocker locker(&mutex);
    wc.wakeAll();
}


bool VideoImageBuffer::containsImageBufferForDeviceNumber(int deviceNumber)
{
    return imageBufferMap.contains(deviceNumber);
}
