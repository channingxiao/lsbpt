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
This class represents a heap of edges with the particularity that we allow to remove
nodes at random position. To achieve this every edge should be self-conscious of its position
in the heap, a property which maintained when the structure is modified
*/



#ifndef EDGEHEAP_H
#define EDGEHEAP_H


#include <vector>
#include "edge.h"
#include "math.h" //to use floor function
#include <algorithm> //to use c++'s heapify function
using namespace std;


class EdgeHeap
{
public:
    EdgeHeap();
    ~EdgeHeap();

    //push back enters an edge in the queue without
    //satisfying the heap property. The linear heapify must
    //be called next.
    void push_back(Edge* e);
    void heapify();

    static bool edgeComparator(Edge* e1, Edge* e2);

    //insert maintaining heap property
    void insert(Edge* e);

    //get first element
    Edge* getFront();

    Edge* getHeap(int ind); // this is for debuging only

    //remove first element
    void removeFront();

    //remove arbitrary element
    void remove(Edge* e);

    //clear all elements
    void clearAll();

    //return size
    long int size();

    //randomly shuffle and reheapify. This makes sense
    //to alter the order of elements that compare to equal
    void randomShuffle();

    //obtain arbitrary element
    Edge* getAt(long int pos);

    //update the position of an edge in the heap,
    //if we know it's been modified. It locally moves the
    //element instead of removing and reinserting
    void update(Edge* e);

    bool isHeap();



private:
    std::vector<Edge*> heap;

    unsigned long int heapifyUp(unsigned long pos);
    void heapifyDown( long  int pos);

    void updateAt(long int pos);
    void removeAt(long int pos);
};

#endif // EDGEHEAP_H
