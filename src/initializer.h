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



#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "rag.h"
#include "histogrammodel.h"
#include <QDebug>
#include "compoundmodel.h"
#include <iostream>
#include <fstream>



using namespace std;




class image;


class initializer
{
public:

    static void initializeRag(RAG & rag, std::vector<Node *> &selectedNodeSet);
    static std::vector< std::vector<Node*> > createNodeMatrix( int blockStartX, int blockStartY, int blockSizeW, int blockSizeH,
                                                           int globalStartX, int globalStartY, int globalSizeW, int globalSizeH);



    static void addEdges(std::vector<Node*> NodeSet, RAG &out){
        std::sort(NodeSet.begin(),NodeSet.end(),Node::nodeComparator_X);
        for(size_t i=0; i < NodeSet.size()-1; i++) {
            Node *n1 = NodeSet[i];
            Node *n2 = NodeSet[i+1];
            if(n1->getPosition().x == n2->getPosition().x)
                if(abs(n1->getPosition().y - n2->getPosition().y) ==1) {
                    Edge* e = new Edge(n1,n2);
                    double edgeWeight = n1->getModel()->getOrder(n2->getModel());
                    e->setWeight(edgeWeight);
                    e->setLength(1);
                    n1->addEdge(e);
                    n2->addEdge(e);
                    out.addEdge(e);
                }

        }

        // sort the leaves based on y and x, and add horizotal edges
        std::sort(NodeSet.begin(),NodeSet.end(),Node::nodeComparator_Y);
        for(size_t i=0; i < NodeSet.size()-1; i++) {
            Node *n1 = NodeSet[i];
            Node *n2 = NodeSet[i+1];

            if(n1->getPosition().y == n2->getPosition().y)
                if(abs(n1->getPosition().x - n2->getPosition().x) ==1) {
                    Edge* e = new Edge(n1,n2);
                    double edgeWeight = n1->getModel()->getOrder(n2->getModel());
                    e->setWeight(edgeWeight);
                    e->setLength(1);
                    n1->addEdge(e);
                    n2->addEdge(e);
                    out.addEdge(e);
                }
        }

    }




    //initialize with probability
    template< typename T>
    static RAG multispectralImageToRAG2(std::vector<Mat> images, std::vector< int > blockPosition,
                                        std::vector<std::vector<std::vector<double > > >&probabilites)
    {
        /**
         * @brief Initialize a rag for a tile.
         * @param images A vector of Mat which stores color information for each band
         * @param blockPosition A vector of lenght 2 which stores the index of t
         *        he tile which is going to be process, the first element
         *        represents the index in X direction (horizontal), and the other
         *        represents the index in Y direction (verticle).
         * @param probabilities A 3D vector, the first dimension represents the
         *        cordinate in Y direction, the second dimension represnts the
         *        cordinate in X direction, and the third dimension represnts
         *        the class probabilities of the pixel
         * @return A initialized rag, see RAG.
         */
        int rows = images[0].rows;
        int cols = images[0].cols;

        //create a matrix of empty nodes of the given size
        std::vector< std::vector<Node*> > nodeMatrix = createNodeMatrix2(rows,cols, blockPosition);

        //add compound models in every position
        for (int i = 0; i<rows;i++){
            for (int j = 0; j<cols; j++){
                compoundModel* newModel = new compoundModel();
                nodeMatrix[i][j]->setModel(newModel);
            }
        }

        //add histogram model
        addHistModel<T>(nodeMatrix,images);
        //add probability model
        if(probabilites.size()>0) addProbModel(nodeMatrix,probabilites);
        //add the nodes to the RAG
        RAG out;
        addNodesToRAG(nodeMatrix,out);

        out.nodeMatrix = nodeMatrix;

        out.width = cols;
        out.height = rows;

        //add edges to rag
        connect(out,nodeMatrix);


        return out;

    }




    //initialize with probability
    template< typename T>
    static RAG multispectralImageToRAG(std::vector<Mat> images, std::vector<std::vector<std::vector<double > > >&probabilites,
                                       int blockStartX, int blockStartY, int blockSizeX, int blockSizeY,
                                       int globalStaetX, int globalStartY, int globalsizeX, int globalSizeY,
                                       std::vector<double> orderMin, std::vector<double> orderMax, int nBins)
    {
        /**
         * @brief Initialize a rag for a tile.
         * @param images A vector of Mat which stores color information for each band
         * @param blockPosition A vector of lenght 2 which stores the index of t
         *        he tile which is going to be process, the first element
         *        represents the index in X direction (horizontal), and the other
         *        represents the index in Y direction (verticle).
         * @param probabilities A 3D vector, the first dimension represents the
         *        cordinate in Y direction, the second dimension represnts the
         *        cordinate in X direction, and the third dimension represnts
         *        the class probabilities of the pixel
         * @return A initialized rag, see RAG.
         */
        int rows = images[0].rows;
        int cols = images[0].cols;

        //create a matrix of empty nodes of the given size
        std::vector< std::vector<Node*> > nodeMatrix = createNodeMatrix(blockStartX, blockStartY, blockSizeX, blockSizeY,
                                                              globalStaetX, globalStartY, globalsizeX, globalSizeY);


        //add compound models in every position
        for (int i = 0; i<rows;i++){
            for (int j = 0; j<cols; j++){
                compoundModel* newModel = new compoundModel();
                nodeMatrix[i][j]->setModel(newModel);
            }
        }

        //add histogram model

        addHistModel<T>(nodeMatrix, images, orderMin, orderMax, nBins);
        //add probability model
        if(probabilites.size()>0) addProbModel(nodeMatrix,probabilites);
        //add the nodes to the RAG
        RAG out;
        addNodesToRAG(nodeMatrix,out);

        out.nodeMatrix = nodeMatrix;

        out.width = cols;
        out.height = rows;

        //add edges to rag
        connect(out,nodeMatrix);


        return out;

    }






private:




    static void connect(RAG &out, std::vector< std::vector<Node*> > &nodeMatrix);

    static std::vector< std::vector<Node*> > createNodeMatrix2(int height, int width, std::vector< int > blockPosition);

    static void addNodesToRAG(const std::vector<std::vector<Node *> > &nodeMatrix, RAG& rag);

    static void addProbModel(std::vector< std::vector<Node*> > &nodeMatrix, std::vector<std::vector<std::vector<double > > >&probabilites);

    static void addEmpytHistModel(std::vector< std::vector<Node*> > &nodeMatrix, unsigned short nbands, int nBins);



    template< typename T>
    static void addHistModel(std::vector< std::vector<Node*> > &nodeMatrix, std::vector<Mat> images, int nBins)
    {

        addEmpytHistModel(nodeMatrix,images.size(), nBins);

        //add spectral information to the model for each of the bands
        for (size_t b=0;b<images.size();b++){
            //addHistogramOneBand<T>(b,globalSettings::orderMin[b],globalSettings::orderMax[b],globalSettings::nbins,images[b],nodeMatrix);
        }

        //we now add mean spectrum information

        for (int short b=0; b<images.size();b++){
            addMeanSpectrumInformation<T>(b,images[b],nodeMatrix);
        }



    }

    template< typename T>
    static void addHistModel(std::vector< std::vector<Node*> > &nodeMatrix, std::vector<Mat> images,
                             std::vector<double> orderMin, std::vector<double> orderMax, int nBins)
    {

        addEmpytHistModel(nodeMatrix,images.size(), nBins);
        //add spectral information to the model for each of the bands
        for (int b=0;b<images.size();b++){
            addHistogramOneBand<T>(b,orderMin[b],orderMax[b],nBins,images[b],nodeMatrix);
            addMeanSpectrumInformation<T>(b,images[b],nodeMatrix);
        }


    }


    template< typename T>
    static void addHistogramOneBand(int band, double min, double max, int nbins,
                                    Mat image, std::vector< std::vector<Node*> > &nodeMatrix)
    {

        for (int i=0;i<image.rows;i++){
            for (int j=0;j<image.cols;j++){
                //compute the bin to which it should fall
                unsigned short bin = (image.at<T>(i,j) - min)/((float) 1 + max - min)*nbins; //1 is added to avoid that max == min
                ((compoundModel*) nodeMatrix[i][j]->getModel())->getHistogramModel()->increaseHistogramValue(band,bin);

            }
        }

    }


    template< typename T> static void addMeanSpectrumInformation(unsigned short band, Mat image, std::vector< std::vector<Node*> > &nodeMatrix){

        //initializes mean spectrum information for the whole image in a given band
        for (int i=0;i<image.rows;i++)
            for (int j=0;j<image.cols;j++){

                ((compoundModel*) nodeMatrix[i][j]->getModel())->getHistogramModel()->setMeanSpectrumAt(band,image.at<T>(i,j));


            }

    }



};

#endif // INITIALIZER_H
