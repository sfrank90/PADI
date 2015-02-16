/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionQuit;
    QAction *actionAddOveralys;
    QAction *actionScaleToFitFrame;
    QAction *actionFullScreen;
    QAction *actionMode;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *imagelabel;
    QFrame *line;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QPushButton *recDirButton;
    QPushButton *recVideoButton;
    QPushButton *snapshotButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *overlaybutton;
    QLabel *overlaylabel;
    QPushButton *modebutton;
    QLabel *modelabel;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuOptions;
    QMenu *menuView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(876, 814);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionAddOveralys = new QAction(MainWindow);
        actionAddOveralys->setObjectName(QStringLiteral("actionAddOveralys"));
        actionAddOveralys->setCheckable(false);
        actionScaleToFitFrame = new QAction(MainWindow);
        actionScaleToFitFrame->setObjectName(QStringLiteral("actionScaleToFitFrame"));
        actionScaleToFitFrame->setCheckable(true);
        actionFullScreen = new QAction(MainWindow);
        actionFullScreen->setObjectName(QStringLiteral("actionFullScreen"));
        actionFullScreen->setCheckable(true);
        actionMode = new QAction(MainWindow);
        actionMode->setObjectName(QStringLiteral("actionMode"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        imagelabel = new QLabel(centralWidget);
        imagelabel->setObjectName(QStringLiteral("imagelabel"));
        imagelabel->setMinimumSize(QSize(800, 600));

        verticalLayout->addWidget(imagelabel);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        recDirButton = new QPushButton(groupBox);
        recDirButton->setObjectName(QStringLiteral("recDirButton"));
        recDirButton->setGeometry(QRect(20, 20, 223, 23));
        recVideoButton = new QPushButton(groupBox);
        recVideoButton->setObjectName(QStringLiteral("recVideoButton"));
        recVideoButton->setGeometry(QRect(50, 50, 75, 23));
        snapshotButton = new QPushButton(groupBox);
        snapshotButton->setObjectName(QStringLiteral("snapshotButton"));
        snapshotButton->setGeometry(QRect(130, 50, 75, 23));

        gridLayout->addWidget(groupBox, 3, 3, 5, 2);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        overlaybutton = new QPushButton(centralWidget);
        overlaybutton->setObjectName(QStringLiteral("overlaybutton"));

        gridLayout->addWidget(overlaybutton, 3, 1, 1, 1);

        overlaylabel = new QLabel(centralWidget);
        overlaylabel->setObjectName(QStringLiteral("overlaylabel"));
        sizePolicy.setHeightForWidth(overlaylabel->sizePolicy().hasHeightForWidth());
        overlaylabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        overlaylabel->setFont(font);
        overlaylabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(overlaylabel, 3, 0, 1, 1);

        modebutton = new QPushButton(centralWidget);
        modebutton->setObjectName(QStringLiteral("modebutton"));

        gridLayout->addWidget(modebutton, 2, 1, 1, 1);

        modelabel = new QLabel(centralWidget);
        modelabel->setObjectName(QStringLiteral("modelabel"));
        sizePolicy.setHeightForWidth(modelabel->sizePolicy().hasHeightForWidth());
        modelabel->setSizePolicy(sizePolicy);
        modelabel->setFont(font);
        modelabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(modelabel, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 876, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuOptions->addAction(actionMode);
        menuOptions->addAction(actionAddOveralys);
        menuView->addAction(actionFullScreen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Mister Spex 2014", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionAddOveralys->setText(QApplication::translate("MainWindow", "Overlays", 0));
        actionScaleToFitFrame->setText(QApplication::translate("MainWindow", "Scale to fit frame", 0));
        actionFullScreen->setText(QApplication::translate("MainWindow", "Full Screen", 0));
        actionMode->setText(QApplication::translate("MainWindow", "Mode", 0));
        imagelabel->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Recording Options", 0));
        recDirButton->setText(QApplication::translate("MainWindow", "Save Directory", 0));
        recVideoButton->setText(QApplication::translate("MainWindow", "Rec. Video", 0));
        snapshotButton->setText(QApplication::translate("MainWindow", "Snapshot", 0));
        overlaybutton->setText(QApplication::translate("MainWindow", "Overlays", 0));
        overlaylabel->setText(QApplication::translate("MainWindow", "Overlays:", 0));
        modebutton->setText(QApplication::translate("MainWindow", "Mode", 0));
        modelabel->setText(QApplication::translate("MainWindow", "Select mode:", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
