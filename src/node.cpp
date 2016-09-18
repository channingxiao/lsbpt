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








#include "node.h"

Node::Node()
{
    parent=NULL;
    leftChild=NULL;
    rightChild=NULL;
    //ifBoarder = false;
    minPosition = 100000;
    maxPosition = -1;
    model=0;
    ifLeaf = false;

}
Node::~Node(){
}




void Node::addEdge(Edge *e)
{
    edges.push_back(e);
}

void Node::removeEdge(Edge *e)
{

  //looks for the correct edge in the list and removes it
  //(linear time)
   std::vector<Edge*>::iterator it = edges.begin();
   while (it!=edges.end()){
       if (*it==e){
           edges.erase(it);
           return;
       }
       it++;
   }

}

void Node::removeAllEdges()
{
    edges.clear();
}


std::vector<Edge*>& Node::getEdges()
{
    return edges;
}


void Node::setPosition(Point p)
{
    this->position=p;
}

Point Node::getPosition()
{
    return this->position;
}



void Node::setParent(Node *n)
{
    this->parent=n;
}

void Node::setLeftChild(Node *n)
{
    this->leftChild=n;
}

void Node::setRightChild(Node *n)
{
    this->rightChild=n;
}

Node *Node::getParent()
{
    return parent;
}

Node *Node::getLeftChild()
{
    return leftChild;
}

Node *Node::getRightChild()
{
    return rightChild;
}

Node *Node::getSibling()
{
    Node* parent = getParent();
    if (parent==0)
        return 0;
    if (parent->getLeftChild()==this)
        return parent->getRightChild();
    else
        return parent->getLeftChild();
}

void Node::replaceChild(Node *old, Node *new_)
{
    if (leftChild==old)
        leftChild=new_;
    else
        rightChild=new_;
}

bool Node::isLeaf()
{
    //it is a leaf as soon as it does not have any children
    //return (rightChild==NULL && leftChild==NULL);
    return ifLeaf;

}

bool Node::isChildOf(Node *n)
{

    Node* n_=this;

    while (n_->getParent()!=0){
        if (n_->getParent()==n)
            return true;
        n_=n_->getParent();
    }

    return false;

}

void Node::setModel(regionModel *m)
{
    this->model=m;
    m->setNode(this);
}

regionModel *Node::getModel()
{
    return model;
}

void Node::replaceModel(regionModel *m)
{
    //replaces the model, which includes freeing the
    //memory of the previous one

    if (this->model!=0)
        delete this->model;
    setModel(m);

}



long int Node::getArea() {

   return model->getArea();


}

float Node::getMeanSpectrumAt(unsigned short ind) {
    return model->getMeanSpectrumAt(ind);
}

std::vector<float> Node::getMeanSpectrum()
{
    return model->getMeanSpectrum();
}

std::vector<double> Node::getProbability()
{
    return model->getProbability();
}

int Node::getClassLabel()
{
    vector<double> probabilities = model->getProbability();
    auto biggest = std::max_element( probabilities.begin(), probabilities.end());
    return std::distance( probabilities.begin(), biggest );
}


void Node::releaseNode(){
    // delete all the edges
    std::vector<Edge*>::iterator it = edges.begin();
    while (it!=edges.end()){
        delete *it;
    }
    edges.clear();
    delete this->getModel();
    delete this;

}


void Node::releaseTree(){

    /**
     * @brief Delete all nodes and edges.
     * This method delete the tree recursively. All edges, node, and Models are
     * deleted.
     */

    // delete all the edges
    std::vector<Edge*>::iterator it = edges.begin();
    while ( it!=edges.end() ){
        delete *it;
    }
    edges.clear();

    if(this->isLeaf()) {
        delete this->getModel();
        delete this;
    } else {
        if(this->getLeftChild() != NULL) this->getLeftChild()->releaseTree();
        if(this->getRightChild()!= NULL) this->getRightChild()->releaseTree();
        delete this->getModel();
        delete this;
    }
}







bool Node::nodeComparator_X(Node* e1, Node* e2)
{
    //This function orders the nodes set based on the position x from smallest to greatest
    if( e1->getPosition().x  <   e2->getPosition().x   ) return true;
    else if( e1->getPosition().x == e2->getPosition().x )
        return (e1->getPosition().y < e2->getPosition().y);
    else return false;


}

bool Node::nodeComparator_Y(Node *e1, Node *e2){

    //This function orders the nodes set based on the position y from smallest to greatest
    if(e1->getPosition().y < e2->getPosition().y ) return true;
    else if( e1->getPosition().y == e2->getPosition().y)
        return ( e1->getPosition().x < e2->getPosition().x );
    else return false;
}








std::vector<int> Node::getBoarderIndexX(){
    return this->boarderIndexX;
}

std::vector<int> Node::getBoarderIndexY(){
    return this->boarderIndexY;
}

void Node::setBoarderIndexX( int x ){
    this->boarderIndexX.push_back(x);

}

void Node::setBoarderIndexY( int y ){
    this->boarderIndexY.push_back( y );
}



void Node::setBoarderIndexX( std::vector<int> index ){
    this->boarderIndexX.insert(this->boarderIndexX.end(), index.begin(), index.end());

}

void Node::setBoarderIndexY( std::vector<int> index ){
    this->boarderIndexY.insert(this->boarderIndexY.end(), index.begin(), index.end());
}


