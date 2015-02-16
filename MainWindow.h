#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>

// Local
#include "CameraConnectDialog.h"
#include "ImageProcessingSettingsDialog.h"
#include "ImageHandler.h"
#include "VideoThread.h"
#include "ProcessingThread.h"
#include "VideoImageBuffer.h"
#include "PlaybackThread.h"
#include "RecordVideoThread.h"


namespace Ui {
    class MainWindow;
}

//! MainWindow class creates the main application window and builds the basis.
/*!
    Main windows of the application which does most of the work, like connection functions and buttons
    as well as the initilization of the different mode.
    Also function for recording and saving an image are provided here.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        //! Constructor of the main window  to set up the UI from the Qt file.
        /*!
        \param parent an QWidget argument. If no parameter is give parent = 0.
        */
        explicit MainWindow(QWidget *parent = 0);
        //! Destructor of the dialog  to delete the created UI.
        /*!
        */
        ~MainWindow();

    private:
        //! MainWindow UI pointer.
        /*!
        Pointer the the user interface file of the dialog.
        */
        Ui::MainWindow *ui;
        //! ImageProcessingSettingsDialog pointer.
        /*!
        Pointer to a imageProcessingSettingsDialog.
        */
		ImageProcessingSettingsDialog *imageProcessingSettingsDialog;
        //! VideoThread pointer.
        /*!
        Pointer to a videoThread.
        */
		VideoThread *videoThread;
        //! VideoImageBuffer pointer.
        /*!
        Pointer to a videoImageBuffer.
        */
		VideoImageBuffer *videoImageBuffer;
        //! ProcessingThread pointer.
        /*!
        Pointer to a processingThread.
        */
		ProcessingThread *processingThread;
        //! PlaybackThread pointer.
        /*!
        Pointer to a playbackThread.
        */
        PlaybackThread *playbackThread;
        //! RecordVideoThread pointer.
        /*!
        Pointer to a recordThread.
        */
        RecordVideoThread *recordThread;
        //! ImageHandler pointer.
        /*!
        Pointer to a imageHandler.
        */
		ImageHandler *imageHandler;
        //! ImageProcessingFlags struct.
        /*!
        Structure of several flags.
        */
        ImageProcessingFlags imageProcessingFlags;
        //! ImageProcessingSettings struct.
        /*!
        Structure of several settings.
        */
		ImageProcessingSettings imageProcessingSettings;
        //! Bool.
        /*!
        Boolean value if image detection shall be done.
        */
		bool imageDetection;
        //! Bool.
        /*!
        Boolean value if detection (in video or liveview shall be done.
        */
        bool detection;
        //! QString.
        /*!
        Directory to record a video.
        */
		QString saveDirectory;
        //! Bool.
        /*!
        Boolean value to determine if recording is on.
        */
		bool recording;
        //! Bool.
        /*!
        Boolean value to determine if liveview mode is on.
        */
		bool liveViewActive;
        //! Bool.
        /*!
        Boolean value to determine if playback mode is on.
        */
        bool playbackActive;
        //! Integer.
        /*!
        Integer value to determine the mode of the program.
        */
		int mode;
        //! Integer.
        /*!
        Integer value for device number.
        */
		int deviceNumber;
        //! QString.
        /*!
        Name of a file.
        */
		QString file;
        //! Integer.
        /*!
        Integer value with recording width.
        */
        int rec_width;
        //! Integer.
        /*!
        Integer value with recording height.
        */
        int rec_height;


        //! Function to show a static image from an image file.
        /*!
        \param fn a QString with the filename to load.
        */
		void showImage(QString);
        //! Function to apply settings and flags on a loaded image.
        /*!
        */
        void applyChangesOnSingleImage();

        //! Function to stop the VideoThread.
        /*!
        */
		void stopVideoThread();
        //! Function to stop the ProcessingThread.
        /*!
        */
        void stopProcessingThread();

        //! Function to start displaying a video from a file.
        /*!
        \param filename a QString with the filename to load.
        */
        void startPlayback(QString);
        //! Function to stop the Playback.
        /*!
        */
        void stopPlayback();
        //! Function to stop the PlaybackThread.
        /*!
        */
        void stopPlaybackThread();

	private slots:
        //! Private slot to update the shown image in MainWindow.
        /*!
        \param frame a QPixmap to load in specific label.
        */
		void updateFrame(const QPixmap &frame);

    public slots:
        //! Public slot to select mode.
        /*!
        */
        void selectMode();

        //! Public slot to connect to camera.
        /*!
        */
		void connectToCamera();
        //! Public slot to disconnect camera.
        /*!
        */
        void disconnectCamera();

        //! Public slot to show about dialog.
        /*!
        */
        void showAboutDialog();
        //! Public slot to set detection flag.
        /*!
        */
        void setDetection(bool);
        //! Public slot to set ImageProcessingSettings.
        /*!
        */
		void setImageProcessingSettings();

        //! Public slot to set recording directory.
        /*!
        */
		void setRecDir();
        //! Public slot to take a snapshot of the actual displayed image.
        /*!
        */
		void takeSnapshot(); //and actual frame
        //! Public slot to record a video in LiveView mode.
        /*!
        */
		void recordVideo(); //start at actual frame till hit button again

	signals:
        //! Signal: Send new ImageProcessingFlags.
        /*!
        This signal emits the actual ImageProcessingFlags to the connected slot.
        \param imageProcessingFlags a ImageProcessingFlags structure.
        */
        void newImageProcessingFlags(struct ImageProcessingFlags imageProcessingFlags);
        //! Signal: Change detection state flag.
        /*!
        This signal emits the actual detection flag to the connected slot.
        \param detection a bool argument.
        */
        void changeDetectionState(bool detection);
        //! Signal: Set Region of interest.
        /*!
        This signal emits the desired ROI to the connected slot.
        \param roi a QRect argument.
        */
		void setROI(QRect roi);
        //! Signal: Set save parameter.
        /*!
        This signal emits the save parameters to the connected slot.
        \param dir a QString argument with Directory name.
        \param fn a QString argument with filename.
        */
        void setSaveParams(QString dir, QString fn);
        //! Signal: Set LiveView snapshot flag.
        /*!
        This signal emits save sflag to the connected slot in ProcessingThread.
        \param sFlag a bool argument.
        */
        void setLiveViewSaveImgFlag(bool sFlag);
        //! Signal: Set record flag.
        /*!
        This signal emits record rflag to the connected slot in ProcessingThread.
        \param rFlag a bool argument.
        */
        void setRecordFlag(bool rFlag);
};

#endif // MAINWINDOW_H
