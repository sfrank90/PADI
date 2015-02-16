#ifndef FACEDETECTION_H
#define FACEDETECTION_H

// OpenCv
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Qt for QString
#include <qstring.h>

// std
#include <iostream>
#include <stdio.h>

// local
#include "Structures.h"

//! FaceDetection class
/*!
    Class has functions for object detection and overlay composing.
*/
class FaceDetection
{
public:
    //! Class constructor which creates a new handler.
    /*!
    */
    FaceDetection();

    //! Function to detect objects in a given image. In this case face objects.
    /*!
    \param inMat an Mat image (OpenCV type) file.
    \param settings an ImageProcessingSettings struct which contains the settings for the area which should be detected
    \param drawFlags an ImageProcessingFlags struct which contains bool values about overlay showing and detection drawing
    \return Image in Mat type with in image drawn detection and/or overlays
    */
    cv::Mat detectObjects(cv::Mat &, ImageProcessingSettings, ImageProcessingFlags);

    //! Function to draw a specific overlay on the given image.
    /*!
    \param fn an QString name of the overlay file to load.
    \param src an Mat image (OpenCV type) file.
    \param output an Mat image (OpenCV type) file which also contains the overlay.
    \param location an Point2i (OpenCV type for single point with to integers coordinates) which is the anker point of the overlay.
    \param scale an integer value for scaling the overlay according to the image size.
    */
    void cvCreateOverlay(QString, const cv::Mat&, cv::Mat &, cv::Point2i, int);

    //! Special draw function for the glasses overlay because the special anker point behaviour.
    /*!
    \param fn an QString name of the overlay file to load.
    \param src an Mat image (OpenCV type) file.
    \param output an Mat image (OpenCV type) file which also contains the overlay.
    \param location an Point2i (OpenCV type for single point with to integers coordinates) which is the anker point of the overlay.
    \param scale an integer value for scaling the overlay according to the image size.
    */
    void cvCreateOverlayGlasses(QString, const cv::Mat&, cv::Mat &, cv::Point2i, int);

private:
    double tem_cropfactor;
    cv::Mat temp_glass_overlay;
};


#endif // FACEDETECTION_H
