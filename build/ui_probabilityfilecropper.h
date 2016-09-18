/********************************************************************************
** Form generated from reading UI file 'probabilityfilecropper.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROBABILITYFILECROPPER_H
#define UI_PROBABILITYFILECROPPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProbabilityFileCropper
{
public:
    QWidget *centralwidget;
    QPushButton *cut;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *probabilityFileName;
    QPushButton *selectProbabiltyFile;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *directoryToSaveFile;
    QPushButton *selectDirectory;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayoutStartPoint;
    QLabel *label_4;
    QSpinBox *startX;
    QLabel *label_5;
    QSpinBox *startY;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayoutImageSize;
    QLabel *label_6;
    QSpinBox *width;
    QLabel *label_7;
    QSpinBox *height;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayoutNUmberofBlocks;
    QLabel *label_27;
    QSpinBox *numBlocksX;
    QLabel *label_29;
    QSpinBox *numBlocksY;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayoutImageSize_2;
    QLabel *label_8;
    QSpinBox *imageWidth;
    QLabel *label_9;
    QSpinBox *imageHeight;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *numClasses;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProbabilityFileCropper)
    {
        if (ProbabilityFileCropper->objectName().isEmpty())
            ProbabilityFileCropper->setObjectName(QStringLiteral("ProbabilityFileCropper"));
        ProbabilityFileCropper->resize(739, 683);
        centralwidget = new QWidget(ProbabilityFileCropper);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        cut = new QPushButton(centralwidget);
        cut->setObjectName(QStringLiteral("cut"));
        cut->setGeometry(QRect(30, 530, 231, 28));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 239, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        probabilityFileName = new QLineEdit(layoutWidget);
        probabilityFileName->setObjectName(QStringLiteral("probabilityFileName"));

        horizontalLayout->addWidget(probabilityFileName);

        selectProbabiltyFile = new QPushButton(layoutWidget);
        selectProbabiltyFile->setObjectName(QStringLiteral("selectProbabiltyFile"));

        horizontalLayout->addWidget(selectProbabiltyFile);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 70, 239, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        directoryToSaveFile = new QLineEdit(layoutWidget1);
        directoryToSaveFile->setObjectName(QStringLiteral("directoryToSaveFile"));

        horizontalLayout_2->addWidget(directoryToSaveFile);

        selectDirectory = new QPushButton(layoutWidget1);
        selectDirectory->setObjectName(QStringLiteral("selectDirectory"));

        horizontalLayout_2->addWidget(selectDirectory);

        layoutWidget_4 = new QWidget(centralwidget);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 320, 351, 33));
        horizontalLayoutStartPoint = new QHBoxLayout(layoutWidget_4);
        horizontalLayoutStartPoint->setObjectName(QStringLiteral("horizontalLayoutStartPoint"));
        horizontalLayoutStartPoint->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayoutStartPoint->addWidget(label_4);

        startX = new QSpinBox(layoutWidget_4);
        startX->setObjectName(QStringLiteral("startX"));
        startX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        startX->setMaximum(100000);
        startX->setValue(0);

        horizontalLayoutStartPoint->addWidget(startX);

        label_5 = new QLabel(layoutWidget_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayoutStartPoint->addWidget(label_5);

        startY = new QSpinBox(layoutWidget_4);
        startY->setObjectName(QStringLiteral("startY"));
        startY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        startY->setMaximum(100000);
        startY->setValue(0);

        horizontalLayoutStartPoint->addWidget(startY);

        layoutWidget_5 = new QWidget(centralwidget);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 360, 351, 33));
        horizontalLayoutImageSize = new QHBoxLayout(layoutWidget_5);
        horizontalLayoutImageSize->setObjectName(QStringLiteral("horizontalLayoutImageSize"));
        horizontalLayoutImageSize->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayoutImageSize->addWidget(label_6);

        width = new QSpinBox(layoutWidget_5);
        width->setObjectName(QStringLiteral("width"));
        width->setButtonSymbols(QAbstractSpinBox::NoButtons);
        width->setMaximum(100000);
        width->setValue(1024);

        horizontalLayoutImageSize->addWidget(width);

        label_7 = new QLabel(layoutWidget_5);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayoutImageSize->addWidget(label_7);

        height = new QSpinBox(layoutWidget_5);
        height->setObjectName(QStringLiteral("height"));
        height->setButtonSymbols(QAbstractSpinBox::NoButtons);
        height->setMaximum(100000);
        height->setValue(1024);

        horizontalLayoutImageSize->addWidget(height);

        layoutWidget_8 = new QWidget(centralwidget);
        layoutWidget_8->setObjectName(QStringLiteral("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(20, 400, 351, 33));
        horizontalLayoutNUmberofBlocks = new QHBoxLayout(layoutWidget_8);
        horizontalLayoutNUmberofBlocks->setObjectName(QStringLiteral("horizontalLayoutNUmberofBlocks"));
        horizontalLayoutNUmberofBlocks->setContentsMargins(0, 0, 0, 0);
        label_27 = new QLabel(layoutWidget_8);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayoutNUmberofBlocks->addWidget(label_27);

        numBlocksX = new QSpinBox(layoutWidget_8);
        numBlocksX->setObjectName(QStringLiteral("numBlocksX"));
        numBlocksX->setMinimum(1);
        numBlocksX->setMaximum(10000);
        numBlocksX->setValue(1);

        horizontalLayoutNUmberofBlocks->addWidget(numBlocksX);

        label_29 = new QLabel(layoutWidget_8);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayoutNUmberofBlocks->addWidget(label_29);

        numBlocksY = new QSpinBox(layoutWidget_8);
        numBlocksY->setObjectName(QStringLiteral("numBlocksY"));
        numBlocksY->setMinimum(1);
        numBlocksY->setMaximum(10000);
        numBlocksY->setValue(1);

        horizontalLayoutNUmberofBlocks->addWidget(numBlocksY);

        layoutWidget_6 = new QWidget(centralwidget);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 140, 370, 33));
        horizontalLayoutImageSize_2 = new QHBoxLayout(layoutWidget_6);
        horizontalLayoutImageSize_2->setObjectName(QStringLiteral("horizontalLayoutImageSize_2"));
        horizontalLayoutImageSize_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget_6);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayoutImageSize_2->addWidget(label_8);

        imageWidth = new QSpinBox(layoutWidget_6);
        imageWidth->setObjectName(QStringLiteral("imageWidth"));
        imageWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        imageWidth->setMaximum(100000);
        imageWidth->setValue(1024);

        horizontalLayoutImageSize_2->addWidget(imageWidth);

        label_9 = new QLabel(layoutWidget_6);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayoutImageSize_2->addWidget(label_9);

        imageHeight = new QSpinBox(layoutWidget_6);
        imageHeight->setObjectName(QStringLiteral("imageHeight"));
        imageHeight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        imageHeight->setMaximum(100000);
        imageHeight->setValue(1024);

        horizontalLayoutImageSize_2->addWidget(imageHeight);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 200, 221, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        numClasses = new QSpinBox(layoutWidget2);
        numClasses->setObjectName(QStringLiteral("numClasses"));

        horizontalLayout_4->addWidget(numClasses);

        ProbabilityFileCropper->setCentralWidget(centralwidget);
        cut->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget_4->raise();
        layoutWidget_5->raise();
        layoutWidget_8->raise();
        layoutWidget_6->raise();
        layoutWidget->raise();
        label->raise();
        menubar = new QMenuBar(ProbabilityFileCropper);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 739, 26));
        ProbabilityFileCropper->setMenuBar(menubar);
        statusbar = new QStatusBar(ProbabilityFileCropper);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ProbabilityFileCropper->setStatusBar(statusbar);

        retranslateUi(ProbabilityFileCropper);

        QMetaObject::connectSlotsByName(ProbabilityFileCropper);
    } // setupUi

    void retranslateUi(QMainWindow *ProbabilityFileCropper)
    {
        ProbabilityFileCropper->setWindowTitle(QApplication::translate("ProbabilityFileCropper", "MainWindow", 0));
        cut->setText(QApplication::translate("ProbabilityFileCropper", "cut", 0));
        selectProbabiltyFile->setText(QApplication::translate("ProbabilityFileCropper", "...", 0));
        selectDirectory->setText(QApplication::translate("ProbabilityFileCropper", "...", 0));
        label_4->setText(QApplication::translate("ProbabilityFileCropper", "StartX", 0));
        label_5->setText(QApplication::translate("ProbabilityFileCropper", "StartY", 0));
        label_6->setText(QApplication::translate("ProbabilityFileCropper", "Width", 0));
        label_7->setText(QApplication::translate("ProbabilityFileCropper", "Height", 0));
        label_27->setText(QApplication::translate("ProbabilityFileCropper", "nBlocksX", 0));
        label_29->setText(QApplication::translate("ProbabilityFileCropper", "nBlocksY", 0));
        label_8->setText(QApplication::translate("ProbabilityFileCropper", "Image width", 0));
        label_9->setText(QApplication::translate("ProbabilityFileCropper", "Image height", 0));
        label->setText(QApplication::translate("ProbabilityFileCropper", "number of classes", 0));
    } // retranslateUi

};

namespace Ui {
    class ProbabilityFileCropper: public Ui_ProbabilityFileCropper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROBABILITYFILECROPPER_H
