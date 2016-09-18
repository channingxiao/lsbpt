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

#ifndef IMAGEBLOCK_H
#define IMAGEBLOCK_H

#include <vector>
#include "rag.h"
#include "io.h"
#include "initializer.h"
#include "gdal_priv.h"
#include "enumerators.h"

using namespace std;


class imageblock
{
public:
    imageblock();
    ~imageblock(){}


    void setSizeX(size_t x);
    size_t getSizeX();
    void setSizeY(size_t y);
    size_t getSizeY();
    void setStartPoint(size_t x, size_t y);
    size_t getStartPointX();
    size_t getStartPointY();
    void setPosition(int blockIndexW,int blockIndexH);
    void setParameters( int indexX, int indexY,
                        GDALDataset * data,
                        int blockSizeX, int blockSizeY,
                        int blockStartX, int blockStartY,
                        int globalSizeX, int globalSizeY,
                        int globalStartX, int globalStartY,
                        IMAGEFORMAT imageFormat,
                        bool ifDeleteNoise,
                        std::vector<double> orderMin, std::vector<double> orderMax,
                        bool ifAddProbabilityModel,
                        int nClasses, int nBins,
                        bool useStdCut,
                        std::string directoryOutput,
                        std::string directoryProbabilities,
                        bool ifPaintRandomColor,std::vector<double> lamda);
    void processing();


     void loadProbabilities();
     void saveToDisk( int level);
     void InitializeRag();
     void createBPT();


       std::vector<Mat> bands;

private:




       IMAGEFORMAT imageFormat;

       std::vector<Node*> selectedSegmentationNodes;
       RAG rag;
       Node* root;
       int nClasses;
       std::string directoryOutput;
       std::string fileNameSegmentation;
       std::string fileNameSegmentationCSV;
       std::string fileNameProbabilities;


       std::vector< int > blockPosition;
       std::vector<std::vector<std::vector<double> > > probabilities;

       void loadBlock();

       GDALDataset * data;
       bool ifDeleteNoise;
       std::vector<double> orderMin;
       std::vector<double> orderMax;


       int globalStartX;
       int globalStartY;
       int globalSizeX;
       int globalSizeY;
       int nBins;

       int SizeX;
       int SizeY;
       int startPointX;
       int startPointY;
       std::vector<double> lamda; // regularization term for segmentation
       bool useStdCut;
       bool ifAddProbabilityModel;
       bool ifPaintRandomColor;







};

#endif // IMAGEBLOCK_H
