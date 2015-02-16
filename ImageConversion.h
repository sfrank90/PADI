#ifndef IMAGECONVERSION_H
#define IMAGECONVERSION_H

#include <iostream>

#include <QImage>
#include <QPixmap>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

/*! \file ImageConversion.h
\brief Image conversion functions.
Four function to convert images between the following three types: OpenCV Mat, QImage, QPixmap.
*/


//basic conversion
//! Image conversion function which converts an OpenCV Mat image to an Qt QImage.
/*!
\param inMat a Mat image to convert.
\return The converted image as QImage (Qt format).
*/
QImage  cvMatToQImage( const cv::Mat &inMat);
//! Image conversion function which converts an OpenCV Mat image to an Qt QImage.
/*!
\param inImage a QImage image to convert.
\param inCloneImageData a boolean value if image should be cloned for conversion.
\return The converted image as Mat (OpenCV format).
*/
cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData);

//! Inline function for direct conversion from Mat to QPixmap format.
/*!
\param inMat a Mat image to convert.
\return The converted image as QPixmap (Qt format).
*/
inline QPixmap cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

// If inPixmap exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inPixmap's data
// with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
//! Inline function for direct conversion from QPixmap to Mat format.
/*!
\param inPixmap a QPixmap image to convert.
\param inCloneImageData a boolean value if image should be cloned for conversion.
\return The converted image as Mat (OpenCV format).
*/
inline cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true )
{
    return QImageToCvMat( inPixmap.toImage(), inCloneImageData );
}

#endif // IMAGECONVERSION_H
