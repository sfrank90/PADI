#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

// Local
#include "ImageConversion.h"
#include "FaceDetection.h"
#include "Structures.h"

#include <iostream>

// Qt
#include <QtGui/QImage>
#include <QtGui/qpixmap.h>

// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

//! Image handler class
/*!
    Class to handle static images for the software.
*/
class ImageHandler
{
    public:
        //! Class constructor which creates a new handler.
        /*!
        */
        ImageHandler();
        //! Class destructor.
        /*!
        */
        ~ImageHandler();
        //! Function to load a single image from a file.
        /*!
        \param fn a QString argument which contains the name of the file to load.
        \param imgProcSettings an ImageProcessingSettings struct which contains the settings for the area which should be detected
        \param drawFlags an ImageProcessingFlags struct which contains bool values about overlay showing and detection drawing
        \param imageDetection a boolean value to say if image detection should be done.
        \return The function returns the selected image converted to QPixmap format with applied detection
        */
		QPixmap loadImageFromFile(QString, struct ImageProcessingSettings, struct ImageProcessingFlags, bool);
        //! Function to apply changes on the selected image.
        /*!
        \param imgProcSettings an ImageProcessingSettings struct which contains the settings for the area which should be detected
        \param drawFlags an ImageProcessingFlags struct which contains bool values about overlay showing and detection drawing
        \return The function returns the selected image converted to QPixmap format with applied detection
        */
		QPixmap applyChangesToImageProc(struct ImageProcessingSettings, struct ImageProcessingFlags);
        //! Function to save the display image to file.
        /*!
        \param fn a QString argument which contains the name to save the image.
        \param dir a QString argument which contains the directory name where the file should be saved.
        \return Boolean value which says if the process was successful or not.
        */
		bool saveImageToFile(QString, QString);

    private:
        //! FaceDetection.
        /*!
        Pointer to instance of FaceDetection class.
        */
        FaceDetection *faceDetection;
        //! Mat (OpenCV image format).
        /*!
        Image which will be display in the main window after conversion.
        */
        Mat image;
        //! Mat (OpenCV image format).
        /*!
        Original image.
        */
		Mat orig_image;
};




#endif // IMAGEHANDLER_H
