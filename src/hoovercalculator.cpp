// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "hoovercalculator.h"
#include "ui_hoovercalculator.h"
#include "QMessageBox"

HooverCalculator::HooverCalculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HooverCalculator)
{
    ui->setupUi(this);
    this->setWindowTitle("Hoover Calculator");
}

HooverCalculator::~HooverCalculator()
{
    delete ui;
}





void HooverCalculator::on_SelectReference_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select reference file"));
    if(fileName.isNull()) {
        QMessageBox ifUseDefaulte;
        //ifUseDefaulte = QMessageBox::question(this, "Question", "Do you want to use defaulte files ?", QMessageBox::Yes | QMessageBox::No);


        switch( false ) {
        case QMessageBox::Yes: exit(1);break;
        case QMessageBox::No: ;
            break;
        default:// should never reach here
            break;
        }
    }
    this->ui->fileName_HooverReference->setText(fileName);
    this->fileName_HooverReference = fileName.toStdString();
}

void HooverCalculator::on_selectTilingSeg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select segmentation file with tiling"));
    this->ui->fileName_HooverTilingSeg->setText(fileName);
    this->fileName_HooverTilingSeg = fileName.toStdString();
}

void HooverCalculator::on_selectHooverComparison_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Set file name to save comparison result"));
    this->ui->fileName_HooverComparison->setText(fileName);
    this->fileName_HooverComparison = fileName.toStdString();
}


void HooverCalculator::on_ComputeHoover_clicked()
{

    float tolerance = this->ui->tolerance->value();
    hooverCompare(this->fileName_HooverReference,
                  this->fileName_HooverTilingSeg,
                  this->fileName_HooverComparison,
                  tolerance);


}

