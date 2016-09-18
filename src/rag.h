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
Implements a region adjacency graph (RAG) that provides a region merging function
that constructs a Binary Partition Tree
*/


#ifndef RAG_H
#define RAG_H


#include "node.h"
#include <iostream>
#include "edgeheap.h"
#include <algorithm>
#include <iostream>

using namespace std;

#include <QMap>
#include <set>


class RAG
{
public:
    RAG();
    ~RAG();
    void addNode(Node* n);
    void addEdge(Edge* e);

    int getNodeSize();
    int getEdgeSize();




    int width,height;
    std::vector< pair<Node*,Node*> > pixelPairs;
    std::vector< std::vector<Node*> > nodeMatrix;
    QSet<Node*> nodes;

    Node* regionMerging();
    Node* merge(Node* n1, Node* n2);


private:

    EdgeHeap edges;


};


#endif // RAG_H
