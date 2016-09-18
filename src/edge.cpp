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







#include "edge.h"
#include "node.h"
Edge::Edge(Node *node1, Node *node2)
{
    this->node1=node1;
    this->node2=node2;
}

void Edge::setWeight(double w)
{
    this->weight=w;
}

double Edge::getWeight()
{
    return weight;
}

Node *Edge::getNode1()
{
    return node1;
}

Node *Edge::getNode2()
{
    return node2;
}

void Edge::setNode1(Node *n)
{
    this->node1=n;
}

void Edge::setNode2(Node *n)
{
    this->node2=n;
}

Node *Edge::traverse(Node *origin){
//returns the other node after traversing the edge
//departing from origin

    if (origin==node1)
        return node2;
    return node1;
}

void Edge::replace(Node *old, Node *new_){
//finds out which of the two nodes is the old one and replaces
//it by the new one

    if (old==node1)
        node1=new_;
    else
        node2=new_;
}

void Edge::setHeapIndex(unsigned long i){
    this->heapIndex=i;
}

unsigned long Edge::getHeapIndex(){
    return heapIndex;
}

bool Edge::equals(Edge *other){
    //edges are defined equal when the nodes to which they point
    //are equal, whichever their order

    if (node1==other->getNode1() && node2==other->getNode2())
        return true;
    if (node1==other->getNode2() && node2==other->getNode1())
        return true;
    return false;

}

void Edge::setLength(unsigned int l)
{
    this->length=l;
}

unsigned int Edge::getLength()
{
    return length;
}

Edge *Edge::clone()
{
    Edge* newEdge = new Edge(this->node1,this->node2);
    newEdge->setWeight(this->getWeight());
    newEdge->setLength(this->getLength());
    newEdge->setHeapIndex(this->getHeapIndex());
    return newEdge;
}



bool Edge::isForward() const
{
    return forward;
}

void Edge::setForward(bool value)
{
    forward = value;
}



