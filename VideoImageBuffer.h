#ifndef SHAREDIMAGEBUFFER_H
#define SHAREDIMAGEBUFFER_H

// Qt
#include <QHash>
#include <QSet>
#include <QWaitCondition>
#include <QMutex>
// OpenCV
#include <opencv/cv.h>
#include <opencv/highgui.h>
// Local
#include "Buffer.h"

using namespace cv;

//! Video buffer class
/*!
    Video buffer class to share images between two or more threads.
*/
class VideoImageBuffer
{
    public:
        //! Constructor of VideoImageBuffer.
        /*!
        */
        VideoImageBuffer();
        //! Function to add a Image buffer.
        /*!
        \param deviceNumber an integer argument with the device number.
        \param imageBuffer a pointer to the image buffer to add (Type Buffer<Mat>).
        */
        void add(int deviceNumber, Buffer<Mat> *imageBuffer);
        //! Get the buffer for specific device number.
        /*!
        \param deviceNumber an integer argument with the device number.
        \return Pointer the requested buffer of type Mat.
        */
        Buffer<Mat>* getByDeviceNumber(int deviceNumber);
        //! Remove a buffer for a specifc device number.
        /*!
        \param deviceNumber an integer argument with the device number.
        */
        void removeByDeviceNumber(int deviceNumber);
        //! Wake all QWaitConditions.
        /*!
        */
        void wakeAll();
        //! Function to check if the Video image buffer contains a buffer for a device number.
        /*!
        \param deviceNumber an integer argument with the device number.
        \return True if VideoImageBuffer contains buffer for specific device number
        */
        bool containsImageBufferForDeviceNumber(int deviceNumber);

    private:
        //! QHash<int, Buffer<Mat>*>
        /*!
        A map which contains all pointers to the added buffers
        */
        QHash<int, Buffer<Mat>*> imageBufferMap;
        //! QSet<int>
        /*!
        */
        QSet<int> syncSet;
        //! QWaitCondition
        /*!
        */
        QWaitCondition wc;
        //! QMutex
        /*!
        */
        QMutex mutex;
};

#endif // SHAREDIMAGEBUFFER_H
