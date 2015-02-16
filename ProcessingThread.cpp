#include "ProcessingThread.h"

ProcessingThread::ProcessingThread(VideoImageBuffer *videoImageBuffer, int deviceNumber) : QThread(), videoImageBuffer(videoImageBuffer)
{
    // Save Device Number
    this->deviceNumber=deviceNumber;
    // Initialize members
    doStop=false;
    saveImage=false;

    faceDetection = new FaceDetection();
}

void ProcessingThread::run()
{
    while(1)
    {
        ////////////////////////////////
        // Stop thread if doStop=TRUE //
        ////////////////////////////////
        doStopMutex.lock();
        if(doStop)
        {
            doStop=false;
            doStopMutex.unlock();
            break;
        }
        doStopMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        processingMutex.lock();
        // Get frame from queue, store in currentFrame, set ROI
		//currentFrame = videoImageBuffer->getByDeviceNumber(deviceNumber)->get();
        currentFrame=Mat(videoImageBuffer->getByDeviceNumber(deviceNumber)->get().clone(), currentROI);

        ////////////////////////////////////
        // PERFORM IMAGE PROCESSING BELOW //
        ////////////////////////////////////

        // Check settings and flags cout
        //std::cout << "Flags: Detection - " << imgProcFlags.showDetectionOn << " | Overlay - " << imgProcFlags.showOverlaysOn << std::endl;
        //std::cout << "Settings: Param1 - " << imgProcSettings.overlayParam1 << " | Param2 - " << imgProcSettings.overlayParam2 << " | Param3 - " << imgProcSettings.overlayParam3 << std::endl;

        // Grayscale conversion (in-place operation)
        //if((currentFrame.channels() == 3 || currentFrame.channels() == 4))
            //cvtColor(currentFrame, currentFrame, CV_BGR2GRAY);

        //FaceDetection
        if(enableFrameProcessing)
            currentFrame = faceDetection->detectObjects(currentFrame, imgProcSettings, imgProcFlags);

        ////////////////////////////////////
        // PERFORM IMAGE PROCESSING ABOVE //
        ////////////////////////////////////

        //check rec video flag
        if(recFlag)
            emit recFrame(currentFrame);

        //save image call
        if(saveImage)
            if(saveCurrentImage(currentFrame))
                std::cout << "Current Image saved" << std::endl;

        // Convert Mat to QImage
        frame=cvMatToQPixmap(currentFrame);
        processingMutex.unlock();

        // Inform GUI thread of new frame (QImage)
        emit newFrame(frame);
    }
    std::cout << "Stopping processing thread..." << std::endl;
}

void ProcessingThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;

    // on stop processing, delete facedetection pointer
    std::cout << "Delete FaceDetection reference" << std::endl;
    delete faceDetection;
}

void ProcessingThread::updateImageProcessingFlags(struct ImageProcessingFlags imgProcFlags)
{
    QMutexLocker locker(&processingMutex);
	this->imgProcFlags.showDetectionOn=imgProcFlags.showDetectionOn;
    this->imgProcFlags.showOverlaysOn=imgProcFlags.showOverlaysOn;
}

void ProcessingThread::updateImageProcessingSettings(struct ImageProcessingSettings imgProcSettings)
{
    QMutexLocker locker(&processingMutex);
	this->imgProcSettings.overlayParam1=imgProcSettings.overlayParam1;
    this->imgProcSettings.overlayParam2=imgProcSettings.overlayParam2;
    this->imgProcSettings.overlayParam3=imgProcSettings.overlayParam3;
}

bool ProcessingThread::saveCurrentImage(Mat img)
{
    std::cout << "Current Image Saver" << std::endl;

    // build path and file name to save
    QString dir = recDir;
    QString fn = recFn;
    if(fn.contains("."))
        fn.replace(".","-");
    dir.append("/");
    dir.append(fn);
    dir.append(".jpg");

    saveImage = false;

    //normal save part
    if(imwrite(dir.toStdString(), img))
    {
        std::cout << "Succes saving image" << std::endl;
        return true;
    }
    else
        return false;
}

void ProcessingThread::setROI(QRect roi)
{
    QMutexLocker locker(&processingMutex);
    currentROI.x = roi.x();
    currentROI.y = roi.y();
    currentROI.width = roi.width();
    currentROI.height = roi.height();
}

void ProcessingThread::setSaveParams(QString dir, QString fn)
{
    recDir = dir;
    recFn = fn;
}

void ProcessingThread::setSaveImgFlag(bool sFlag){
    saveImage = sFlag;
}

void ProcessingThread::setFrameProcessing(bool flag){
    enableFrameProcessing = flag;
}

void ProcessingThread::setRecFlag(bool rFlag){
    recFlag = rFlag;
}

QRect ProcessingThread::getCurrentROI()
{
    return QRect(currentROI.x, currentROI.y, currentROI.width, currentROI.height);
}
