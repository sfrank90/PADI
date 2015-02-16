#include "CameraConnectDialog.h"
#include "ui_CameraConnectDialog.h"
// Qt
#include <QtCore/QThread>
#include <QMessageBox>

CameraConnectDialog::CameraConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraConnectDialog)
{  
    // Setup dialog
    ui->setupUi(this);
}

CameraConnectDialog::~CameraConnectDialog()
{
    delete ui;
}

int CameraConnectDialog::getMode()
{
	if(ui->liveViewRadio->isChecked())
		return 1;
	if(ui->recordedRadio->isChecked())
		return 2;
	if(ui->imageRadio->isChecked())
		return 3;
	else
	{
		return 0;
	}
}
