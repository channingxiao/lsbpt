/********************************************************************************
** Form generated from reading UI file 'hoovercalculator.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOOVERCALCULATOR_H
#define UI_HOOVERCALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HooverCalculator
{
public:
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *fileName_HooverComparison;
    QPushButton *selectHooverComparison;
    QPushButton *ComputeHoover;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *fileName_HooverReference;
    QPushButton *SelectReference;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *tolerance;
    QLabel *label_9;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *fileName_HooverTilingSeg;
    QPushButton *selectTilingSeg;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *HooverCalculator)
    {
        if (HooverCalculator->objectName().isEmpty())
            HooverCalculator->setObjectName(QStringLiteral("HooverCalculator"));
        HooverCalculator->resize(310, 260);
        layoutWidget_2 = new QWidget(HooverCalculator);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 110, 261, 32));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        fileName_HooverComparison = new QLineEdit(layoutWidget_2);
        fileName_HooverComparison->setObjectName(QStringLiteral("fileName_HooverComparison"));
        QPalette palette;
        QBrush brush(QColor(128, 128, 128, 101));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(128, 128, 128, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        fileName_HooverComparison->setPalette(palette);

        horizontalLayout_8->addWidget(fileName_HooverComparison);

        selectHooverComparison = new QPushButton(layoutWidget_2);
        selectHooverComparison->setObjectName(QStringLiteral("selectHooverComparison"));

        horizontalLayout_8->addWidget(selectHooverComparison);

        ComputeHoover = new QPushButton(HooverCalculator);
        ComputeHoover->setObjectName(QStringLiteral("ComputeHoover"));
        ComputeHoover->setGeometry(QRect(20, 220, 111, 29));
        layoutWidget = new QWidget(HooverCalculator);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(18, 10, 261, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        fileName_HooverReference = new QLineEdit(layoutWidget);
        fileName_HooverReference->setObjectName(QStringLiteral("fileName_HooverReference"));
        QPalette palette1;
        QBrush brush2(QColor(128, 128, 128, 98));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        fileName_HooverReference->setPalette(palette1);
        fileName_HooverReference->setFrame(true);
        fileName_HooverReference->setEchoMode(QLineEdit::Normal);

        horizontalLayout_2->addWidget(fileName_HooverReference);

        SelectReference = new QPushButton(layoutWidget);
        SelectReference->setObjectName(QStringLiteral("SelectReference"));

        horizontalLayout_2->addWidget(SelectReference);

        layoutWidget_4 = new QWidget(HooverCalculator);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 160, 141, 32));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        tolerance = new QDoubleSpinBox(layoutWidget_4);
        tolerance->setObjectName(QStringLiteral("tolerance"));
        tolerance->setMinimum(0.51);
        tolerance->setMaximum(1);
        tolerance->setSingleStep(0.1);
        tolerance->setValue(1);

        horizontalLayout_5->addWidget(tolerance);

        label_9 = new QLabel(layoutWidget_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_5->addWidget(label_9);

        layoutWidget_3 = new QWidget(HooverCalculator);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 60, 261, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        fileName_HooverTilingSeg = new QLineEdit(layoutWidget_3);
        fileName_HooverTilingSeg->setObjectName(QStringLiteral("fileName_HooverTilingSeg"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        fileName_HooverTilingSeg->setPalette(palette2);

        horizontalLayout_4->addWidget(fileName_HooverTilingSeg);

        selectTilingSeg = new QPushButton(layoutWidget_3);
        selectTilingSeg->setObjectName(QStringLiteral("selectTilingSeg"));

        horizontalLayout_4->addWidget(selectTilingSeg);

        buttonBox = new QDialogButtonBox(HooverCalculator);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(210, 200, 61, 71));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(true);
        buttonBox->raise();
        layoutWidget_2->raise();
        ComputeHoover->raise();
        layoutWidget->raise();
        layoutWidget_4->raise();
        layoutWidget_3->raise();
        buttonBox->raise();

        retranslateUi(HooverCalculator);
        QObject::connect(buttonBox, SIGNAL(accepted()), HooverCalculator, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), HooverCalculator, SLOT(reject()));

        QMetaObject::connectSlotsByName(HooverCalculator);
    } // setupUi

    void retranslateUi(QDialog *HooverCalculator)
    {
        HooverCalculator->setWindowTitle(QApplication::translate("HooverCalculator", "Dialog", 0));
        fileName_HooverComparison->setText(QApplication::translate("HooverCalculator", "Save result", 0));
        selectHooverComparison->setText(QApplication::translate("HooverCalculator", "...", 0));
        ComputeHoover->setText(QApplication::translate("HooverCalculator", "Compute", 0));
        fileName_HooverReference->setText(QApplication::translate("HooverCalculator", "reference file", 0));
        fileName_HooverReference->setPlaceholderText(QString());
        SelectReference->setText(QApplication::translate("HooverCalculator", "...", 0));
        label_9->setText(QApplication::translate("HooverCalculator", "Tolerance", 0));
        fileName_HooverTilingSeg->setText(QApplication::translate("HooverCalculator", "segmentation with tiling", 0));
        selectTilingSeg->setText(QApplication::translate("HooverCalculator", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class HooverCalculator: public Ui_HooverCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOOVERCALCULATOR_H
