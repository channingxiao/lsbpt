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



#ifndef IO_H
#define IO_H



#include "gdal.h"
#include "gdal_priv.h"

#include <iostream>
#include <node.h>
#include "compoundmodel.h"
#include <fstream>
#include <cstdlib>  // random number generator
#include <ctime>  // set seed in random number generator

using namespace std;
using namespace cv;

class io
{
public:
    io();





    static void read2Mat(std::vector<Mat> *bands, GDALDataset *poDataset,
                        size_t roiX, size_t roiY, size_t roiW, size_t roiH,
                        bool ifDeleteNoise,
                        std::vector<double> orderMin, std::vector<double> orderMax );




    static void writeNodeToDisk(Node * node, int color[], GDALDataset * poDataset, int globalStartX, int globalStartY);
    static void writeClassMap(Node * node, int classLabel, GDALDataset * poDataset, int globalStartX, int globalStartY);



    static void writeNodeToCSV(Node * node, int label, ofstream &fout);

    static void writeBoarderNodeToCSV(Node * node, int label, ofstream &fout, bool ifAddProbabilityModel);


    static void writeBoarderNodeSetToCSV(std::vector<Node *> nodeSet, ofstream &fout, bool ifAddProbabilityModel);


    static void createEmptyImage(std::string fileName, int width, int height, int nBandCount);

    template<class T>
    static void clip(T *buffer, const std::vector<double> &min, const std::vector<double> &max,
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

              // io::rescale(buffer[k], min(i), max(i),  )
            }
        }

    return;

    }


    template<class T>
    static void rescale(T &thevalue, T min, T max, T rescaleMin, T rescaleMax){
        thevalue = (T)(1.0*(rescaleMax - rescaleMin)/(max-min)*(thevalue-min) + rescaleMin);
    }



    static void bestSegmentation(Node *n, std::vector<Node *> &selectedNodes, double &cost, double lamda, bool useStdCut);



};

#endif // IO_H
