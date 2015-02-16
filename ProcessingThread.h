#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

// Qt
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QQueue>
// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
// Local
#include "Structures.h"
#include "Config.h"
#include "Buffer.h"
#include "VideoImageBuffer.h"
#include "ImageConversion.h"
#include "FaceDetection.h"

using namespace cv;

//! Processing class which does image detection in webcam mode.
/*!
    Thread processing captured images.
*/
class ProcessingThread : public QThread
{
    Q_OBJECT

    public:
        //! Thread constructor class.
        /*!
        \param videoImageBuffer pointer to a buffer which contains the captured images.
        \param deviceNumber an integer argument.
        */
        ProcessingThread(VideoImageBuffer *videoImageBuffer, int deviceNumber);
        //! Function to get the current region of interest.
        /*!
          \return QRect - The current ROI
        */
		QRect getCurrentROI();
        //! Set stop flag for thread worker.
        /*!
        */
        void stop();

    private:
        //! Function to set ROI.
        /*!
        */
		void setROI();
        //! Function to reset ROI.
        /*!
        */
        void resetROI();
        //! Function to save current image.
        /*!
          \param img a Mat image argument.
          \return Boolean value if process was successful.
        */
        bool saveCurrentImage(Mat);

        //! FaceDetection.
        /*!
        Pointer to class instance for FaceDetection.
        */
        FaceDetection *faceDetection;

        //! VideoImageBuffer.
        /*!
        Pointer to buffer which contains the images.
        */
        VideoImageBuffer *videoImageBuffer;
        //! Mat image.
        /*!
        Current image.
        */
        Mat currentFrame;
        //! Mat image.
        /*!
        Current image in grayscale.
        */
        Mat currentFrameGrayscale;
        //! QPixmap image.
        /*!
        Current image converted to QPixmap format.
        */
        QPixmap frame;
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
        //! Size.
        /*!
        Size of the frame.
        */
        Size frameSize;
        //! Point.
        /*!
        Frame point.
        */
        Point framePoint;
        //! Rect.
        /*!
        Current region of interest.
        */
		Rect currentROI;
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
        Boolean value if frame processing is enabled.
        */
        bool enableFrameProcessing;
        //! Bool.
        /*!
        Boolean value if image shall be saved.
        */
        bool saveImage;
        //! QString.
        /*!
        Directory to record a video.
        */
        QString recDir;
        //! QString.
        /*!
        Filename of the recorded video.
        */
        QString recFn;
        //! Bool.
        /*!
        State if video shall be recorded.
        */
        bool recFlag;

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
        //! Private slot to set region of interest.
        /*!
        \param roi a QRect argument.
        */
		void setROI(QRect roi);
        //! Private slot to set save parameters.
        /*!
        \param dir a QString argument which contains the Directory name.
        \param fn a QString argument which contains the file name.
        */
        void setSaveParams(QString dir, QString fn);
        //! Private slot to set save image sFlag.
        /*!
        \param sFlag a bool argument.
        */
        void setSaveImgFlag(bool sFlag);
        //! Private slot to set frame processing flag.
        /*!
        \param flag a bool argument.
        */
        void setFrameProcessing(bool flag);
        //! Private slot to set recording rFlag.
        /*!
        \param rFlag a bool argument.
        */
        void setRecFlag(bool rFlag);

	signals:
        //! Signal: New frame.
        /*!
        This signale emits the next frame to the main window to display it.
        \param frame a QPixmap image.
        */
		void newFrame(const QPixmap &frame);
        //! Signal: Record frame.
        /*!
        This signale emits the next frame for recording.
        \param img a Mat image.
        */
        void recFrame(const Mat &img);
};

#endif // PROCESSINGTHREAD_H
