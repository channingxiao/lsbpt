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

#ifndef IMAGE_H
#define IMAGE_H

#include "gdal.h"
#include "gdal_priv.h"
#include "imageblock.h"
#include "io.h"
#include <string> // to_string()
#include "compoundmodel.h"
#include "algorithm"
#include "rag.h"
#include "workingboundary.h"
#include "enumerators.h"

using namespace std;


class image
{
public:
    image(){}
    ~image(){}

    void linkFile();

    void processing();
    void ProcessTiles();
    int ComputeCircle( int totalTiles );
    void ProcessBoundaryX();
    void ProcessBoundaryY();
    void PrintTileInfo(int indexX, int indexY);
    void findImageFormat();

    void mergeBlockX(const std::vector< WorkingBoundary > &workingBoundaries ,
                     const std::vector<int> &blockPosition1,
                     const std::vector<int> &blockPosition2);

    void mergeBlockY(const std::vector< WorkingBoundary > &workingBoundaries,
                     const std::vector<int> &blockPosition1,
                     const std::vector<int> &blockPosition2);

    void selectBoarderSegments( std::vector<Node *> *selected,
                                const std::vector< WorkingBoundary > & workingBoundaries,
                                std::string boarderFileName);

    void saveToDisk(const std::vector< Node *> &selectedSegmentationNodes,
                    const std::vector< WorkingBoundary > &workingBoundaries, int level);

    void saveToDisk(const std::vector< Node *> &selectedSegmentationNodes, int row, int level);


    void setGlobalSettings(int imageWidth, int imageHeight,
                           int startPointX, int startPointY,
                           int nBlocksX, int nBlocksY,
                           bool ifDeleteNoise, double nStdLeft, double nStdRight,
                           bool ifUseMinimumToMerge, int floor,
                           int nbins,
                           bool areaWeighted, double areaExponent,
                           bool useStdCut,
                           bool ifAddProbabilityModel, double probabilityModelWeight, int nClasses,
                           std::vector<double> lamda,
                           bool ifPaintRandomColor);

    void print_ImageInfo();
    void blockSizeCalculator_evenSplite();
    void blockStartPointCalculator_evenSplite();


    void createEmptyImage(std::string fileName);

    void createEmptyCSV(std::string fileName);

    void SetStatistics();


    std::string fileNameImage;
    std::string directoryOutput;
    std::string directoryProbabilities;



private:



    GDALDataset * data;
    std::string logFileName;
    IMAGEFORMAT imageFormat;

    std::string fileNameSegmentation;
    std::string fileNameSegmentationCSV;


    int rasterWidth;
    int rasterHeight;
    int rasterBandCount;
    std::vector<double> rasterMin;
    std::vector<double> rasterMax;
    std::vector<double> rasterMean;
    std::vector<double> rasterStdDev;
    // for preprocessing
    bool ifDeleteNoise;
    double nStdLeft; // number of standard deviation
    double nStdRight;
    std::vector<double> orderMin;
    std::vector<double> orderMax;


    int imageWidth;    // the width of the image we are going to process  ( number of pixes)
    int imageHeight;  // the height of the image part we are going to process
    int nBands;   // the number of bands in the image
    int nBlocksX; // the number of blocks per row in image tiling
    int nBlocksY; // the number of blocks per colum in image tiling
    int startPointX; // the start point of the part of image we are going to process
    int startPointY;

    double areaExponent; // area weight in expenatial
    bool areaWeighted;  // if we use area weighting
    int floor;   // minimum size to merge
    bool ifUseMinimumToMerge;
    std::vector<double> lamda; // regularization term for segmentation
    int nbins;  // number of bins in histogram model

    bool ifAddProbabilityModel;
    double probabilityModelWeight;
    int nClasses;
    bool useStdCut;

    std::vector<int> blockSizeW;
    std::vector<int> blockSizeH;

    std::vector<size_t> blocksStartPointX;
    std::vector<size_t> blocksStartPointY;


    bool ifPaintRandomColor;






};


#endif // IMAGE_H
