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

#include "mainwindow.h"
#include <hoovermetrics.h>
#include <hoovercalculator.h>
#include <imagecropper.h>
#include <probabilityfilecropper.h>
#include "algorithm"

#include <stdio.h>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectFileName_clicked()
{
    /** Selecte the image file to process
     *
     *
     */

    QString fileName = QFileDialog::getOpenFileName(this,tr("Select file name"));
    if(fileName.isNull()) {
        QMessageBox::critical(this, tr("Error!"), tr("Image file is not selected!"));
    } else {
        this->ui->fileName->setText(fileName); // show the file path in the GUI
        this->myimage.fileNameImage = fileName.toStdString();
    }

}


void MainWindow::on_selectDirectory_clicked()
{
    /**
     * @brief Select directory where all results will be stored
     *
     */

    QFileDialog selectDirectoryDialog;
    selectDirectoryDialog.setFileMode(QFileDialog::Directory);
    selectDirectoryDialog.setOption(QFileDialog::ShowDirsOnly);
    selectDirectoryDialog.setDirectory(QDir::home());
    QString directoryName = selectDirectoryDialog.getExistingDirectory(this, tr("Open Directory"));

    if(! directoryName.isEmpty() ){
        this->ui->directoryName->setText(directoryName);
        this->myimage.directoryOutput = directoryName.toStdString();
    } else {
        directoryName = QDir::homePath();
        this->ui->directoryName->setText(directoryName);
        this->myimage.directoryOutput = directoryName.toStdString();
        cout << directoryName.toStdString() << endl;
        QMessageBox::warning(this, tr("Warming!"),  tr("Directory is set to your home!"));
    }

}



void MainWindow::on_selectDirectoryProbabilities_clicked()
{
    /**
     * @brief Select the direchtory where the probability files are stored
     */

    QFileDialog selectDirectoryDialog;
    selectDirectoryDialog.setFileMode(QFileDialog::Directory);
    selectDirectoryDialog.setOption(QFileDialog::ShowDirsOnly);
    selectDirectoryDialog.setDirectory(QDir::current());
    QString directoryName = selectDirectoryDialog.getExistingDirectory(this, tr("Open Directory"));

    if( ! directoryName.isEmpty() ){
        this->ui->directoryProbabilities->setText(directoryName);
        this->myimage.directoryProbabilities = directoryName.toStdString();
    } else {
        QMessageBox::warning(this, tr("Warming!"),  tr("Directory is not selected!"));
    }

}




void MainWindow::on_Go_clicked()
{
    /**
     * @brief Start the processing
     */






    //parse segmentation regularization term
    std::vector<double> lamda;
    if( !this->ui->lamda->text().isEmpty() ){
        std::string bandMapString = this->ui->lamda->text().toStdString();
        stringstream bandMapStream(bandMapString);
        double i;
        while( bandMapStream >> i) {
            lamda.push_back( i );
            if( (bandMapStream.peek() == ';') | (bandMapStream.peek() == ' '))
                bandMapStream.ignore();
        }
    }
    std::sort(lamda.begin(), lamda.end(), std::greater<double>() );



    myimage.setGlobalSettings( this->ui->roiw->value(), this->ui->roih->value(),
                               this->ui->roix->value(), this->ui->roiy->value(),
                               this->ui->numBlocksX->value(), this->ui->numBlocksY->value(),
                               this->ui->ifDeleteNoise->isChecked(), this->ui->nStdLeft->value(),
                               this->ui->nStdRight->value(),
                               this->ui->ifUseMinimumToMerge->isChecked(), this->ui->floor->value(),
                               this->ui->nbins->value(),
                               this->ui->areaWeighted->isChecked(), this->ui->areaExponent->value(),
                               this->ui->useStdCut->isChecked(),
                               this->ui->ifAddProbabilityModel->isChecked(),
                               this->ui->probabilityModelWeight->value(),this->ui->nClasses->value(),
                               lamda, this->ui->ifPaintRandomColor->isChecked());


    myimage.print_ImageInfo();
    double time_all = (double)getTickCount();

    myimage.processing();

    time_all = ((double)getTickCount() - time_all)/getTickFrequency();
    std::cout << "The toal running time is " << time_all << " seconds" << endl;
    QMessageBox::information(NULL,"Done", "The job has been done !");

}





void MainWindow::on_actionHoover_Calculator_triggered()
{
    /**
     * @brief Launch a hoover calculator interface
     */

    HooverCalculator * hoover = new HooverCalculator(this);
    hoover->show();

}

void MainWindow::on_actionImage_Cropper_triggered()
{
    /**
     * @brief Launch a image cropper interface
     */

    ImageCropper * imageCropperWindow = new ImageCropper(this);
    imageCropperWindow->show();

}

void MainWindow::on_actionProbability_File_Cropper_triggered()
{
    /**
     * @brief Launch a probability file cropper interface
     */
    ProbabilityFileCropper * probabilityFileCropperWindow = new ProbabilityFileCropper(this);
    probabilityFileCropperWindow->show();
}


















