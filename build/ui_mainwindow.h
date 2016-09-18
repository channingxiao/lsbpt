/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTest;
    QAction *actionHoover_Calculator;
    QAction *actionImage_Cropper;
    QAction *actionProbability_File_Cropper;
    QWidget *centralWidget;
    QPushButton *Go;
    QFrame *frame_2;
    QCheckBox *ifAddProbabilityModel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDoubleSpinBox *probabilityModelWeight;
    QWidget *layoutWidget_11;
    QVBoxLayout *verticalLayout;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *directoryProbabilities;
    QPushButton *selectDirectoryProbabilities;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_21;
    QSpinBox *nClasses;
    QCheckBox *useStdCut;
    QFrame *frame_3;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayoutStartPoint;
    QLabel *label_3;
    QSpinBox *roix;
    QLabel *label_4;
    QSpinBox *roiy;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayoutNUmberofBlocks;
    QLabel *label_27;
    QSpinBox *numBlocksX;
    QLabel *label_29;
    QSpinBox *numBlocksY;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayoutImageSize;
    QLabel *label_6;
    QSpinBox *roiw;
    QLabel *label_5;
    QSpinBox *roih;
    QFrame *frame_4;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_7;
    QSpinBox *nbins;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *areaWeighted;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_12;
    QDoubleSpinBox *areaExponent;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *ifUseMinimumToMerge;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_13;
    QSpinBox *floor;
    QCheckBox *ifPaintRandomColor;
    QWidget *layoutWidget_10;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *lamda;
    QFrame *frame_5;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *directoryName;
    QPushButton *selectDirectory;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayoutFileName;
    QLineEdit *fileName;
    QPushButton *selectFileName;
    QFrame *frame_6;
    QWidget *layoutWidget_12;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *ifDeleteNoise;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *numStd_left;
    QDoubleSpinBox *nStdLeft;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QDoubleSpinBox *nStdRight;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTool;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(388, 869);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionHoover_Calculator = new QAction(MainWindow);
        actionHoover_Calculator->setObjectName(QStringLiteral("actionHoover_Calculator"));
        actionImage_Cropper = new QAction(MainWindow);
        actionImage_Cropper->setObjectName(QStringLiteral("actionImage_Cropper"));
        actionProbability_File_Cropper = new QAction(MainWindow);
        actionProbability_File_Cropper->setObjectName(QStringLiteral("actionProbability_File_Cropper"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Go = new QPushButton(centralWidget);
        Go->setObjectName(QStringLiteral("Go"));
        Go->setGeometry(QRect(10, 760, 371, 29));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 350, 371, 181));
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        ifAddProbabilityModel = new QCheckBox(frame_2);
        ifAddProbabilityModel->setObjectName(QStringLiteral("ifAddProbabilityModel"));
        ifAddProbabilityModel->setGeometry(QRect(10, 0, 191, 25));
        layoutWidget = new QWidget(frame_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 100, 261, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        probabilityModelWeight = new QDoubleSpinBox(layoutWidget);
        probabilityModelWeight->setObjectName(QStringLiteral("probabilityModelWeight"));
        probabilityModelWeight->setMinimum(0);
        probabilityModelWeight->setMaximum(1);
        probabilityModelWeight->setSingleStep(0.1);
        probabilityModelWeight->setValue(0);

        horizontalLayout_2->addWidget(probabilityModelWeight);

        layoutWidget_11 = new QWidget(frame_2);
        layoutWidget_11->setObjectName(QStringLiteral("layoutWidget_11"));
        layoutWidget_11->setGeometry(QRect(10, 30, 351, 60));
        verticalLayout = new QVBoxLayout(layoutWidget_11);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget_11);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout->addWidget(label_10);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        directoryProbabilities = new QLineEdit(layoutWidget_11);
        directoryProbabilities->setObjectName(QStringLiteral("directoryProbabilities"));

        horizontalLayout_8->addWidget(directoryProbabilities);

        selectDirectoryProbabilities = new QPushButton(layoutWidget_11);
        selectDirectoryProbabilities->setObjectName(QStringLiteral("selectDirectoryProbabilities"));

        horizontalLayout_8->addWidget(selectDirectoryProbabilities);


        verticalLayout->addLayout(horizontalLayout_8);

        layoutWidget1 = new QWidget(frame_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 140, 151, 32));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget1);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_9->addWidget(label_21);

        nClasses = new QSpinBox(layoutWidget1);
        nClasses->setObjectName(QStringLiteral("nClasses"));
        nClasses->setButtonSymbols(QAbstractSpinBox::NoButtons);
        nClasses->setMaximum(1000);
        nClasses->setValue(2);

        horizontalLayout_9->addWidget(nClasses);

        useStdCut = new QCheckBox(frame_2);
        useStdCut->setObjectName(QStringLiteral("useStdCut"));
        useStdCut->setGeometry(QRect(220, 140, 131, 31));
        useStdCut->setChecked(true);
        layoutWidget->raise();
        ifAddProbabilityModel->raise();
        layoutWidget->raise();
        layoutWidget_11->raise();
        useStdCut->raise();
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(10, 110, 371, 131));
        frame_3->setFrameShape(QFrame::WinPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        layoutWidget_4 = new QWidget(frame_3);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 10, 351, 33));
        horizontalLayoutStartPoint = new QHBoxLayout(layoutWidget_4);
        horizontalLayoutStartPoint->setSpacing(6);
        horizontalLayoutStartPoint->setContentsMargins(11, 11, 11, 11);
        horizontalLayoutStartPoint->setObjectName(QStringLiteral("horizontalLayoutStartPoint"));
        horizontalLayoutStartPoint->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayoutStartPoint->addWidget(label_3);

        roix = new QSpinBox(layoutWidget_4);
        roix->setObjectName(QStringLiteral("roix"));
        roix->setButtonSymbols(QAbstractSpinBox::NoButtons);
        roix->setMaximum(100000);
        roix->setValue(0);

        horizontalLayoutStartPoint->addWidget(roix);

        label_4 = new QLabel(layoutWidget_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayoutStartPoint->addWidget(label_4);

        roiy = new QSpinBox(layoutWidget_4);
        roiy->setObjectName(QStringLiteral("roiy"));
        roiy->setButtonSymbols(QAbstractSpinBox::NoButtons);
        roiy->setMaximum(100000);
        roiy->setValue(0);

        horizontalLayoutStartPoint->addWidget(roiy);

        layoutWidget_8 = new QWidget(frame_3);
        layoutWidget_8->setObjectName(QStringLiteral("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(10, 90, 351, 33));
        horizontalLayoutNUmberofBlocks = new QHBoxLayout(layoutWidget_8);
        horizontalLayoutNUmberofBlocks->setSpacing(6);
        horizontalLayoutNUmberofBlocks->setContentsMargins(11, 11, 11, 11);
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

        layoutWidget_5 = new QWidget(frame_3);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 50, 351, 33));
        horizontalLayoutImageSize = new QHBoxLayout(layoutWidget_5);
        horizontalLayoutImageSize->setSpacing(6);
        horizontalLayoutImageSize->setContentsMargins(11, 11, 11, 11);
        horizontalLayoutImageSize->setObjectName(QStringLiteral("horizontalLayoutImageSize"));
        horizontalLayoutImageSize->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayoutImageSize->addWidget(label_6);

        roiw = new QSpinBox(layoutWidget_5);
        roiw->setObjectName(QStringLiteral("roiw"));
        roiw->setButtonSymbols(QAbstractSpinBox::NoButtons);
        roiw->setMaximum(100000);
        roiw->setValue(0);

        horizontalLayoutImageSize->addWidget(roiw);

        label_5 = new QLabel(layoutWidget_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayoutImageSize->addWidget(label_5);

        roih = new QSpinBox(layoutWidget_5);
        roih->setObjectName(QStringLiteral("roih"));
        roih->setButtonSymbols(QAbstractSpinBox::NoButtons);
        roih->setMaximum(100000);
        roih->setValue(0);

        horizontalLayoutImageSize->addWidget(roih);

        frame_4 = new QFrame(centralWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(10, 540, 371, 201));
        frame_4->setFrameShape(QFrame::WinPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        formLayoutWidget = new QWidget(frame_4);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 162, 33));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_7);

        nbins = new QSpinBox(formLayoutWidget);
        nbins->setObjectName(QStringLiteral("nbins"));
        nbins->setButtonSymbols(QAbstractSpinBox::NoButtons);
        nbins->setMaximum(1000);
        nbins->setValue(30);

        formLayout->setWidget(0, QFormLayout::FieldRole, nbins);

        layoutWidget_6 = new QWidget(frame_4);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 50, 351, 34));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        areaWeighted = new QCheckBox(layoutWidget_6);
        areaWeighted->setObjectName(QStringLiteral("areaWeighted"));
        areaWeighted->setChecked(false);

        horizontalLayout_12->addWidget(areaWeighted);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_12 = new QLabel(layoutWidget_6);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_3->addWidget(label_12);

        areaExponent = new QDoubleSpinBox(layoutWidget_6);
        areaExponent->setObjectName(QStringLiteral("areaExponent"));
        areaExponent->setButtonSymbols(QAbstractSpinBox::NoButtons);
        areaExponent->setDecimals(5);
        areaExponent->setValue(0);

        horizontalLayout_3->addWidget(areaExponent);


        horizontalLayout_12->addLayout(horizontalLayout_3);

        layoutWidget_7 = new QWidget(frame_4);
        layoutWidget_7->setObjectName(QStringLiteral("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(10, 90, 351, 34));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        ifUseMinimumToMerge = new QCheckBox(layoutWidget_7);
        ifUseMinimumToMerge->setObjectName(QStringLiteral("ifUseMinimumToMerge"));
        ifUseMinimumToMerge->setChecked(false);

        horizontalLayout_13->addWidget(ifUseMinimumToMerge);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_13 = new QLabel(layoutWidget_7);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_6->addWidget(label_13);

        floor = new QSpinBox(layoutWidget_7);
        floor->setObjectName(QStringLiteral("floor"));
        floor->setButtonSymbols(QAbstractSpinBox::NoButtons);
        floor->setMaximum(10000);
        floor->setValue(30);

        horizontalLayout_6->addWidget(floor);


        horizontalLayout_13->addLayout(horizontalLayout_6);

        ifPaintRandomColor = new QCheckBox(frame_4);
        ifPaintRandomColor->setObjectName(QStringLiteral("ifPaintRandomColor"));
        ifPaintRandomColor->setGeometry(QRect(10, 170, 241, 26));
        ifPaintRandomColor->setChecked(true);
        layoutWidget_10 = new QWidget(frame_4);
        layoutWidget_10->setObjectName(QStringLiteral("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(10, 130, 351, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_10);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget_10);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_4->addWidget(label_9);

        lamda = new QLineEdit(layoutWidget_10);
        lamda->setObjectName(QStringLiteral("lamda"));

        horizontalLayout_4->addWidget(lamda);

        frame_5 = new QFrame(centralWidget);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(10, 10, 371, 91));
        frame_5->setFrameShape(QFrame::WinPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        layoutWidget_2 = new QWidget(frame_5);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 50, 351, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        directoryName = new QLineEdit(layoutWidget_2);
        directoryName->setObjectName(QStringLiteral("directoryName"));
        QPalette palette;
        QBrush brush(QColor(44, 44, 44, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(128, 128, 128, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        directoryName->setPalette(palette);

        horizontalLayout->addWidget(directoryName);

        selectDirectory = new QPushButton(layoutWidget_2);
        selectDirectory->setObjectName(QStringLiteral("selectDirectory"));

        horizontalLayout->addWidget(selectDirectory);

        layoutWidget_3 = new QWidget(frame_5);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 10, 351, 33));
        horizontalLayoutFileName = new QHBoxLayout(layoutWidget_3);
        horizontalLayoutFileName->setSpacing(6);
        horizontalLayoutFileName->setContentsMargins(11, 11, 11, 11);
        horizontalLayoutFileName->setObjectName(QStringLiteral("horizontalLayoutFileName"));
        horizontalLayoutFileName->setContentsMargins(0, 0, 0, 0);
        fileName = new QLineEdit(layoutWidget_3);
        fileName->setObjectName(QStringLiteral("fileName"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        fileName->setPalette(palette1);
        fileName->setFrame(true);

        horizontalLayoutFileName->addWidget(fileName);

        selectFileName = new QPushButton(layoutWidget_3);
        selectFileName->setObjectName(QStringLiteral("selectFileName"));

        horizontalLayoutFileName->addWidget(selectFileName);

        selectFileName->raise();
        fileName->raise();
        frame_6 = new QFrame(centralWidget);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setGeometry(QRect(10, 250, 371, 91));
        frame_6->setFrameShape(QFrame::WinPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        layoutWidget_12 = new QWidget(frame_6);
        layoutWidget_12->setObjectName(QStringLiteral("layoutWidget_12"));
        layoutWidget_12->setGeometry(QRect(10, 10, 351, 74));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_12);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        ifDeleteNoise = new QCheckBox(layoutWidget_12);
        ifDeleteNoise->setObjectName(QStringLiteral("ifDeleteNoise"));
        ifDeleteNoise->setChecked(false);

        horizontalLayout_11->addWidget(ifDeleteNoise);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        numStd_left = new QLabel(layoutWidget_12);
        numStd_left->setObjectName(QStringLiteral("numStd_left"));

        horizontalLayout_10->addWidget(numStd_left);

        nStdLeft = new QDoubleSpinBox(layoutWidget_12);
        nStdLeft->setObjectName(QStringLiteral("nStdLeft"));
        nStdLeft->setDecimals(1);
        nStdLeft->setMinimum(0);
        nStdLeft->setSingleStep(0.1);
        nStdLeft->setValue(2);

        horizontalLayout_10->addWidget(nStdLeft);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(layoutWidget_12);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        nStdRight = new QDoubleSpinBox(layoutWidget_12);
        nStdRight->setObjectName(QStringLiteral("nStdRight"));
        nStdRight->setDecimals(1);
        nStdRight->setSingleStep(0.1);
        nStdRight->setValue(2);

        horizontalLayout_5->addWidget(nStdRight);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_11->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 388, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuTool->addAction(actionHoover_Calculator);
        menuTool->addAction(actionImage_Cropper);
        menuTool->addAction(actionProbability_File_Cropper);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LSBPT", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0));
        actionHoover_Calculator->setText(QApplication::translate("MainWindow", "Hoover Calculator", 0));
        actionImage_Cropper->setText(QApplication::translate("MainWindow", "Image Cropper", 0));
        actionProbability_File_Cropper->setText(QApplication::translate("MainWindow", "Probability File Cropper", 0));
        Go->setText(QApplication::translate("MainWindow", "Go", 0));
        ifAddProbabilityModel->setText(QApplication::translate("MainWindow", "if add probability model", 0));
        label->setText(QApplication::translate("MainWindow", "Probability Model weight", 0));
        label_10->setText(QApplication::translate("MainWindow", "probabilities directory", 0));
        directoryProbabilities->setText(QApplication::translate("MainWindow", "probabilities/directory", 0));
        selectDirectoryProbabilities->setText(QApplication::translate("MainWindow", "...", 0));
        label_21->setText(QApplication::translate("MainWindow", "N. classes:", 0));
        useStdCut->setText(QApplication::translate("MainWindow", "use Std cut", 0));
        label_3->setText(QApplication::translate("MainWindow", "StartX", 0));
        label_4->setText(QApplication::translate("MainWindow", "StartY", 0));
        label_27->setText(QApplication::translate("MainWindow", "nBlocksX", 0));
        label_29->setText(QApplication::translate("MainWindow", "nBlocksY", 0));
        label_6->setText(QApplication::translate("MainWindow", "Width", 0));
        label_5->setText(QApplication::translate("MainWindow", "Height", 0));
        label_7->setText(QApplication::translate("MainWindow", "Num. of bins", 0));
        areaWeighted->setText(QApplication::translate("MainWindow", "Area weighted", 0));
        label_12->setText(QApplication::translate("MainWindow", "Area exponent:", 0));
        ifUseMinimumToMerge->setText(QApplication::translate("MainWindow", "Min. to merge", 0));
        label_13->setText(QApplication::translate("MainWindow", "Min. size to merge:", 0));
        ifPaintRandomColor->setText(QApplication::translate("MainWindow", "Paint with random color", 0));
        label_9->setText(QApplication::translate("MainWindow", "Segmentation Reg", 0));
        lamda->setInputMask(QString());
        lamda->setPlaceholderText(QApplication::translate("MainWindow", "10000", 0));
        directoryName->setText(QApplication::translate("MainWindow", "out/put/directory", 0));
        selectDirectory->setText(QApplication::translate("MainWindow", "...", 0));
        fileName->setInputMask(QString());
        fileName->setText(QApplication::translate("MainWindow", "full/path/image.tif", 0));
        selectFileName->setText(QApplication::translate("MainWindow", "...", 0));
        ifDeleteNoise->setText(QApplication::translate("MainWindow", "Delete noise", 0));
        numStd_left->setText(QApplication::translate("MainWindow", "nStdLeft", 0));
        label_2->setText(QApplication::translate("MainWindow", "nStdRight", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuTool->setTitle(QApplication::translate("MainWindow", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
