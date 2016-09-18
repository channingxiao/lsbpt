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






#include "initializer.h"







std::vector< std::vector<Node*> > initializer::createNodeMatrix( int blockStartX, int blockStartY,
                                                       int blockSizeX, int blockSizeY,
                                                       int globalStartX, int globalStartY,
                                                       int globalSizeX, int globalSizeY)
{

    std::vector< std::vector<Node*> > nodeMatrix (blockSizeY,std::vector<Node*>(blockSizeX));

    for (int i=0;i<blockSizeY;i++)
        for (int j=0;j<blockSizeX;j++){
            Node* n = new Node();

            // tracking region type
            if(i == 0 && blockStartY != globalStartY) {
                n->setBoarderIndexY( blockStartY );
            }

            if(i == blockSizeY-1 && blockStartY+blockSizeY != globalStartY + globalSizeY) {
                n->setBoarderIndexY( blockStartY + blockSizeY -1 );
            }

            if(j == 0 && blockStartX != globalStartX) {
                n->setBoarderIndexX( blockStartX );
            }
            if(j == blockSizeX-1 && blockStartX+blockSizeX != globalStartX + globalSizeX) {
                n->setBoarderIndexX( blockStartX + blockSizeX -1);
            }

            // Add global offset
            n->setPosition(Point(blockStartX + j,blockStartY+i));
            n->ifLeaf = true;
            nodeMatrix[i][j]=n;
        }
    return nodeMatrix;
    std::cout <<"Node matrix has been created" << endl;
}






// ============================================================================================================================================================================================



// ======================================================= Add models to each node, histgrame, (I put the probability and shapemodel in the end ===============================================

/*
void initializer::addEmpytHistModel(std::vector<std::vector<Node *> > &nodeMatrix, unsigned short nbands)
{

    size_t height = nodeMatrix.size();
    size_t width = nodeMatrix[0].size();

    for (size_t i = 0; i<height;i++)
        for (size_t j = 0; j<width; j++){

            int nbins = globalSettings::nbins;
            histogramModel* hist_model = new histogramModel(nbands,nbins);
            compoundModel* model = (compoundModel*) nodeMatrix[i][j]->getModel();
            model->setHistogramModel(hist_model);

        }

}

*/


void initializer::addEmpytHistModel(std::vector<std::vector<Node *> > &nodeMatrix, unsigned short nbands, int nBins)
{

    size_t height = nodeMatrix.size();
    size_t width = nodeMatrix[0].size();

    for (size_t i = 0; i<height;i++)
        for (size_t j = 0; j<width; j++){
            histogramModel* hist_model = new histogramModel(nbands,nBins);
            compoundModel* model = (compoundModel*) nodeMatrix[i][j]->getModel();
            model->setHistogramModel(hist_model);
        }

}

 // ==========================================================================================================================================================================================




// ============================================================== Add nodes to RAG ==========================================================================================================

void initializer::addNodesToRAG(const std::vector<std::vector<Node *> > &nodeMatrix, RAG &rag)
{
    size_t height = nodeMatrix.size();
    size_t width = nodeMatrix[0].size();

    for (size_t i = 0; i<height;i++)
        for (size_t j = 0; j<width; j++){
            rag.addNode(nodeMatrix[i][j]);
        }
}

// ============================================================== Connect the nodes ===========================================================================================================

void initializer::connect(RAG &out,std::vector< std::vector<Node*> > &nodeMatrix ){


    std::vector< pair<Node*,Node*> > pixelPairs;


    size_t height = nodeMatrix.size();
    size_t width = nodeMatrix[0].size();

    //connect vertically with next row
    for (size_t i=0;i<height-1;i++)
        for (size_t j=0;j<width;j++){
            Node* n1 = nodeMatrix[i][j];
            Node* n2 = nodeMatrix[i+1][j];

            Edge* e = new Edge(n1,n2);

            n1->addEdge(e);
            n2->addEdge(e);

            double edgeWeight = n1->getModel()->getOrder(n2->getModel());

            e->setWeight(edgeWeight);

            e->setLength(1);

            out.addEdge(e);

            pixelPairs.push_back(pair<Node*,Node*>(n1,n2));

        }


    //connect horizontally with next column
    for (size_t i=0;i<height;i++)
        for (size_t j=0;j<width-1;j++){
            Node* n1 = nodeMatrix[i][j];
            Node* n2 = nodeMatrix[i][j+1];

            Edge* e = new Edge(n1,n2);

            n1->addEdge(e);
            n2->addEdge(e);

            double edgeWeight = n1->getModel()->getOrder(n2->getModel());


            e->setWeight(edgeWeight);

            e->setLength(1);

            out.addEdge(e);

            pixelPairs.push_back(pair<Node*,Node*>(n1,n2));



        }

    out.pixelPairs = pixelPairs;

}




void initializer::addProbModel(std::vector<std::vector<Node *> > &nodeMatrix, std::vector<std::vector<std::vector<double> > > &probabilites)
{
    size_t rows = nodeMatrix.size();
    size_t cols = nodeMatrix[0].size();

    //add a new empty prob model
    for (size_t i = 0; i<rows;i++)
        for (size_t j = 0; j<cols; j++){
            ((compoundModel*) nodeMatrix[i][j]->getModel())->setProbModel(new probabilityModel());
        }

    //set probability vector of every point
    for (size_t i=0;i<rows;i++)
        for (size_t j=0;j<cols;j++){

            probabilityModel* model = ((compoundModel*) nodeMatrix[i][j]->getModel())->getProbModel();
            std::vector<double> probs = probabilites[i][j];
            for (size_t c=0;c<probs.size();c++)
                model->setClassProbability(c,probs[c]);
        }

    //set class cost of every point
    for (size_t i=0;i<rows;i++){
        for (size_t j=0;j<cols;j++){
            probabilityModel* model = ((compoundModel*) nodeMatrix[i][j]->getModel())->getProbModel();
            std::vector<double> probs = probabilites[i][j];
            for (size_t c=0;c<probs.size();c++) {
                model->setClassCost(c,-log(probs[c]));
            }
        }
    }


}



void initializer::initializeRag(RAG & rag, std::vector<Node *> &selectedNodeSet){
    for(size_t i=0; i < selectedNodeSet.size(); i++) {
        rag.addNode( selectedNodeSet[i] );
    }
    addEdges(selectedNodeSet,rag);
    return;

}









