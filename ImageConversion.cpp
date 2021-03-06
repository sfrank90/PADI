#include "ImageConversion.h"
// Qt
#include <QDebug>

QImage  cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
 
        return image;
        }
 
        // 8-bit, 3 channel
        case CV_8UC3:
        {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
 
        return image.rgbSwapped();
        }
 
        // 8-bit, 1 channel
        case CV_8UC1:
        {
        static QVector<QRgb>  sColorTable;
 
        // only create our color table once
        if ( sColorTable.isEmpty() )
        {
            for ( int i = 0; i < 256; ++i )
                sColorTable.push_back( qRgb( i, i, i ) );
        }
 
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
 
        image.setColorTable( sColorTable );
 
        return image;
        }
 
        default:
            std::cout << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type() << std::endl;
        break;
    }
 
    return QImage();
}

// If inImage exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inImage's
// data with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true )
{
    switch ( inImage.format() )
    {
        // 8-bit, 4 channel
        case QImage::Format_RGB32:
        {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );
 
        return (inCloneImageData ? mat.clone() : mat);
        }
 
        // 8-bit, 3 channel
        case QImage::Format_RGB888:
        {
        if ( !inCloneImageData )
            std::cout << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage" << std::endl;
 
        QImage   swapped = inImage.rgbSwapped();
 
        return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
        }
 
        // 8-bit, 1 channel
        case QImage::Format_Indexed8:
        {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );
 
        return (inCloneImageData ? mat.clone() : mat);
        }
 
        default:
        std::cout << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format() << std::endl;
        break;
    }
 
    return cv::Mat();
}
