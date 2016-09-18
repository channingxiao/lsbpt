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








/*
Represents a node in a RAG, with a list of pointers to its associated edges.
The model used to represent regions is independent of this class and is
accessed via a pointer to an object of the abstract class Model.
*/



#ifndef NODE_H
#define NODE_H


#include <vector>
using namespace std;

#include <QSet>
#include "gdal.h"
#include "gdal_priv.h"
#include <opencv/cv.h> //for painting regions
using namespace cv;

#include "regionModel.h"
#include "edge.h"





class io;

class Node
{
public:
    Node();
    ~Node();



    void addEdge(Edge* e);
    void removeEdge(Edge* e);
    void removeAllEdges();

    std::vector<Edge*>& getEdges();

    void setParent(Node* n);
    void setLeftChild(Node* n);
    void setRightChild(Node* n);
    Node* getParent();
    Node* getLeftChild();
    Node* getRightChild();

    Node* getSibling();

    void replaceChild(Node* old,Node* new_);

    bool isLeaf();

    bool isChildOf(Node* n);

    void setModel(regionModel* m);
    regionModel* getModel();

    void replaceModel(regionModel* m);


    void setPosition(Point p);
    Point getPosition();


    long int getArea();

    float getMeanSpectrumAt(unsigned short ind);
    std::vector<float> getMeanSpectrum();
    std::vector<double> getProbability();
    int getClassLabel();



    void releaseNode();
    void releaseTree();


    static bool nodeComparator_X(Node* e1, Node* e2);
    static bool nodeComparator_Y(Node* e1, Node* e2);





    std::vector<int> getBoarderIndexX();
    std::vector<int> getBoarderIndexY();
    void setBoarderIndexX( int x );
    void setBoarderIndexX( std::vector<int> index );
    void setBoarderIndexY( int y );
    void setBoarderIndexY( std::vector<int> index );



    bool ifLeaf;
    int minPosition;
    int maxPosition ;
private:
    Node* parent;
    Node* leftChild;
    Node* rightChild;

    std::vector<Edge*> edges;

    regionModel* model;

    Point position;


    std::vector<std::vector<int>> boarderIndex;

    std::vector<int> boarderIndexX;
    std::vector<int> boarderIndexY;

};

#endif // NODE_H
