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






#include <iostream>
#include "edgeheap.h"
#include "node.h"

EdgeHeap::EdgeHeap()
{
}

EdgeHeap::~EdgeHeap()
{
}

void EdgeHeap::push_back(Edge *e)
{
    heap.push_back(e);
}



void EdgeHeap::heapify()
{

    //we heapify by using c++ linear time algorithm and
    make_heap(heap.begin(),heap.end(),edgeComparator);

    //set its current heap position to every edge
    for(size_t i=0;i<heap.size();i++)
        heap[i]->setHeapIndex(i);

}


bool EdgeHeap::edgeComparator(Edge* e1, Edge* e2)
{
    //we're ordering from greatest to lowest similarity, so it uses
    //return (e1->getWeight()  >   e2->getWeight());



    if( e1->getWeight()  >   e2->getWeight() ){
        return true;
    } else if(  e1->getWeight()  <   e2->getWeight() ) {
        return false;
    } else {

        //int depth11 = e1->getNode1()->getDepth();
        //int depth12 = e1->getNode2()->getDepth();
        int depth11 = e1->getNode1()->getArea();
        int depth12 = e1->getNode2()->getArea();

        int depthSmaller1 = depth11 < depth12 ? depth11 : depth12;
        int depthLarger1 = depth11 > depth12 ? depth11 : depth12;

        //int depth21 = e2->getNode1()->getDepth();
        //int depth22 = e2->getNode2() ->getDepth();
        int depth21 = e2->getNode1()->getArea();
        int depth22 = e2->getNode2() ->getArea();


        int depthSmaller2 = depth21 < depth22 ? depth21 : depth22;
        int depthLarger2 = depth21 > depth22 ? depth21 : depth22;

        if( depthLarger1 > depthLarger2 ) {
            return true;
        } else if( depthLarger1 < depthLarger2 ) {
            return false;
        } else {

            if( depthSmaller1 > depthSmaller2 ) {
                return true;
            } else if ( depthSmaller1 < depthSmaller2 ) {
                return false;
            } else {

                // compare the position

                // find smaller one in each edge
                Point smaller1, larger1, smaller2, larger2;
                if( e1->getNode1()->getPosition().x > e1->getNode2()->getPosition().x ){
                    smaller1 = e1->getNode2()->getPosition();
                    larger1 = e1->getNode1()->getPosition();
                } else if( e1->getNode1()->getPosition().x < e1->getNode1()->getPosition().x ){
                    smaller1 = e1->getNode1()->getPosition();
                    larger1 = e1->getNode2()->getPosition();
                } else {
                    if( e1->getNode1()->getPosition().y > e1->getNode2()->getPosition().y ) {
                        smaller1 = e1->getNode2()->getPosition();
                        larger1 = e1->getNode1()->getPosition();
                    }else{
                        smaller1 = e1->getNode1()->getPosition();
                        larger1 = e1->getNode2()->getPosition();
                    }
                }

                if( e2->getNode1()->getPosition().x > e2->getNode2()->getPosition().x ){
                    smaller2 = e2->getNode2()->getPosition();
                    larger2 = e2->getNode1()->getPosition();
                } else if( e2->getNode1()->getPosition().x < e2->getNode1()->getPosition().x ){
                    smaller2 = e2->getNode1()->getPosition();
                    larger2 = e2->getNode2()->getPosition();
                } else {
                    if( e2->getNode1()->getPosition().y > e2->getNode2()->getPosition().y ) {
                        smaller2 = e2->getNode2()->getPosition();
                        larger2 = e2->getNode1()->getPosition();
                    }else{
                        smaller2 = e2->getNode1()->getPosition();
                        larger2 = e2->getNode2()->getPosition();
                    }
                }


                //compare smaller pair
                if( smaller1.x > smaller2.x ){
                    return true;
                } else if( smaller1.x < smaller2.x ){
                    return false;
                } else {
                    if( smaller1.y > smaller2.y ){
                        return true;
                    } else if( smaller1.y < smaller2.y ){
                        return false;
                    } else {
                        // The two positions in the first pair are the same, compare the larger pair
                        if( larger1.x > larger2.x ){
                            return true;
                        } else if( larger1.x < larger2.x ){
                            return false;
                        } else {
                            if( larger1.y > larger2.y ){
                                return true;
                            } else {
                                return false;
                            }
                        }
                    }
                }




            }
        }
    }







/*

        // compare the position
    if( e1->getWeight()  >   e2->getWeight() ){
        return true;
    } else if(  e1->getWeight()  <   e2->getWeight() ) {
        return false;
    } else {

        // find smaller one in each edge
        Point smaller1, larger1, smaller2, larger2;
        if( e1->getNode1()->getPosition().x > e1->getNode2()->getPosition().x ){
            smaller1 = e1->getNode2()->getPosition();
            larger1 = e1->getNode1()->getPosition();
        } else if( e1->getNode1()->getPosition().x < e1->getNode1()->getPosition().x ){
            smaller1 = e1->getNode1()->getPosition();
            larger1 = e1->getNode2()->getPosition();
        } else {
            if( e1->getNode1()->getPosition().y > e1->getNode2()->getPosition().y ) {
                smaller1 = e1->getNode2()->getPosition();
                larger1 = e1->getNode1()->getPosition();
            }else{
                smaller1 = e1->getNode1()->getPosition();
                larger1 = e1->getNode2()->getPosition();
            }
        }

        if( e2->getNode1()->getPosition().x > e2->getNode2()->getPosition().x ){
            smaller2 = e2->getNode2()->getPosition();
            larger2 = e2->getNode1()->getPosition();
        } else if( e2->getNode1()->getPosition().x < e2->getNode1()->getPosition().x ){
            smaller2 = e2->getNode1()->getPosition();
            larger2 = e2->getNode2()->getPosition();
        } else {
            if( e2->getNode1()->getPosition().y > e2->getNode2()->getPosition().y ) {
                smaller2 = e2->getNode2()->getPosition();
                larger2 = e2->getNode1()->getPosition();
            }else{
                smaller2 = e2->getNode1()->getPosition();
                larger2 = e2->getNode2()->getPosition();
            }
        }


        //compare smaller pair
        if( smaller1.x > smaller2.x ){
            return true;
        } else if( smaller1.x < smaller2.x ){
            return false;
        } else {
            if( smaller1.y > smaller2.y ){
                return true;
            } else if( smaller1.y < smaller2.y ){
                return false;
            } else {
                // The two positions in the first pair are the same, compare the larger pair
                if( larger1.x > larger2.x ){
                    return true;
                } else if( larger1.x < larger2.x ){
                    return false;
                } else {
                    if( larger1.y > larger2.y ){
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
    }



*/



}



void EdgeHeap::insert(Edge *e)
{
    //put it add the end of the heap...
    heap.push_back(e);
    //...and push it up (which returns its final position)
    long int index = heapifyUp(heap.size() - 1);
    //update its index in the heap
    heap[index]->setHeapIndex(index);
}

Edge *EdgeHeap::getFront()
{
    return heap[0];
}


Edge *EdgeHeap::getHeap(int ind){
    return heap[ind];
}



void EdgeHeap::removeFront()
{
    removeAt(0);
}

void EdgeHeap::removeAt(long int pos)
{




    //Replace by the element at the end of the heap...
    heap[pos] = heap.back();

    //...and update its position
    heap[pos]->setHeapIndex(pos);

    //Now remove the last element
    heap.pop_back();


    //find out parent's position
    unsigned long int parent = (float) floor( ((float)pos-1) / 2.0 );
    //And heapify from the position which was updated

    if (pos>0 && edgeComparator(heap[parent],heap[pos])){
        unsigned long index = heapifyUp(pos);
        //update its index in the heap
        heap[index]->setHeapIndex(index);


    } else {
        heapifyDown(pos);
    }




}

void EdgeHeap::clearAll()
{
    for (int i=0;i<heap.size();i++)
        delete heap.at(i);
    heap.clear();
}

 long EdgeHeap::size()
{
     return heap.size();
 }

 void EdgeHeap::randomShuffle()
 {
     random_shuffle(heap.begin(),heap.end());
     //heapify();
 }

 Edge *EdgeHeap::getAt(long pos)
 {
     return heap[pos];
 }

 void EdgeHeap::updateAt(long pos)
 {

     //find out parent's position
     unsigned long int parent = (float) floor( ((float)pos-1) / 2.0 );

     //is the current element greater than it's parent?
     if (pos>0 && edgeComparator(heap[parent],heap[pos])){
         unsigned long index = heapifyUp(pos);
         //update its index in the heap
         heap[index]->setHeapIndex(index);
     } else {
         heapifyDown(pos);
     }



 }


 void EdgeHeap::remove(Edge *e)
 {

//#pragma omp critical (heap)
    {

     removeAt(e->getHeapIndex());

     }
 }

 void EdgeHeap::update(Edge *e)
 {
//#pragma omp critical (heap)
    {

     updateAt(e->getHeapIndex());

     }
 }

 bool EdgeHeap::isHeap()
 {


     //is heap?
     bool h = true;

     for (size_t i=0;i<heap.size();i++){

         size_t l = 2*i+1;
         size_t r = 2*i+2;

         if (l >= heap.size())
         {
             continue;
         }

         if (r >= heap.size()){

             if (edgeComparator(heap[i],heap[l])){

                 h = false;
                 break;
             }

             continue;
         }


         if (edgeComparator(heap[i],heap[l]) || edgeComparator(heap[i],heap[r])){

             h=false;
             break;

         }

     }

     return h;

 }

 unsigned long EdgeHeap::heapifyUp( unsigned long int pos)
{
    bool done = false;
    while (!done)
    {
        //check bounds
        if ( !( pos >= 1 && pos < heap.size() ) )
        {
            return pos;
        }

        //find out parent's position
        unsigned long int parent = (float) floor( ((float)pos-1) / 2.0 );

        //is the current element greater than it's parent?
        if ( edgeComparator(heap[parent],heap[pos]) )
        {
            //swap it up and continue with the parent's position:

            //update the indices
            heap[pos]->setHeapIndex(parent);
            heap[parent]->setHeapIndex(pos);

            //swap
            std::swap( heap[pos], heap[parent] );

            //continue with parent
            pos = parent;
            continue;
        }
        done = true;
    }
    return pos;
}

void EdgeHeap::heapifyDown( long int pos)
{
    bool done = false;
    while (!done)
    {
        unsigned long int leftChildIndex = 2*pos + 1;
        unsigned long int rightChildIndex = 2*pos + 2;
        if (leftChildIndex >= heap.size())
        {

            // there is no left child, so we're at a leaf, done
            done = true;
            continue;
        }


        if (rightChildIndex >= heap.size()){

            //there is no right child, it has only left subtree

            if (edgeComparator(heap[pos],heap[leftChildIndex])){
                //if the left child is lower, swap

                // keep indexes updated
                heap[pos]->setHeapIndex(leftChildIndex);
                heap[leftChildIndex]->setHeapIndex(pos);

                // swap
                std::swap(heap[pos], heap[leftChildIndex]);


            }

            done = true; // i can assure it's over even if it was swapped (it would be a leaf)
            continue;


        }


        //if it is lower than any of its children...

        if (edgeComparator(heap[pos],heap[leftChildIndex])
                || edgeComparator(heap[pos],heap[rightChildIndex])){

            //if the one on the right is the greater
            if (edgeComparator(heap[leftChildIndex],heap[rightChildIndex])){

                //now swap with the one on the right...

                // keep indexes updated
                heap[pos]->setHeapIndex(rightChildIndex);
                heap[rightChildIndex]->setHeapIndex(pos);

                // swap
                std::swap(heap[pos], heap[rightChildIndex]);

                //and go on on the right hand side...
                pos = rightChildIndex;
                continue;

            } else {  // the one on the left is the greater
                //now swap with the one on the left...

                // keep indexes updated
                heap[pos]->setHeapIndex(leftChildIndex);
                heap[leftChildIndex]->setHeapIndex(pos);

                // swap
                std::swap(heap[pos], heap[leftChildIndex]);

                //and go on on the right hand side...
                pos = leftChildIndex;
                continue;

            }

        }


        done= true;

    }
}
