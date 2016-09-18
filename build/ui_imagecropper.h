/********************************************************************************
** Form generated from reading UI file 'imagecropper.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGECROPPER_H
#define UI_IMAGECROPPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageCropper
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *CroppingSettings;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *ifDeleteNoise;
    QHBoxLayout *horizontalLayout_3;
    QLabel *numStd_left_2;
    QDoubleSpinBox *nStdLeft;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QDoubleSpinBox *nStdRight;
    QFrame *frame_2;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *ifRescale;
    QHBoxLayout *horizontalLayout_10;
    QLabel *scaledMinLabel_3;
    QDoubleSpinBox *scaledMin;
    QHBoxLayout *horizontalLayout_11;
    QLabel *scaledMaxLabel;
    QDoubleSpinBox *scaledMax;
    QFrame *frame_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayoutStartPoint_3;
    QLabel *label_12;
    QSpinBox *startX;
    QLabel *label_13;
    QSpinBox *startY;
    QHBoxLayout *horizontalLayoutImageSize_3;
    QLabel *label_14;
    QSpinBox *width;
    QLabel *label_15;
    QSpinBox *height;
    QHBoxLayout *horizontalLayoutNUmberofBlocks_3;
    QLabel *label_31;
    QSpinBox *nBlocksX;
    QLabel *label_32;
    QSpinBox *nBlocksY;
    QFrame *frame_4;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutFileName;
    QLineEdit *fileName;
    QPushButton *selectFileName;
    QHBoxLayout *horizontalLayoutFileName_2;
    QLineEdit *directoryName;
    QPushButton *selectDirectory;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLineEdit *fullImageWidth;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *fullImageHeight;
    QPushButton *cut;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *bandMap;
    QLineEdit *orderMin;
    QLabel *label_4;
    QLineEdit *orderMax;
    QLabel *label_5;
    QPushButton *crop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ImageCropper)
    {
        if (ImageCropper->objectName().isEmpty())
            ImageCropper->setObjectName(QStringLiteral("ImageCropper"));
        ImageCropper->resize(425, 733);
        centralwidget = new QWidget(ImageCropper);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 148, 401, 331));
        tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        CroppingSettings = new QWidget();
        CroppingSettings->setObjectName(QStringLiteral("CroppingSettings"));
        layoutWidget_2 = new QWidget(CroppingSettings);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 10, 4, 4));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));

        verticalLayout_7->addLayout(horizontalLayout_7);

        layoutWidget = new QWidget(CroppingSettings);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 381, 291));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(layoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget_3 = new QWidget(frame);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 10, 174, 103));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        ifDeleteNoise = new QCheckBox(layoutWidget_3);
        ifDeleteNoise->setObjectName(QStringLiteral("ifDeleteNoise"));
        ifDeleteNoise->setChecked(false);

        verticalLayout_6->addWidget(ifDeleteNoise);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        numStd_left_2 = new QLabel(layoutWidget_3);
        numStd_left_2->setObjectName(QStringLiteral("numStd_left_2"));

        horizontalLayout_3->addWidget(numStd_left_2);

        nStdLeft = new QDoubleSpinBox(layoutWidget_3);
        nStdLeft->setObjectName(QStringLiteral("nStdLeft"));
        nStdLeft->setButtonSymbols(QAbstractSpinBox::NoButtons);
        nStdLeft->setDecimals(1);
        nStdLeft->setMinimum(0);
        nStdLeft->setSingleStep(0.5);
        nStdLeft->setValue(3);

        horizontalLayout_3->addWidget(nStdLeft);


        verticalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_3 = new QLabel(layoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_8->addWidget(label_3);

        nStdRight = new QDoubleSpinBox(layoutWidget_3);
        nStdRight->setObjectName(QStringLiteral("nStdRight"));
        nStdRight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        nStdRight->setDecimals(1);
        nStdRight->setSingleStep(0.5);
        nStdRight->setValue(3);

        horizontalLayout_8->addWidget(nStdRight);


        verticalLayout_6->addLayout(horizontalLayout_8);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        layoutWidget_4 = new QWidget(frame_2);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(0, 10, 217, 103));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        ifRescale = new QCheckBox(layoutWidget_4);
        ifRescale->setObjectName(QStringLiteral("ifRescale"));

        verticalLayout_4->addWidget(ifRescale);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        scaledMinLabel_3 = new QLabel(layoutWidget_4);
        scaledMinLabel_3->setObjectName(QStringLiteral("scaledMinLabel_3"));

        horizontalLayout_10->addWidget(scaledMinLabel_3);

        scaledMin = new QDoubleSpinBox(layoutWidget_4);
        scaledMin->setObjectName(QStringLiteral("scaledMin"));
        scaledMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        scaledMin->setDecimals(0);
        scaledMin->setMinimum(0);
        scaledMin->setMaximum(1e+06);
        scaledMin->setSingleStep(1);
        scaledMin->setValue(0);

        horizontalLayout_10->addWidget(scaledMin);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        scaledMaxLabel = new QLabel(layoutWidget_4);
        scaledMaxLabel->setObjectName(QStringLiteral("scaledMaxLabel"));

        horizontalLayout_11->addWidget(scaledMaxLabel);

        scaledMax = new QDoubleSpinBox(layoutWidget_4);
        scaledMax->setObjectName(QStringLiteral("scaledMax"));
        scaledMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        scaledMax->setDecimals(0);
        scaledMax->setMaximum(1e+06);
        scaledMax->setSingleStep(0.5);
        scaledMax->setValue(255);

        horizontalLayout_11->addWidget(scaledMax);


        verticalLayout_4->addLayout(horizontalLayout_11);


        horizontalLayout->addWidget(frame_2);


        verticalLayout_3->addLayout(horizontalLayout);

        frame_3 = new QFrame(layoutWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::WinPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        layoutWidget1 = new QWidget(frame_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 361, 110));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutStartPoint_3 = new QHBoxLayout();
        horizontalLayoutStartPoint_3->setObjectName(QStringLiteral("horizontalLayoutStartPoint_3"));
        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayoutStartPoint_3->addWidget(label_12);

        startX = new QSpinBox(layoutWidget1);
        startX->setObjectName(QStringLiteral("startX"));
        startX->setFrame(true);
        startX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        startX->setKeyboardTracking(true);
        startX->setMaximum(100000);
        startX->setValue(0);

        horizontalLayoutStartPoint_3->addWidget(startX);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayoutStartPoint_3->addWidget(label_13);

        startY = new QSpinBox(layoutWidget1);
        startY->setObjectName(QStringLiteral("startY"));
        startY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        startY->setMaximum(100000);
        startY->setValue(0);

        horizontalLayoutStartPoint_3->addWidget(startY);


        verticalLayout_2->addLayout(horizontalLayoutStartPoint_3);

        horizontalLayoutImageSize_3 = new QHBoxLayout();
        horizontalLayoutImageSize_3->setObjectName(QStringLiteral("horizontalLayoutImageSize_3"));
        label_14 = new QLabel(layoutWidget1);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayoutImageSize_3->addWidget(label_14);

        width = new QSpinBox(layoutWidget1);
        width->setObjectName(QStringLiteral("width"));
        width->setButtonSymbols(QAbstractSpinBox::NoButtons);
        width->setMaximum(100000);
        width->setValue(1024);

        horizontalLayoutImageSize_3->addWidget(width);

        label_15 = new QLabel(layoutWidget1);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayoutImageSize_3->addWidget(label_15);

        height = new QSpinBox(layoutWidget1);
        height->setObjectName(QStringLiteral("height"));
        height->setButtonSymbols(QAbstractSpinBox::NoButtons);
        height->setMaximum(100000);
        height->setValue(1024);

        horizontalLayoutImageSize_3->addWidget(height);


        verticalLayout_2->addLayout(horizontalLayoutImageSize_3);

        horizontalLayoutNUmberofBlocks_3 = new QHBoxLayout();
        horizontalLayoutNUmberofBlocks_3->setObjectName(QStringLiteral("horizontalLayoutNUmberofBlocks_3"));
        label_31 = new QLabel(layoutWidget1);
        label_31->setObjectName(QStringLiteral("label_31"));

        horizontalLayoutNUmberofBlocks_3->addWidget(label_31);

        nBlocksX = new QSpinBox(layoutWidget1);
        nBlocksX->setObjectName(QStringLiteral("nBlocksX"));
        nBlocksX->setMinimum(1);
        nBlocksX->setMaximum(10000);
        nBlocksX->setValue(1);

        horizontalLayoutNUmberofBlocks_3->addWidget(nBlocksX);

        label_32 = new QLabel(layoutWidget1);
        label_32->setObjectName(QStringLiteral("label_32"));

        horizontalLayoutNUmberofBlocks_3->addWidget(label_32);

        nBlocksY = new QSpinBox(layoutWidget1);
        nBlocksY->setObjectName(QStringLiteral("nBlocksY"));
        nBlocksY->setMinimum(1);
        nBlocksY->setMaximum(10000);
        nBlocksY->setValue(1);

        horizontalLayoutNUmberofBlocks_3->addWidget(nBlocksY);


        verticalLayout_2->addLayout(horizontalLayoutNUmberofBlocks_3);


        verticalLayout_3->addWidget(frame_3);

        tabWidget->addTab(CroppingSettings, QString());
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(10, 0, 401, 131));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        layoutWidget2 = new QWidget(frame_4);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 381, 112));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutFileName = new QHBoxLayout();
        horizontalLayoutFileName->setObjectName(QStringLiteral("horizontalLayoutFileName"));
        horizontalLayoutFileName->setSizeConstraint(QLayout::SetFixedSize);
        fileName = new QLineEdit(layoutWidget2);
        fileName->setObjectName(QStringLiteral("fileName"));
        QPalette palette;
        QBrush brush(QColor(128, 128, 128, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        fileName->setPalette(palette);
        fileName->setFrame(true);

        horizontalLayoutFileName->addWidget(fileName);

        selectFileName = new QPushButton(layoutWidget2);
        selectFileName->setObjectName(QStringLiteral("selectFileName"));

        horizontalLayoutFileName->addWidget(selectFileName);


        verticalLayout->addLayout(horizontalLayoutFileName);

        horizontalLayoutFileName_2 = new QHBoxLayout();
        horizontalLayoutFileName_2->setObjectName(QStringLiteral("horizontalLayoutFileName_2"));
        directoryName = new QLineEdit(layoutWidget2);
        directoryName->setObjectName(QStringLiteral("directoryName"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        directoryName->setPalette(palette1);
        directoryName->setFrame(true);

        horizontalLayoutFileName_2->addWidget(directoryName);

        selectDirectory = new QPushButton(layoutWidget2);
        selectDirectory->setObjectName(QStringLiteral("selectDirectory"));

        horizontalLayoutFileName_2->addWidget(selectDirectory);


        verticalLayout->addLayout(horizontalLayoutFileName_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        fullImageWidth = new QLineEdit(layoutWidget2);
        fullImageWidth->setObjectName(QStringLiteral("fullImageWidth"));

        horizontalLayout_5->addWidget(fullImageWidth);


        horizontalLayout_9->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_6->addWidget(label_7);

        fullImageHeight = new QLineEdit(layoutWidget2);
        fullImageHeight->setObjectName(QStringLiteral("fullImageHeight"));

        horizontalLayout_6->addWidget(fullImageHeight);


        horizontalLayout_9->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_9);

        cut = new QPushButton(centralwidget);
        cut->setObjectName(QStringLiteral("cut"));
        cut->setGeometry(QRect(10, 610, 401, 28));
        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 490, 241, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        bandMap = new QLineEdit(layoutWidget3);
        bandMap->setObjectName(QStringLiteral("bandMap"));

        horizontalLayout_2->addWidget(bandMap);

        orderMin = new QLineEdit(centralwidget);
        orderMin->setObjectName(QStringLiteral("orderMin"));
        orderMin->setGeometry(QRect(66, 530, 193, 30));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 530, 40, 30));
        orderMax = new QLineEdit(centralwidget);
        orderMax->setObjectName(QStringLiteral("orderMax"));
        orderMax->setGeometry(QRect(66, 570, 193, 30));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 570, 40, 30));
        crop = new QPushButton(centralwidget);
        crop->setObjectName(QStringLiteral("crop"));
        crop->setGeometry(QRect(10, 640, 401, 28));
        ImageCropper->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ImageCropper);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 425, 26));
        ImageCropper->setMenuBar(menubar);
        statusbar = new QStatusBar(ImageCropper);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ImageCropper->setStatusBar(statusbar);

        retranslateUi(ImageCropper);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ImageCropper);
    } // setupUi

    void retranslateUi(QMainWindow *ImageCropper)
    {
        ImageCropper->setWindowTitle(QApplication::translate("ImageCropper", "MainWindow", 0));
        ifDeleteNoise->setText(QApplication::translate("ImageCropper", "Delete noise", 0));
        numStd_left_2->setText(QApplication::translate("ImageCropper", "Mean - std x", 0));
        label_3->setText(QApplication::translate("ImageCropper", "Mean + std x", 0));
        ifRescale->setText(QApplication::translate("ImageCropper", "Rescale linearly", 0));
        scaledMinLabel_3->setText(QApplication::translate("ImageCropper", "Rescaled min", 0));
        scaledMaxLabel->setText(QApplication::translate("ImageCropper", "Rescaled max", 0));
        label_12->setText(QApplication::translate("ImageCropper", "StartX", 0));
        label_13->setText(QApplication::translate("ImageCropper", "StartY", 0));
        label_14->setText(QApplication::translate("ImageCropper", "Width", 0));
        label_15->setText(QApplication::translate("ImageCropper", "Height", 0));
        label_31->setText(QApplication::translate("ImageCropper", "nBlocksX", 0));
        label_32->setText(QApplication::translate("ImageCropper", "nBlocksY", 0));
        tabWidget->setTabText(tabWidget->indexOf(CroppingSettings), QApplication::translate("ImageCropper", "Cropping settings", 0));
        fileName->setInputMask(QString());
        fileName->setText(QApplication::translate("ImageCropper", "image/file/path/.../image.tif", 0));
        selectFileName->setText(QApplication::translate("ImageCropper", "...", 0));
        directoryName->setInputMask(QString());
        directoryName->setText(QApplication::translate("ImageCropper", "Directory/to/save/results/", 0));
        selectDirectory->setText(QApplication::translate("ImageCropper", "...", 0));
        label->setText(QApplication::translate("ImageCropper", "Full image width", 0));
        label_7->setText(QApplication::translate("ImageCropper", "Full image height", 0));
        cut->setText(QApplication::translate("ImageCropper", "Cut", 0));
        label_2->setText(QApplication::translate("ImageCropper", "Bands", 0));
        label_4->setText(QApplication::translate("ImageCropper", "Min", 0));
        label_5->setText(QApplication::translate("ImageCropper", "Bands", 0));
        crop->setText(QApplication::translate("ImageCropper", "Crop", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageCropper: public Ui_ImageCropper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGECROPPER_H
