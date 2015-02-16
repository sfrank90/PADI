#ifndef PLAYBACKTHREAD_H
#define PLAYBACKTHREAD_H

// local
#include "FaceDetection.h"
#include "ImageConversion.h"

// Qt
#include <QtCore/QThread>
#include <QtCore/QQueue>
#include <QMutex>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// Local

using namespace cv;

//! Playback class which creates a thread to play a video.
/*!
    Thread creating class to playback a video from file.
*/
class PlaybackThread : public QThread
{
    Q_OBJECT

    public:
        //! Thread constructor class.
        /*!
        \param filename a QString argument which contains the video filename.
        */
        PlaybackThread(QString filename);
        //! Set stop flag for thread worker.
        /*!
        */
        void stop();
        //! Function to load video file to VideoCapture.
        /*!
        */
        bool loadPlayback();

    private:
        //! FaceDetection.
        /*!
        Pointer to instance of FaceDetection class.
        */
        FaceDetection *faceDetection;
        //! QMutex.
        /*!
        Mutex to stop the thread.
        */
        QMutex doStopMutex;
        //! QMutex.
        /*!
        Mutex which is set while processing the image.
        */
        QMutex processingMutex;
        //! Bool.
        /*!
        Boolean value to stop the thread.
        */
        volatile bool doStop;
        //! VideoCapture.
        /*!
        VideoCapture reads in the images from the given file.
        */
        VideoCapture cap;
        //! Mat.
        /*!
        Grabbed frame from the video file.
        */
        Mat grabbedFrame;
        //! QPixmap.
        /*!
        Converted image in QPixmap format which will be emitted to main window to display
        */
        QPixmap frame;
        //! QString.
        /*!
        Filename of the video file.
        */
        QString fn;
        //! Integer.
        /*!
        Integer value which contains the framerate.
        */
        int fps;
        //! Integer.
        /*!
        Integer value which contains the number of grabbed frames.
        */
        int frames;
        //! Integer.
        /*!
        Integer counter value.
        */
        int counter;
        //! Boolean.
        /*!
        Boolean value to make detection or not.
        */
        bool detectionState;

        //! ImageProcessingFlags struct.
        /*!
        Structure which contains information about the flags.
        */
        struct ImageProcessingFlags imgProcFlags;
        //! ImageProcessingSettings struct.
        /*!
        Structure which contains information about the settings.
        */
        struct ImageProcessingSettings imgProcSettings;

    protected:
        //! Thread function which runs till doStop is set to true.
        /*!
        To function is the worker of the thread. It does all the calls to detection functions and emits new images.
        */
        void run();

    private slots:
        //! Private slot to update the ImageProcessingFlags.
        /*!
        \param imgProcFlags a ImageProcessingFlags struct.
        */
        void updateImageProcessingFlags(struct ImageProcessingFlags);
        //! Private slot to update the ImageProcessingSettings.
        /*!
        \param imgProcSettings a ImageProcessingSettings struct.
        */
        void updateImageProcessingSettings(struct ImageProcessingSettings);
        //! Private slot to update the detection state.
        /*!
        \param flag a bool value.
        */
        void updateDetState(bool);

    signals:
        //! Signal: Next frame.
        /*!
        This signale emits the next frame to the main window to display it.
        \param frame a QPixmap image.
        */
        void nextFrame(const QPixmap &frame);
};

#endif // PLAYBACKTHREAD_H
