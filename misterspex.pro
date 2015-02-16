QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = misterspex
TEMPLATE = app

DEFINES += APP_VERSION=\\\"1.0.1\\\"


win32 {
    INCLUDEPATH += C:\\opencv\\build\\include

    CONFIG(release, debug|release)
    {
        LIBS += -LC:\\opencv\\build\\x86\\vc11\\lib \
            -lopencv_core247 \
            -lopencv_highgui247 \
            -lopencv_imgproc247 \
            -lopencv_objdetect247 \
    }
    CONFIG(debug, debug|release)
    {
        LIBS += -LC:\\opencv\\build\\x86\\vc11\\lib \
            -lopencv_core247d \
            -lopencv_highgui247d \
            -lopencv_imgproc247d \
            -lopencv_objdetect247d
    }

    RC_FILE += Misterspex.rc
}
else {
    message("Compile for linux")
    QT_CONFIG -= no-pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

SOURCES += main.cpp \
    CameraConnectDialog.cpp \
    FaceDetection.cpp \
    ImageConversion.cpp \
    ImageHandler.cpp \
    ImageProcessingSettingsDialog.cpp \
    MainWindow.cpp \
    ProcessingThread.cpp \
    PlaybackThread.cpp \
    VideoImageBuffer.cpp \
    VideoThread.cpp \
    RecordVideoThread.cpp

HEADERS += \
    Buffer.h \
    CameraConnectDialog.h \
    Config.h \
    FaceDetection.h \
    ImageConversion.h \
    ImageHandler.h \
    ImageProcessingSettingsDialog.h \
    MainWindow.h \
    ProcessingThread.h \
    PlaybackThread.h \
    Structures.h \
    VideoImageBuffer.h \
    VideoThread.h \
    PlaybackThread.h \
    RecordVideoThread.h


FORMS += \
    MainWindow.ui \
    CameraConnectDialog.ui \
    ImageProcessingSettingsDialog.ui

QMAKE_CXXFLAGS += -Wall
