#include "MainWindow.h"
#include "ui_MainWindow.h"
// Qt
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //setup UI
    ui->setupUi(this);

	// Create image processing settings dialog
	imageProcessingSettingsDialog = new ImageProcessingSettingsDialog(this);

    //connect other signals/slots
	connect(ui->actionMode, SIGNAL(triggered()),this , SLOT(selectMode()));
	connect(ui->actionAddOveralys, SIGNAL(triggered()),this , SLOT(setImageProcessingSettings()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionDetection, SIGNAL(toggled(bool)), this, SLOT(setDetection(bool)));

	//connect recording buttons
	connect(ui->recDirButton, SIGNAL(released()), SLOT(setRecDir()));
	connect(ui->recVideoButton, SIGNAL(released()), SLOT(recordVideo()));
	connect(ui->snapshotButton, SIGNAL(released()), SLOT(takeSnapshot()));

	//connect button
	connect(ui->modebutton, SIGNAL(released()), SLOT(selectMode()));
	connect(ui->overlaybutton, SIGNAL(released()), SLOT(setImageProcessingSettings()));

	//disable overlay functions
	ui->overlaybutton->setDisabled(true);
	ui->actionAddOveralys->setDisabled(true);

	//disable snapshot and rec button
	ui->snapshotButton->setDisabled(true);
	ui->recVideoButton->setDisabled(true);

	//init user information
	ui->imagelabel->setText("Please select initial mode for the software...");

	//initialization of variables
	recording = false;
	liveViewActive = false;
    playbackActive = false;
    detection = ui->actionDetection->isChecked();
	saveDirectory = "";
	this->deviceNumber = 0;

	// Initialize ImageProcessingFlags structure
	imageProcessingFlags.showDetectionOn=false;
	imageProcessingFlags.showOverlaysOn=true;

	// label adjustement for images
	ui->imagelabel->setAlignment(Qt::AlignCenter);

	////////////////////////////////////////////
	// Check for necessary cascade files

	QFile cascade_face( "./cascade/haarcascade_frontalface_alt.xml" );
	QFile cascade_eyes( "./cascade/haarcascade_eye_tree_eyeglasses.xml" );
	QFile cascade_nose( "./cascade/haarcascade_mcs_nose.xml" );
	QFile cascade_mouth( "./cascade/haarcascade_mcs_mouth.xml" );
  
	if( !cascade_face.exists() || !cascade_eyes.exists() || !cascade_nose.exists() || !cascade_mouth.exists() )
	{
		// disable all detections due to missing xml files
		imageDetection = false;
		QMessageBox::warning(this,"WARNING:","Detection was disabled because Haarcascade XML files are missing!");
		close();
	} else
		imageDetection = true;
}

MainWindow::~MainWindow()
{
    // destruct all
	if(liveViewActive)
		disconnectCamera();

    if(playbackActive)
        stopPlayback();

    if(recording)
        recordVideo();

	if(imageProcessingSettingsDialog != NULL)
		delete imageProcessingSettingsDialog;

    if(imageHandler != NULL)
        delete imageHandler;

    delete ui;
}

void MainWindow::selectMode()
{	
    // Show dialog for mode
    CameraConnectDialog *cameraConnectDialog = new CameraConnectDialog(this);

    if(cameraConnectDialog->exec()==QDialog::Accepted)
    {
        // File Dialog
        QFileDialog* fd = new QFileDialog;
        fd->setDirectory(".");

		// store mode (integer) to private variable
		mode = cameraConnectDialog->getMode();

        if(mode != 1)
        {
            // first of all stop liveview thread if camera is active
            if(liveViewActive)
            {
                std::cout << "Disconnect camera!" << std::endl;
                disconnectCamera();
            }
        }
        if(mode != 1 || mode != 2)
            ui->recVideoButton->setDisabled(true);
        if(mode != 2)
        {
            if(playbackActive)
                stopPlayback();
        }
        if(mode != 3)
        {
            ui->actionDetection->setDisabled(false);
        }

		switch(mode)
		{
			case 0: 
				QMessageBox::warning(this,"ERROR:","No valid mode selected!");
				break;
			case 1: 
				ui->imagelabel->setText("Connecting...");
				connectToCamera();
				break;
			case 2: 
                fd->setNameFilter("Videos (*.avi *.mp4)");
                if(fd->exec() == QFileDialog::Accepted)
                    file = fd->selectedFiles()[0];

                //standard file dialog
                //file = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              //QString(), tr("Video files (*.mp4);;All Files (*)"));
				if(file.isEmpty())
				{
					mode = 0;
					ui->statusBar->showMessage("Video selection canceled.", 4000);
					delete cameraConnectDialog;
					return;
				}
                if(playbackActive)
                    stopPlayback();
                startPlayback(file);
				break;
			case 3: 
                fd->setNameFilter("Images (*.jpg)");
                if(fd->exec() == QFileDialog::Accepted)
                    file = fd->selectedFiles()[0];

                //standard file dialoag
                //file = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              //QString(), tr("Image files (*.jpg *.jpeg *.png);;All Files (*)"));
				if(file.isEmpty())
				{
					mode = 0;
					ui->statusBar->showMessage("Image selection canceled.", 4000);
					delete cameraConnectDialog;
					return;
				}
				// call show image
				showImage(file);

				break;
		}
        delete fd;
    } else
	{
		mode = 0;
		ui->statusBar->showMessage("Mode selection canceled.", 4000);
		delete cameraConnectDialog;
		return;
	}

    // Delete dialog
    delete cameraConnectDialog;
}

//------------------------------------------------
//------------- liveview functions ---------------
void MainWindow::connectToCamera()
{
	// start video thread for live view
	if(mode == 1 && !liveViewActive)
	{
        videoImageBuffer = new VideoImageBuffer();
        Buffer<Mat> *imageBuffer = new Buffer<Mat>(1000);
        // Add created ImageBuffer to SharedImageBuffer object
        videoImageBuffer->add(deviceNumber, imageBuffer);
        // Create VideoThread
        videoThread = new VideoThread(videoImageBuffer, deviceNumber, true);

		if(videoThread->connectToCamera())
		{
            rec_height = videoThread->getInputSourceHeight();
            rec_width = videoThread->getInputSourceWidth();

			ui->statusBar->showMessage("Connecting...", 5000);

			// Create processing thread
            //videoImageBuffer = new VideoImageBuffer();
			processingThread = new ProcessingThread(videoImageBuffer, deviceNumber);

			// Setup signal/slot connections
			connect(processingThread, SIGNAL(newFrame(QPixmap)), this, SLOT(updateFrame(QPixmap)));	
			connect(imageProcessingSettingsDialog, SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)), processingThread, SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
			connect(this, SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)), processingThread, SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
            connect(this, SIGNAL(changeDetectionState(bool)), processingThread, SLOT(setFrameProcessing(bool)));
			connect(this, SIGNAL(setROI(QRect)), processingThread, SLOT(setROI(QRect)));
            connect(this, SIGNAL(setSaveParams(QString, QString)), processingThread, SLOT(setSaveParams(QString, QString)));
            connect(this, SIGNAL(setLiveViewSaveImgFlag(bool)), processingThread, SLOT(setSaveImgFlag(bool)));
            connect(this, SIGNAL(setRecordFlag(bool)), processingThread, SLOT(setRecFlag(bool)));
			
			// Set initial data in processing thread
            emit changeDetectionState(detection);
			emit setROI(QRect(0, 0, videoThread->getInputSourceWidth(), videoThread->getInputSourceHeight()));
			emit newImageProcessingFlags(imageProcessingFlags);
            emit setRecordFlag(false);

			imageProcessingSettingsDialog->updateStoredSettingsFromDialog();

			// Start capturing frames from camera
			videoThread->start();
			// Start processing captured frames
			processingThread->start();

            // Set internal flag
			liveViewActive=true;

            //enable snapshot button
            ui->snapshotButton->setDisabled(false);

            //enable overlays
            ui->overlaybutton->setDisabled(false);
            ui->actionAddOveralys->setDisabled(false);

            //enable record video button
            ui->recVideoButton->setDisabled(false);

			ui->statusBar->showMessage("Connected to Webcam. Mode: LiveView", 4000);
		}
		else
		{
            ui->imagelabel->setText("Camera seems to be not available! Check if plugged in...");
			ui->statusBar->showMessage("Connecting to camera failed!", 5000);
		}
	}
}

void MainWindow::disconnectCamera()
{
	if(liveViewActive)
	{
		// Stop processing thread
        if(processingThread->isRunning())
            stopProcessingThread();
        // Stop capture thread
		if(videoThread->isRunning())
            stopVideoThread();

        // Remove from shared buffer
        videoImageBuffer->removeByDeviceNumber(deviceNumber);
        // Disconnect camera
        if(videoThread->disconnectCamera())
			ui->statusBar->showMessage("LiveView Camera successfully disconnected.", 4000);
        else
            ui->statusBar->showMessage("LiveView Camera already disconnected.", 4000);
	}

	// delete created pointer
	if(videoImageBuffer != NULL)
        delete videoImageBuffer;
	if(processingThread != NULL)
        delete processingThread;
	if(videoThread != NULL)
        delete videoThread;

	// set liveView not active
	liveViewActive = false;
}

void MainWindow::updateFrame(const QPixmap &frame)
{
	//get display label size
	int width = ui->imagelabel->width();
	int height = ui->imagelabel->height();

    // Display frame
    ui->imagelabel->setPixmap(frame.scaled(width,height,Qt::KeepAspectRatio));
}

void MainWindow::stopVideoThread()
{
	ui->statusBar->showMessage("About to stop capture thread...", 3000);
    videoThread->stop();
    videoImageBuffer->wakeAll();
    // Take one frame off a FULL queue to allow the capture thread to finish
    if(videoImageBuffer->getByDeviceNumber(deviceNumber)->isFull())
        videoImageBuffer->getByDeviceNumber(deviceNumber)->get();
    videoThread->wait();
	ui->statusBar->showMessage("Video thread successfully stopped.", 3000);
}

void MainWindow::stopProcessingThread()
{
	ui->statusBar->showMessage("About to stop processing thread...", 3000);
    processingThread->stop();
    videoImageBuffer->wakeAll();
    processingThread->wait();
	ui->statusBar->showMessage("Processing thread successfully stopped.", 3000);
}
//------------------------------------------------

//------------------------------------------------
//----------- Show Playback Functions ------------
void MainWindow::startPlayback(QString filename)
{
    if(mode == 2)
    {
        ui->statusBar->showMessage("Loading file...", 5000);

        // Create playback thread
        playbackThread = new PlaybackThread(filename);

        // Setup signal/slot connections
        connect(playbackThread, SIGNAL(nextFrame(QPixmap)), this, SLOT(updateFrame(QPixmap)));
        connect(imageProcessingSettingsDialog, SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)), playbackThread, SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
        connect(this, SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)), playbackThread, SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        connect(this, SIGNAL(changeDetectionState(bool)), playbackThread, SLOT(updateDetState(bool)));

        emit changeDetectionState(detection);
        emit newImageProcessingFlags(imageProcessingFlags);

        //load videofile
        if(!playbackThread->loadPlayback())
        {
            ui->statusBar->showMessage("Error loading Videofile!", 4000);
            return;
        }

        // Start playback
        playbackThread->start();

        // Set internal flag
        playbackActive=true;

        //enable snapshot button
        ui->snapshotButton->setDisabled(false);

        //enable overlays
        ui->overlaybutton->setDisabled(false);
        ui->actionAddOveralys->setDisabled(false);

        //enable record video button
        //ui->recVideoButton->setDisabled(false);

        ui->statusBar->showMessage("Mode: Playback", 4000);
    }
}

void MainWindow::stopPlayback()
{
    if(playbackActive)
    {
        if(playbackThread->isRunning())
            stopPlaybackThread();
    }

    // delete created pointer
    if(playbackThread != NULL)
        delete playbackThread;

    std::cout << "Playback thread stopped!" << std::endl;
    playbackActive = false;
}

void MainWindow::stopPlaybackThread()
{
    ui->statusBar->showMessage("About to stop playback thread...", 3000);
    playbackThread->stop();
    playbackThread->wait();
    ui->statusBar->showMessage("Playback thread successfully stopped.", 3000);
}


//------------------------------------------------

//------------------------------------------------
//----------- Show Image Functions ---------------
void MainWindow::showImage(QString fn)
{
	imageHandler = new ImageHandler();

	// status information
	ui->imagelabel->setText("Loading image from file...");
	ui->statusBar->showMessage("Loading image from file...", 4000);

	imageProcessingSettings = imageProcessingSettingsDialog->getImgProcSettingsForImg();
	imageProcessingFlags = imageProcessingSettingsDialog->ImgProcFlagsForImg();

	QPixmap temp_pix = imageHandler->loadImageFromFile(fn, imageProcessingSettings, imageProcessingFlags, imageDetection);

	ui->statusBar->showMessage("Image loaded", 4000);

	//get display label size
	int width = ui->imagelabel->width();
	int height = ui->imagelabel->height();

	ui->imagelabel->setPixmap(temp_pix.scaled(width,height,Qt::KeepAspectRatio));

	//enable snapshot button
	ui->snapshotButton->setDisabled(false);

    //disable action detection
    ui->actionDetection->setDisabled(true);

	//enable overlays
	ui->overlaybutton->setDisabled(false);
	ui->actionAddOveralys->setDisabled(false);
}

void MainWindow::applyChangesOnSingleImage()
{
	ui->statusBar->showMessage("Apply changes to image", 4000);

	imageProcessingSettings = imageProcessingSettingsDialog->getImgProcSettingsForImg();
	imageProcessingFlags = imageProcessingSettingsDialog->ImgProcFlagsForImg();
	if(imageDetection)
	{
		QPixmap img_new = imageHandler->applyChangesToImageProc(imageProcessingSettings, imageProcessingFlags);

		//get display label size
		int width = ui->imagelabel->width();
		int height = ui->imagelabel->height();

		ui->imagelabel->setPixmap(img_new.scaled(width,height,Qt::KeepAspectRatio));
	}
}
//------------------------------------------------

// Option functions
void MainWindow::showAboutDialog()
{
    QMessageBox::about(this, "About", QString("MisterSpex Demo 2014 \nProgrammed for PADI, WS 13/14 @ TU Braunschweig"));
}

void MainWindow::setDetection(bool input)
{
    if(input)
        this->detection = true;
    else
        this->detection = false;

    emit changeDetectionState(this->detection);

}

//------------------------------------------------
//------ Recording options and functions --------- 
void MainWindow::takeSnapshot()
{
    bool succ = false;
	QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);
    bool ok = false;
    QString filename =  inputDialog->getText(NULL ,"Snapshot Filename",
                                          "Filename: (without *.jpg ...)", QLineEdit::Normal,
                                          "", &ok);
    delete inputDialog;
    // return if cancel inputdialog
    if(!ok)
    {
        ui->statusBar->showMessage("Save Snapshot: Canceled!", 5000);
        return;
    }
	if(saveDirectory.isEmpty())
	{
        saveDirectory = "./output";
        QMessageBox::warning(this,"WARNING:",QString("No user directory selected. Default dir (%1/) will be used!").arg(saveDirectory));
		if (!QDir(saveDirectory).exists()) {
			QDir().mkdir(saveDirectory);
		}
	}
    //static image
    if(mode == 3)
	{
        if(filename.isEmpty())
            filename = "Test";
        succ = imageHandler->saveImageToFile(filename, saveDirectory);
	}
    //current image from LiveView
    if(mode == 1)
    {
        if(filename.isEmpty())
            filename = "Test";
        emit setSaveParams(saveDirectory, filename);
        emit setLiveViewSaveImgFlag(true);
        succ = true;
    }
	if(succ)
        ui->statusBar->showMessage(QString("Snapshot saved to dir (%1/%2.jpg)").arg(saveDirectory,filename), 5000);
	else
		ui->statusBar->showMessage("Error while saving snapshot", 5000);
}
		
void MainWindow::recordVideo()//start at actual frame till hit button again
{
	if(!recording)
	{
        QInputDialog* inputDialog = new QInputDialog();
        inputDialog->setOptions(QInputDialog::NoButtons);
        bool ok = false;
        QString filename =  inputDialog->getText(NULL ,"Video Filename",
                                              "Filename: (without *.avi ...)", QLineEdit::Normal,
                                              "", &ok);
        delete inputDialog;
        // return if cancel inputdialog
        if(!ok)
        {
            ui->statusBar->showMessage("Record Video: Canceled!", 5000);
            return;
        }

        if(filename.isEmpty())
            filename = "TestVideo";

		if(saveDirectory.isEmpty())
		{
            saveDirectory = "./output";
            QMessageBox::warning(this,"WARNING:",QString("No user directory selected. Default dir (%1/) will be used!").arg(saveDirectory));
			if (!QDir(saveDirectory).exists()) {
				QDir().mkdir(saveDirectory);
			}
		}
        QString dir = saveDirectory;

        // build path and file name to save
        if(filename.contains("."))
            filename.replace(".","-");
        dir.append("/");
        dir.append(filename);
        dir.append(".avi");

		recording = true;
		// change button text to "stop recording"
		ui->recVideoButton->setText("Stop Rec.");
		//disable snapshot button
		ui->snapshotButton->setDisabled(true);

        //create record thread
        recordThread = new RecordVideoThread(dir, rec_height, rec_width);
        if(!recordThread->createVideoWriter())
        {
            recording = false;

            ui->recVideoButton->setText("Rec. Video");
            //disable snapshot button
            ui->snapshotButton->setDisabled(false);

            delete recordThread;
            ui->statusBar->showMessage("Recording video failed...");
            return;
        }
        qRegisterMetaType< Mat >("Mat");
        connect(processingThread, SIGNAL(recFrame(Mat)), recordThread, SLOT(addRecFrame(Mat)));

        // send stop rec signal
        emit setRecordFlag(true);

        ui->statusBar->showMessage(QString("Recording video to dir (%1)").arg(saveDirectory));
	} else 
	{
        std::cout << "Stopping record thread" << std::endl;

		recording = false;

        // send stop rec signal
        emit setRecordFlag(false);

		// change button text to "Rec. Video"
		ui->recVideoButton->setText("Rec. Video");
		// enable snapshot button
		ui->snapshotButton->setDisabled(false);

        //finalize and stop thread
        recordThread->stop();

        //delete thread
        delete recordThread;

		ui->statusBar->showMessage("Recording stopped! File saved.", 5000);
	}
}

void MainWindow::setRecDir()
{
    QFileDialog* dir_select = new QFileDialog;
    dir_select->setDirectory(".");
    dir_select->setFileMode(QFileDialog::DirectoryOnly);

    if(dir_select->exec()  == QFileDialog::Accepted)
    {
        saveDirectory = dir_select->selectedFiles()[0];
        ui->statusBar->showMessage(QString("Directory: %1").arg(dir_select->selectedFiles()[0]));
    }
    delete dir_select;

    //standard choose directory
    //saveDirectory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             //"/home",
                                             //QFileDialog::ShowDirsOnly
                                             //| QFileDialog::DontResolveSymlinks);
}
//------------------------------------------------


// Image Processing Settings
void MainWindow::setImageProcessingSettings()
{
    // Prompt user:
    // If user presses OK button on dialog, update image processing settings
    if(imageProcessingSettingsDialog->exec()==QDialog::Accepted)
	{
        imageProcessingSettingsDialog->updateStoredSettingsFromDialog();
        if(mode == 1 || mode == 2)
        {
            imageProcessingFlags = imageProcessingSettingsDialog->ImgProcFlagsForImg();
            emit newImageProcessingFlags(imageProcessingFlags);
        }
        if(mode == 3)
			applyChangesOnSingleImage();
	}
    // Else, restore dialog state
    else
        imageProcessingSettingsDialog->updateDialogSettingsFromStored();
}
