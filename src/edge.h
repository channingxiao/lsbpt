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
This class represents a RAG's edge, with pointers to the so-called
node1 and node2, the nodes adjacent to the edge. Every edge has a weight
and it can be self-conscious about its position in a heap structure to allow
random deletions.
*/


#ifndef EDGE_H
#define EDGE_H


class Node;

class Edge
{
public:
    //an edge must be constructed from two nodes
    Edge(Node* node1, Node* node2);

    //associated weight
    void setWeight(double w);
    double getWeight();

    //associated endpoints
    Node* getNode1();
    Node* getNode2();

    void setNode1(Node* n);
    void setNode2(Node* n);

    //we can define if it is a forward/backward edge
    bool isForward() const;
    void setForward(bool value);

    //get the other node, given one of them
    Node* traverse(Node* origin);

    //replace an endpoint by another one
    void replace(Node* old, Node* new_);

    //it can know its position in a heap structure
    void setHeapIndex(unsigned long int i);
    unsigned long int getHeapIndex();

    //compare edges in terms of endpoints
    bool equals(Edge* other);

    void setLength(unsigned int l);
    unsigned int getLength();

    //clone an edge
    Edge* clone();




private:

    Node* node1;
    Node* node2;

    double weight;

    unsigned long int heapIndex;

    unsigned int length;

    bool forward;

};

#endif // EDGE_H
