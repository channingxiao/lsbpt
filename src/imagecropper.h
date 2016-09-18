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

#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "gdal.h"
#include "gdal_priv.h"
#include <iostream>

using namespace std;
namespace Ui {
class ImageCropper;
}

class ImageCropper : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageCropper(QWidget *parent = 0);
    ~ImageCropper();

    void linkedFile();
        void blockSizeCalculator_evenSplite();
        void blockStartPointCalculator_evenSplite();
        void cropImage(std::vector<int> &bandIndex);


        template<class T>
        void rescale(T &thevalue, T min, T max, double rescaleMin, double rescaleMax){
            thevalue = (T)(1.0*(rescaleMax - rescaleMin)/(max-min)*(thevalue-min) + rescaleMin);
        }

        template<class T>
        void clip(T *buffer, const std::vector<double> &min, const std::vector<double> &max,
                          int numBand, size_t numPixel)
        {
            //check the input
            if(min.size() != max.size()) {
                exit(1);
            }else if( min.size() != numBand ){
                exit(1);
            }

            for(int i=0; i<numBand; i++) {
                for(int k = numPixel*i; k< numPixel*(i+1); k++){

                    if( buffer[k] > max[i]) {
                        buffer[k]= max[i];
                    } else if( buffer[k] <min[i]) {
                        buffer[k] = min[i];
                    }

                    if( ifRescale ) {
                        rescale<T> (buffer[k], min[i], max[i], scaledMin , scaledMax );
                    }

                }
            }

        return;

        }







    private slots:

        void on_selectDirectory_clicked();
        void on_selectFileName_clicked();


        void on_cut_clicked();


        void on_crop_clicked();


private:
           Ui::ImageCropper *ui;




           std::string imageFileName; ///< The file name of the image which is going to be cut.
           std::string directoryName; ///< The directory which the cut image will be saved.


           unsigned imageSizeX; ///< The width of full image.
           unsigned imageSizeY; ///< The height of full image.

           unsigned startPointX; ///< The X cordinate of up left corner pixel starting to crop.
           unsigned startPointY; ///< The Y cordinate of up left corner pixel starting to crop.
           unsigned imageCutSizeX; ///< The width of the part of image which will be cut.
           unsigned imageCutSizeY; ///< The height of the part of image which will be cut.

           unsigned nBlocksX; ///< Number of blocks the image is going to be cut in X direction.
           unsigned nBlocksY; ///< Number of blocks the image is going to be cut in Y direction.

           std::vector<int> blockSizeW;
           std::vector<int> blockSizeH;

           std::vector<int> blocksStartPointX;
           std::vector<int> blocksStartPointY;

           GDALDataset *data;

           bool ifDeleteNoise;
           double nStdLeft; // number of standard deviation
           double nStdRight;

           bool ifRescale;
           double scaledMin;
           double scaledMax;


};

#endif // IMAGECROPPER_H
