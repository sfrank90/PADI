#include "ImageHandler.h"
// Qt
#include <QDebug>
#include <iostream>
#include <string>
#include <QImageWriter>

ImageHandler::ImageHandler()
{
    std::cout << "Create ImageHandler with FaceDetection" << std::endl;
    faceDetection = new FaceDetection();
}

QPixmap ImageHandler::loadImageFromFile(QString fn, struct ImageProcessingSettings imgProcSettings, ImageProcessingFlags drawFlags, bool imageDetection)
{
	image = imread(fn.toStdString(), CV_LOAD_IMAGE_COLOR);
	if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
    }
	// deep copy to save original img
	orig_image = image.clone();
	if(imageDetection)
	{
        Mat img_cpy = faceDetection->detectObjects(image, imgProcSettings, drawFlags);

		QPixmap qt_img = cvMatToQPixmap(img_cpy);
        //std::cout << "Image converted!" << std::endl;

		return qt_img;
	}
	else
		return cvMatToQPixmap(image);
}

QPixmap ImageHandler::applyChangesToImageProc(struct ImageProcessingSettings imgProcSettings, ImageProcessingFlags drawFlags)
{
	// reset image to orig_image
	image = orig_image.clone();

    Mat img_cpy = faceDetection->detectObjects(image, imgProcSettings, drawFlags);

	QPixmap qt_img = cvMatToQPixmap(img_cpy);
    //std::cout << "Image converted!" << std::endl;

	return qt_img;
}

bool ImageHandler::saveImageToFile(QString fn, QString dir)
{
    // build path and file name to save
	if(fn.contains("."))
		fn.replace(".","-");
    dir.append("/");
	dir.append(fn);
	dir.append(".jpg");

    //normal save part
    if(imwrite(dir.toStdString(), image))
    {
        std::cout << "Succes saving image" << std::endl;
		return true;
    }
	else
		return false;
}

ImageHandler::~ImageHandler()
{
    // delete facedetection pointer if playback thread stopped
    std::cout << "Delete FaceDetection reference" << std::endl;
    delete faceDetection;
}
