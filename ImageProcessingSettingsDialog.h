#ifndef IMAGEPROCESSINGSETTINGSDIALOG_H
#define IMAGEPROCESSINGSETTINGSDIALOG_H

// Qt
#include <QDialog>
#include <QAbstractButton>
// Local
#include "Structures.h"
#include "Config.h"

namespace Ui {
class ImageProcessingSettingsDialog;
}

//! Image processing dialog class
/*!
    Dialog to set specifc parameters which will be applied on the displayed image.
*/
class ImageProcessingSettingsDialog : public QDialog
{
    Q_OBJECT

    public:
        //! Constructor of the dialog  to set up the UI from the Qt file.
        /*!
        \param parent an QWidget argument. If no parameter is give parent = 0.
        */
        explicit ImageProcessingSettingsDialog(QWidget *parent = 0);
        //! Destructor of the dialog  to delete the created UI.
        /*!
        */
        ~ImageProcessingSettingsDialog();
        //! Function which updates the dialog settings from the stored ones.
        /*!
        */
        void updateDialogSettingsFromStored();

		//simple image functions
        //! Function to get actual ImageProcessingSettings struct.
        /*!
        \return ImageProcessingSettings struct which contains the acutal settings.
        */
		ImageProcessingSettings getImgProcSettingsForImg();
        //! Function to get actual ImageProcessingFlags struct.
        /*!
        \return ImageProcessingFlags struct which contains the acutal flags.
        */
		ImageProcessingFlags ImgProcFlagsForImg();

    private:
        //! ImageProcessingSettingsDialog UI pointer.
        /*!
        Pointer the the user interface file of the dialog.
        */
        Ui::ImageProcessingSettingsDialog *ui;
        //! ImageProcessingSettings struct.
        /*!
        Structure of several settings.
        */
        ImageProcessingSettings imageProcessingSettings;

    public slots:
        //! Public slot to updated the stored settings from the dialog ones.
        /*!
        Public slot to connect with a specific action in program that should call this function
        */
        void updateStoredSettingsFromDialog();

    private slots:
        //! Private slot to reset the display settings.
        /*!
        Private slot tocall function to reset settings. Value from Config.h are used.
        */
        void resetOverlays();

    signals:
        //! Signal: New ImageProcessingSettings are set.
        /*!
        \param p_settings ImageProcessingSettings struct as argument.
        */
        void newImageProcessingSettings(struct ImageProcessingSettings p_settings);
};

#endif // IMAGEPROCESSINGSETTINGSDIALOG_H
