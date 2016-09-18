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

#include "imagecropper.h"
#include "ui_imagecropper.h"
#include <sstream> // for parsing bandMap

ImageCropper::ImageCropper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageCropper)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Cropper");
}

ImageCropper::~ImageCropper()
{
    delete ui;
}




void ImageCropper::on_cut_clicked()
{
    //parse bandMap, if input is 0, them select all bands
    std::vector<int> bandMap;
    if( !this->ui->bandMap->text().isEmpty() ){
        std::string bandMapString = this->ui->bandMap->text().toStdString();
        stringstream bandMapStream(bandMapString);
        int i;
        while( bandMapStream >> i) {
            bandMap.push_back( i );
            if( bandMapStream.peek() == ',' | bandMapStream.peek() == ' ')
                bandMapStream.ignore();
        }

    }

    this->imageCutSizeX = this->ui->width->value();
    this->imageCutSizeY = this->ui->height->value();
    this->startPointX = this->ui->startX->value();
    this->startPointY = this->ui->startY->value();
    this->nBlocksX = this->ui->nBlocksX->value();
    this->nBlocksY = this->ui->nBlocksY->value();
    this->ifDeleteNoise = this->ui->ifDeleteNoise->isChecked();
    this->nStdLeft = this->ui->nStdLeft->value();
    this->nStdRight = this->ui->nStdRight->value();
    this->ifRescale = this->ui->ifRescale->isChecked();
    this->scaledMin = this->ui->scaledMin->value();
    this->scaledMax = this->ui->scaledMax->value();

    //qDebug() << this->scaledMin <<" " << this->scaledMax << endl;

    this->blockSizeCalculator_evenSplite();
    this->blockStartPointCalculator_evenSplite();

    this->cropImage(bandMap);

    QMessageBox::information(NULL,"Done", "The job has been cropped !");


}





void ImageCropper::on_selectFileName_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select file name"));
    if(fileName.isNull()) {
        QMessageBox fileNotSelected;
        fileNotSelected.QDialog::setWindowTitle("Image file not selected !");
        fileNotSelected.setText("Click Ok to select image file, Cacell to exit.");
        fileNotSelected.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        fileNotSelected.setDefaultButton(QMessageBox::Ok);
        int ret = fileNotSelected.exec();
        switch(ret) {
        case QMessageBox::Cancel: exit(1);break;
        case QMessageBox::Ok: ImageCropper::on_selectFileName_clicked(); // go back to select file
            break;
        default:// should never reach here
            break;
        }
    }
    this->ui->fileName->setText(fileName); // show the file path in the GUI
    this->imageFileName = fileName.toStdString();

    linkedFile();

    this->imageSizeX = data->GetRasterXSize();
    this->imageSizeY = data->GetRasterYSize();

    this->ui->fullImageWidth->setText( QString::number(this->imageSizeX) );
    this->ui->fullImageHeight->setText( QString::number(this->imageSizeY) );
}




void ImageCropper::on_selectDirectory_clicked()
{
    QFileDialog selectDirectoryDialog;
    selectDirectoryDialog.setFileMode(QFileDialog::Directory);
    selectDirectoryDialog.setOption(QFileDialog::ShowDirsOnly);
    selectDirectoryDialog.setDirectory(QDir::home());
    QString directoryName = selectDirectoryDialog.getExistingDirectory(this, tr("Open Directory"));
    this->ui->directoryName->setText(directoryName);
    this->directoryName = directoryName.toStdString();
}







void ImageCropper::linkedFile()
{
    GDALAllRegister();
    this->data =  (GDALDataset *) GDALOpen( this->imageFileName.c_str(), GA_ReadOnly );
    if( this->data== NULL ) QMessageBox::critical(NULL,"File linking fail !", "Image can't open with GDAL.");
    //globalSettings::image_format = globalSettings::data->GetRasterBand(1)->GetRasterDataType();
    GetGDALDriverManager()->AutoSkipDrivers();
    qDebug()<<"Image linked" <<endl;
}





void ImageCropper::blockSizeCalculator_evenSplite()
{  // this function evenly splite the image

    blockSizeW.clear();
    blockSizeH.clear();

    int eachSizeX = imageCutSizeX/nBlocksX;
    int eachSizeY = imageCutSizeY/nBlocksY;

    for(int i= 0;i< nBlocksX-1; i++ )
        blockSizeW.push_back(eachSizeX);
    blockSizeW.push_back(imageCutSizeX - eachSizeX*(nBlocksX-1));

    for(int j=0; j<nBlocksY-1; j++)
        blockSizeH.push_back(eachSizeY);
    blockSizeH.push_back(imageCutSizeY- eachSizeY*(nBlocksY-1));

    return;
}



void ImageCropper::blockStartPointCalculator_evenSplite()
{

    blocksStartPointX.clear();
    blocksStartPointY.clear();

    blocksStartPointX.push_back(startPointX);
    blocksStartPointY.push_back(startPointY);

    for(int i= 1; i < nBlocksX; i++)
        blocksStartPointX.push_back(blocksStartPointX[i-1] + blockSizeW[i-1]);

    for(int j=1; j < nBlocksY; j++)
        blocksStartPointY.push_back(blocksStartPointY[j-1]+ blockSizeH[j-1]);

    return;
}



void ImageCropper::cropImage(std::vector<int> &bandIndex)
{

    // The band index start from 1


    GDALAllRegister();
    GDALDataset *poDataset =  (GDALDataset *) GDALOpen( this->imageFileName.c_str(), GA_ReadOnly ); // open file
    //int BandCount = poDataset->GetRasterCount();

    const char *pszFormat = "GTiff";
    GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName( pszFormat );
    char **papszOptions = NULL;
    papszOptions = CSLSetNameValue( papszOptions, "TILED", "NO" );
    papszOptions = CSLSetNameValue( papszOptions,"BIGTIFF", "IF_NEEDED" );


    std::vector<double> rasterMin;
    std::vector<double> rasterMax;
    std::vector<double> rasterMean;
    std::vector<double> rasterStdDev;
    // for preprocessing

    std::vector<double> orderMin;
    std::vector<double> orderMax;

    //if the bandIndex is empty, do for all bands
    if(bandIndex.size() == 0) {
        for(int i=1; i < poDataset->GetRasterCount()+1; i++)
            bandIndex.push_back(i);

    }



    for(size_t i=0; i < bandIndex.size(); i++) {

        GDALRasterBand * rasterBand = poDataset->GetRasterBand( bandIndex[i] );
        int bApproxOK = 0;
        int bForce = 1;
        double min=0;
        double max=0;
        double mean=0;
        double stdDev=0;
        rasterBand->GetStatistics(bApproxOK, bForce, &min, &max, &mean, &stdDev);
        rasterMin.push_back(min);
        rasterMax.push_back(max);
        rasterMean.push_back(mean);
        rasterStdDev.push_back(stdDev);

        orderMin.push_back( rasterMean[i] - nStdLeft*rasterStdDev[i]  );
        orderMax.push_back( rasterMean[i] + nStdRight*rasterStdDev[i] );

    }

    /*

    orderMin[0] = 0;
    orderMin[1] = 0;
    orderMin[2] = 0;
    orderMax[0] = 769;
    orderMax[1] = 710;
    orderMax[2] = 706;


    */



    for(int i = 0; i < this->nBlocksX; i++)
        for(int j = 0; j < this->nBlocksY; j++) {

            std::string fileName_out = this->directoryName + "/" + to_string(i/10) + to_string( i%10 ) +to_string(j/10) + to_string(j%10) + ".tif";

           int width = this->blockSizeW[i];
           int height = this->blockSizeH[j];
           int startX = this->blocksStartPointX[i];
           int startY = this->blocksStartPointY[j];
           int BandCount = bandIndex.size();

            GDALDataset *data_out;
            data_out= poDriver->Create(fileName_out.c_str(),width,height,BandCount,GDT_Byte,papszOptions);

            double *buffer= new double [width*height*BandCount];
            int *panBandMap = new int[BandCount];
            for(int k=0; k < BandCount; k++) panBandMap[k] = bandIndex[k];
            poDataset->RasterIO( GF_Read, startX, startY,width,height,
                                 buffer,width,height,GDT_Float64,BandCount,panBandMap,0,0,0);

           if( this->ifDeleteNoise ) {
               clip<double>(buffer, orderMin, orderMax,
                               BandCount, width*height);
           }

           // data_out->RasterIO( GF_Write, 0, 0,width,height,
                     //           buffer,width,height,GDT_Float64,BandCount,0,0,0,0 );

           uint8_t *buffer_int = new uint8_t[width*height*BandCount];
           for(int k=0; k < width*height*BandCount; k++) buffer_int[k] = static_cast<uint8_t>(buffer[k]);

            data_out->RasterIO( GF_Write, 0, 0,width,height,
                               buffer_int,width,height,GDT_Byte,BandCount,0,0,0,0 );

            delete[] buffer;
            delete[] buffer_int;
            delete data_out;

        }

    delete poDataset;
    return;

}

void ImageCropper::on_crop_clicked()
{





}


