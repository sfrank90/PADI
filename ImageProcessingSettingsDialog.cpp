#include "ImageProcessingSettingsDialog.h"
#include "ui_ImageProcessingSettingsDialog.h"
// Qt
#include <QMessageBox>
#include <QFile>

ImageProcessingSettingsDialog::ImageProcessingSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageProcessingSettingsDialog)
{
    // Setup dialog
    ui->setupUi(this);
    // Connect GUI signals and slots
    connect(ui->resetOverlays,SIGNAL(released()),SLOT(resetOverlays()));
    connect(ui->applyButton,SIGNAL(released()),SLOT(updateStoredSettingsFromDialog()));

	////////////////////////////////////////////
	// check for overlay files else qwarning
	QFile overlay_eyes( "./overlays/glasses.png" );
	QFile overlay_nose( "./overlays/rednose.png" );
	QFile overlay_mouth( "./overlays/redlips.png" );
  
	if( !overlay_eyes.exists())
	{
		// disable all detections due to missing xml files
		ui->glasses->setDisabled(true);
		QMessageBox::warning(this,"WARNING:","Coud not find glasses overlay!");
	}
	if( !overlay_nose.exists())
	{
		// disable all detections due to missing xml files
		ui->nose->setDisabled(true);
		QMessageBox::warning(this,"WARNING:","Coud not find nose overlay!");
	}
	if( !overlay_mouth.exists())
	{
		// disable all detections due to missing xml files
		ui->redlips->setDisabled(true);
		QMessageBox::warning(this,"WARNING:","Coud not find mouth overlay!");
	}
	if( !overlay_eyes.exists() && !overlay_nose.exists() && !overlay_mouth.exists())
	{
		ui->showOverlays->setChecked(false);
		ui->showOverlays->setDisabled(true);
	}

    // Update image processing settings in imageProcessingSettings structure and processingThread
    updateStoredSettingsFromDialog();
}

ImageProcessingSettingsDialog::~ImageProcessingSettingsDialog()
{
    delete ui;
}

void ImageProcessingSettingsDialog::updateStoredSettingsFromDialog()
{
	if(ui->glasses->isChecked())
		imageProcessingSettings.overlayParam1 = true;
	else
		imageProcessingSettings.overlayParam1 = false;
	if(ui->nose->isChecked())
		imageProcessingSettings.overlayParam2 = true;
	else
		imageProcessingSettings.overlayParam2 = false;
	if(ui->redlips->isChecked())
		imageProcessingSettings.overlayParam3 = true;
	else
		imageProcessingSettings.overlayParam3 = false;
    emit newImageProcessingSettings(imageProcessingSettings);
}

void ImageProcessingSettingsDialog::updateDialogSettingsFromStored()
{
    if(imageProcessingSettings.overlayParam1)
		ui->glasses->setChecked(true);
	else
		ui->glasses->setChecked(false);
	if(imageProcessingSettings.overlayParam1)
		ui->nose->setChecked(true);
	else
		ui->nose->setChecked(false);
	if(imageProcessingSettings.overlayParam1)
		ui->redlips->setChecked(true);
	else
		ui->redlips->setChecked(false);
}

void ImageProcessingSettingsDialog::resetOverlays()
{
    ui->glasses->setChecked(OVERLAY_PARAM_1);
    ui->nose->setChecked(OVERLAY_PARAM_2);
    ui->redlips->setChecked(OVERLAY_PARAM_3);

}

// just a simple image function. NOT for LiveView or Playback mode
ImageProcessingSettings ImageProcessingSettingsDialog::getImgProcSettingsForImg()
{
	return imageProcessingSettings;
}

ImageProcessingFlags ImageProcessingSettingsDialog::ImgProcFlagsForImg()
{
	ImageProcessingFlags flags;
	if(ui->showFacedetection->isChecked())
		flags.showDetectionOn = true;
	else 
		flags.showDetectionOn = false;
	if(ui->showOverlays->isChecked())
		flags.showOverlaysOn = true;
	else 
		flags.showOverlaysOn = false;

	return flags;
}

