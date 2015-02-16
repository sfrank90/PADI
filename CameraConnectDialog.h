#ifndef CAMERACONNECTDIALOG_H
#define CAMERACONNECTDIALOG_H

// Qt
#include <QDialog>
// Local
#include "Config.h"

namespace Ui {
class CameraConnectDialog;
}

//! Camera connect dialog class
/*!
    Dialog class to select the mode in which the software should run.
*/
class CameraConnectDialog : public QDialog
{
    Q_OBJECT
    
    public:
        //! Constructor of the dialog  to set up the UI from the Qt file.
        /*!
        \param parent an QWidget argument. If no parameter is give parent = 0.
        */
        explicit CameraConnectDialog(QWidget *parent=0);
        //! Destructor of the dialog  to delete the created UI.
        /*!
        */
        ~CameraConnectDialog();
        //! Function which return the user selected mode.
        /*!
        \return An integer value which identifies the selected mode.
        */
        int getMode();

    private:
        //! CameraConnectDialog UI pointer.
        /*!
        Pointer the the user interface file of the dialog.
        */
        Ui::CameraConnectDialog *ui;
};

#endif // CAMERACONNECTDIALOG_H
