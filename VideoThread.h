#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

// local
#include "VideoImageBuffer.h"

// Qt
#include <QtCore/QTime>
#include <QtCore/QThread>
// OpenCV
#include <opencv2/highgui/highgui.hpp>
// Local

using namespace cv;

//! Video class which cpatures an image from a webcam or specific device.
/*!
    Thread to capture images.
*/
class VideoThread : public QThread
{
    Q_OBJECT

    public:
        //! Thread constructor class.
        /*!
        \param videoImageBuffer pointer to a buffer which contains the captured images.
        \param deviceNumber an integer argument.
        \param dropFrameIfBufferFull a bool value to set if images shall be dropped when the buffer is full.
        */
        VideoThread(VideoImageBuffer *videoImageBuffer, int deviceNumber, bool dropFrameIfBufferFull);
        //! Set stop flag for thread worker.
        /*!
        */
        void stop();
        //! Function to create a camera connection.
        /*!
          \return Returns true when attempt was successful.
        */
        bool connectToCamera();
        //! Function to disconnect a camera connection.
        /*!
          \return Returns true when attempt was successful.
        */
        bool disconnectCamera();
        //! Function to check if a camera is connected.
        /*!
          \return Returns true when a camera is connected.
        */
        bool isCameraConnected();
        //! Function to get the camera input width of an image.
        /*!
          \return Returns the width as an integer value.
        */
        int getInputSourceWidth();
        //! Function to get the camera input height of an image.
        /*!
          \return Returns the height as an integer value.
        */
        int getInputSourceHeight();

    private:
        //! VideoImageBuffer.
        /*!
        Pointer to buffer which contains the images.
        */
		VideoImageBuffer *videoImageBuffer;
        //! VideoCapture.
        /*!
        Variable to store the camera connection. From OpenCV lib.
        */
        VideoCapture cap;
        //! Mat image.
        /*!
        Grabbed frame from input source.
        */
        Mat grabbedFrame;
        //! QMutex.
        /*!
        Mutex to stop the thread.
        */
        QMutex doStopMutex;
        //! Bool.
        /*!
        Boolean value to stop the thread.
        */
        volatile bool doStop;
        //! Integer.
        /*!
        Integer value for device number.
        */
        int deviceNumber;
        //! Bool.
        /*!
        Boolean value if a frame shall be dropped when the buffer is full.
        */
		bool dropFrameIfBufferFull;


    protected:
        //! Thread function which runs till doStop is set to true.
        /*!
        To function is the worker of the thread. It does all the calls to detection functions and emits new images.
        */
        void run();
};

#endif // VIDEOTHREAD_H
