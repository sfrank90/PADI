/********************************************************************************
** Form generated from reading UI file 'ImageProcessingSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSINGSETTINGSDIALOG_H
#define UI_IMAGEPROCESSINGSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessingSettingsDialog
{
public:
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_40;
    QTabWidget *tabWidget;
    QWidget *overlaytab;
    QWidget *layoutWidget2_5;
    QVBoxLayout *verticalLayout_41;
    QHBoxLayout *horizontalLayout_48;
    QVBoxLayout *verticalLayout_42;
    QHBoxLayout *horizontalLayout;
    QLabel *label_68;
    QVBoxLayout *verticalLayout_43;
    QCheckBox *glasses;
    QCheckBox *nose;
    QCheckBox *redlips;
    QSpacerItem *verticalSpacer_29;
    QFrame *line;
    QCheckBox *showFacedetection;
    QCheckBox *showOverlays;
    QSpacerItem *verticalSpacer_31;
    QPushButton *resetOverlays;
    QFrame *line_9;
    QHBoxLayout *horizontalLayout_59;
    QPushButton *applyButton;
    QFrame *line_10;
    QDialogButtonBox *okCancelBox;

    void setupUi(QDialog *ImageProcessingSettingsDialog)
    {
        if (ImageProcessingSettingsDialog->objectName().isEmpty())
            ImageProcessingSettingsDialog->setObjectName(QStringLiteral("ImageProcessingSettingsDialog"));
        ImageProcessingSettingsDialog->resize(440, 381);
        layoutWidget1 = new QWidget(ImageProcessingSettingsDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 421, 361));
        verticalLayout_40 = new QVBoxLayout(layoutWidget1);
        verticalLayout_40->setObjectName(QStringLiteral("verticalLayout_40"));
        verticalLayout_40->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(layoutWidget1);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        overlaytab = new QWidget();
        overlaytab->setObjectName(QStringLiteral("overlaytab"));
        layoutWidget2_5 = new QWidget(overlaytab);
        layoutWidget2_5->setObjectName(QStringLiteral("layoutWidget2_5"));
        layoutWidget2_5->setGeometry(QRect(10, 10, 401, 221));
        verticalLayout_41 = new QVBoxLayout(layoutWidget2_5);
        verticalLayout_41->setObjectName(QStringLiteral("verticalLayout_41"));
        verticalLayout_41->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setObjectName(QStringLiteral("horizontalLayout_48"));
        verticalLayout_42 = new QVBoxLayout();
        verticalLayout_42->setObjectName(QStringLiteral("verticalLayout_42"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        verticalLayout_42->addLayout(horizontalLayout);

        label_68 = new QLabel(layoutWidget2_5);
        label_68->setObjectName(QStringLiteral("label_68"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_68->sizePolicy().hasHeightForWidth());
        label_68->setSizePolicy(sizePolicy);
        label_68->setMinimumSize(QSize(0, 27));
        label_68->setMaximumSize(QSize(140, 27));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        label_68->setFont(font);

        verticalLayout_42->addWidget(label_68);

        verticalLayout_43 = new QVBoxLayout();
        verticalLayout_43->setObjectName(QStringLiteral("verticalLayout_43"));
        glasses = new QCheckBox(layoutWidget2_5);
        glasses->setObjectName(QStringLiteral("glasses"));

        verticalLayout_43->addWidget(glasses);

        nose = new QCheckBox(layoutWidget2_5);
        nose->setObjectName(QStringLiteral("nose"));

        verticalLayout_43->addWidget(nose);

        redlips = new QCheckBox(layoutWidget2_5);
        redlips->setObjectName(QStringLiteral("redlips"));

        verticalLayout_43->addWidget(redlips);

        verticalSpacer_29 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_43->addItem(verticalSpacer_29);


        verticalLayout_42->addLayout(verticalLayout_43);


        horizontalLayout_48->addLayout(verticalLayout_42);


        verticalLayout_41->addLayout(horizontalLayout_48);

        line = new QFrame(layoutWidget2_5);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_41->addWidget(line);

        showFacedetection = new QCheckBox(layoutWidget2_5);
        showFacedetection->setObjectName(QStringLiteral("showFacedetection"));

        verticalLayout_41->addWidget(showFacedetection);

        showOverlays = new QCheckBox(layoutWidget2_5);
        showOverlays->setObjectName(QStringLiteral("showOverlays"));
        showOverlays->setChecked(true);

        verticalLayout_41->addWidget(showOverlays);

        verticalSpacer_31 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_41->addItem(verticalSpacer_31);

        resetOverlays = new QPushButton(layoutWidget2_5);
        resetOverlays->setObjectName(QStringLiteral("resetOverlays"));

        verticalLayout_41->addWidget(resetOverlays);

        tabWidget->addTab(overlaytab, QString());

        verticalLayout_40->addWidget(tabWidget);

        line_9 = new QFrame(layoutWidget1);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        verticalLayout_40->addWidget(line_9);

        horizontalLayout_59 = new QHBoxLayout();
        horizontalLayout_59->setObjectName(QStringLiteral("horizontalLayout_59"));
        applyButton = new QPushButton(layoutWidget1);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        horizontalLayout_59->addWidget(applyButton);


        verticalLayout_40->addLayout(horizontalLayout_59);

        line_10 = new QFrame(layoutWidget1);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        verticalLayout_40->addWidget(line_10);

        okCancelBox = new QDialogButtonBox(layoutWidget1);
        okCancelBox->setObjectName(QStringLiteral("okCancelBox"));
        okCancelBox->setOrientation(Qt::Horizontal);
        okCancelBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_40->addWidget(okCancelBox);

        QWidget::setTabOrder(tabWidget, applyButton);
        QWidget::setTabOrder(applyButton, okCancelBox);
        QWidget::setTabOrder(okCancelBox, resetOverlays);

        retranslateUi(ImageProcessingSettingsDialog);
        QObject::connect(okCancelBox, SIGNAL(accepted()), ImageProcessingSettingsDialog, SLOT(accept()));
        QObject::connect(okCancelBox, SIGNAL(rejected()), ImageProcessingSettingsDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ImageProcessingSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageProcessingSettingsDialog)
    {
        ImageProcessingSettingsDialog->setWindowTitle(QApplication::translate("ImageProcessingSettingsDialog", "Image Processing Settings", 0));
        label_68->setText(QApplication::translate("ImageProcessingSettingsDialog", "Type:", 0));
        glasses->setText(QApplication::translate("ImageProcessingSettingsDialog", "Glasses", 0));
        nose->setText(QApplication::translate("ImageProcessingSettingsDialog", "Nose", 0));
        redlips->setText(QApplication::translate("ImageProcessingSettingsDialog", "Red Lips", 0));
        showFacedetection->setText(QApplication::translate("ImageProcessingSettingsDialog", "Show facedetection", 0));
        showOverlays->setText(QApplication::translate("ImageProcessingSettingsDialog", "Show Overlays", 0));
        resetOverlays->setText(QApplication::translate("ImageProcessingSettingsDialog", "Reset", 0));
        tabWidget->setTabText(tabWidget->indexOf(overlaytab), QApplication::translate("ImageProcessingSettingsDialog", "Overlays", 0));
#ifndef QT_NO_TOOLTIP
        applyButton->setToolTip(QApplication::translate("ImageProcessingSettingsDialog", "<html><head/><body><p>If you are in the &quot;Single Image Mode&quot; then the apply function only updates the stored settings. To really apply hit &quot;OK&quot;</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        applyButton->setText(QApplication::translate("ImageProcessingSettingsDialog", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessingSettingsDialog: public Ui_ImageProcessingSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSINGSETTINGSDIALOG_H
