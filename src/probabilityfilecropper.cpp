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

#include "probabilityfilecropper.h"
#include "ui_probabilityfilecropper.h"
#include "QDialog"
#include "QFileDialog"
#include "QDebug"
#include "fstream"

ProbabilityFileCropper::ProbabilityFileCropper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProbabilityFileCropper)
{
    ui->setupUi(this);
}

ProbabilityFileCropper::~ProbabilityFileCropper()
{
    delete ui;
}

void ProbabilityFileCropper::on_selectProbabiltyFile_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("Select file name"));
   this->ui->probabilityFileName->setText(fileName);
   this->probabilityFileName = fileName.toStdString();

}

void ProbabilityFileCropper::on_selectDirectory_clicked()
{
    QFileDialog selectDirectoryDialog;
    selectDirectoryDialog.setFileMode(QFileDialog::Directory);
    selectDirectoryDialog.setOption(QFileDialog::ShowDirsOnly);
    selectDirectoryDialog.setDirectory(QDir::home());
    QString directoryName = selectDirectoryDialog.getExistingDirectory(this, tr("Open Directory"));

    if(! directoryName.isEmpty()){
        this->ui->directoryToSaveFile->setText(directoryName);
        this->directoryName = directoryName.toStdString();

    }
}


void ProbabilityFileCropper::on_cut_clicked()
{
    this->imageWidth = this->ui->imageWidth->value();
    this->imageHeight = this->ui->imageHeight->value();
    this->numClasses = this->ui->numClasses->value();

    this->width = this->ui->width->value();
    this->height = this->ui->height->value();
    this->startX = this->ui->startX->value();
    this->startY = this->ui->startY->value();

    this->numBlocksX = this->ui->numBlocksX->value();
    this->numBlocksY = this->ui->numBlocksY->value();


    int n_items = imageWidth*imageHeight*numClasses;

    std::vector<double> probData(n_items);
    std::ifstream dataFile;

    std::cout << "filename is :" << probabilityFileName << endl;

    dataFile.open(this->probabilityFileName.c_str(), std::ios_base::in | std::ios_base::binary); //
    if(!dataFile.is_open()) {
        qDebug() << "Probability file not open.";
        exit(1);
    }
    dataFile.read(reinterpret_cast<char*>(&probData[0]), n_items*sizeof(double));
    dataFile.close();


    std::vector<std::vector<std::vector<double> > > probabilities(imageWidth,std::vector< std::vector <double>  >(imageHeight, std::vector<double>(numClasses)) );
    for (size_t i=0;i<imageWidth;i++){
        for (size_t j=0;j<imageHeight;j++){
            for (size_t p=0;p<numClasses;p++){
                    probabilities[i][j][p] = probData[j*imageWidth*numClasses + i*numClasses + p];
            }
        }
    }

    dataFile.close();


    std::vector<double> probsToFile(width*height*numClasses);
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            for (int p=0;p<numClasses;p++){
                 probsToFile[j*width*numClasses + i*numClasses + p] = probabilities[startX + i ][startY + j][p];
            }
        }
    }

    std::string fileNameOut;
    if( ! this->directoryName.empty() ) {
        fileNameOut = probabilityFileName+"Cut.dat";
    } else {
        fileNameOut = probabilityFileName + "Cut.dat";
    }
    ofstream data_file;
    data_file.open(fileNameOut.c_str(), ios_base::out | ios_base::binary);
    data_file.write(reinterpret_cast<char*>(&probsToFile[0]),probsToFile.size()*sizeof(double));
    data_file.close();

    std::cout << fileNameOut << endl;

    qDebug() << "Probability file seperated !" << endl;

}
