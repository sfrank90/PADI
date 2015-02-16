/********************************************************************************
** Form generated from reading UI file 'CameraConnectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACONNECTDIALOG_H
#define UI_CAMERACONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraConnectDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_1;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *liveViewRadio;
    QSpacerItem *horizontalSpacer_1;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *recordedRadio;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QRadioButton *imageRadio;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *okCancelBox;
    QSpacerItem *verticalSpacer;
    QButtonGroup *modeRadioGroup;

    void setupUi(QDialog *CameraConnectDialog)
    {
        if (CameraConnectDialog->objectName().isEmpty())
            CameraConnectDialog->setObjectName(QStringLiteral("CameraConnectDialog"));
        CameraConnectDialog->resize(424, 200);
        layoutWidget = new QWidget(CameraConnectDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 391, 351));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_1 = new QLabel(layoutWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_1->setFont(font);

        verticalLayout_3->addWidget(label_1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        liveViewRadio = new QRadioButton(layoutWidget);
        modeRadioGroup = new QButtonGroup(CameraConnectDialog);
        modeRadioGroup->setObjectName(QStringLiteral("modeRadioGroup"));
        modeRadioGroup->addButton(liveViewRadio);
        liveViewRadio->setObjectName(QStringLiteral("liveViewRadio"));

        horizontalLayout_2->addWidget(liveViewRadio);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_1);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        recordedRadio = new QRadioButton(layoutWidget);
        modeRadioGroup->addButton(recordedRadio);
        recordedRadio->setObjectName(QStringLiteral("recordedRadio"));

        horizontalLayout_8->addWidget(recordedRadio);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        imageRadio = new QRadioButton(layoutWidget);
        modeRadioGroup->addButton(imageRadio);
        imageRadio->setObjectName(QStringLiteral("imageRadio"));

        horizontalLayout->addWidget(imageRadio);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        okCancelBox = new QDialogButtonBox(layoutWidget);
        okCancelBox->setObjectName(QStringLiteral("okCancelBox"));
        okCancelBox->setOrientation(Qt::Horizontal);
        okCancelBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(okCancelBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);


        retranslateUi(CameraConnectDialog);
        QObject::connect(okCancelBox, SIGNAL(accepted()), CameraConnectDialog, SLOT(accept()));
        QObject::connect(okCancelBox, SIGNAL(rejected()), CameraConnectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraConnectDialog)
    {
        CameraConnectDialog->setWindowTitle(QApplication::translate("CameraConnectDialog", "Connect to Camera", 0));
        label_1->setText(QApplication::translate("CameraConnectDialog", "Select mode:", 0));
        liveViewRadio->setText(QApplication::translate("CameraConnectDialog", "LiveView", 0));
        recordedRadio->setText(QApplication::translate("CameraConnectDialog", "Recorded Video", 0));
        imageRadio->setText(QApplication::translate("CameraConnectDialog", "Image", 0));
    } // retranslateUi

};

namespace Ui {
    class CameraConnectDialog: public Ui_CameraConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACONNECTDIALOG_H
