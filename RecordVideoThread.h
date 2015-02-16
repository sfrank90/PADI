#ifndef RECORDVIDEOTHREAD_H
#define RECORDVIDEOTHREAD_H

#include <iostream>

// Qt
#include <QtCore/QThread>
#include <QtCore/QQueue>
#include <QMutex>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// Local

using namespace cv;

//! Record Video class which records the processed images from the webcam to a video file.
/*!
    Thread to record processed images.
*/
class RecordVideoThread : public QThread
{
    Q_OBJECT

    public:
        //! Thread constructor class.
        /*!
        \param filename a QString argument - Filename for recording.
        \param height an integer argument with the height of the video.
        \param width an integer argument with the width of the video.
        */
        RecordVideoThread(QString filename, int height, int width);
        //! Set stop flag for thread worker.
        /*!
        */
        void stop();
        //! Function to create a new video writer.
        /*!
          \return bool - True if successfull.
        */
        bool createVideoWriter();

    private:
        //! QMutex.
        /*!
        Mutex to stop the thread.
        */
        QMutex doStopMutex;
        //! QMutex.
        /*!
        Mutex which is set while recording the image.
        */
        QMutex recordingMutex;
        //! Bool.
        /*!
        Boolean value to stop the thread.
        */
        volatile bool doStop;

        //! VideoWriter.
        /*!
        VideoWriter from OpenCV to record video to file.
        */
        VideoWriter vid_writer;
        //! QString.
        /*!
        Filename of the recorded video.
        */
        QString fn;
        //! Integer.
        /*!
        Integer value with recording width.
        */
        int rec_width;
        //! Integer.
        /*!
        Integer value with recording height.
        */
        int rec_height;
        //! Integer.
        /*!
        Integer value with recording framerate.
        */
        int rec_fps;


    protected:
        //! Thread function which runs till doStop is set to true.
        /*!
        To function is the worker of the thread. It does all the calls to detection functions and emits new images.
        */
        void run();

    private slots:
        //! Private slot to add next image to video file.
        /*!
        \param frame a Mat image to add to recorded vide file.
        */
        void addRecFrame(const Mat &frame);
};

#endif // RECORDVIDEOTHREAD_H
