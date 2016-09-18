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








#include "rag.h"
#include "QDebug"

RAG::RAG()
{
}
RAG::~RAG()
{

}

void RAG::addNode(Node *n)
{
    nodes.insert(n);
}



int RAG::getNodeSize(){
    return nodes.size();
}

int RAG::getEdgeSize(){
    return edges.size();
}



void RAG::addEdge(Edge *e)
{
    edges.push_back(e);
}









//========================================================================================================================================================================================================


Node* RAG::regionMerging()
{
    /**
     * @brief Create a BPT
     * @return A Node, which is the root of the tree.
     * This method takes a initialized rag, merges two regions each time till
     * one Node left.
     *
     */


    edges.heapify();

    Node* merged=NULL;


    // if there is only one node
    if(edges.size() == 0 ) {
        merged = *nodes.begin();
    }
    while (edges.size()>0){

        // Take first edge, which has the smallest edge weight
        Edge* leastWeighted = edges.getFront();
        edges.removeFront();

        //remove it from associated nodes
        Node* n1 = leastWeighted->getNode1();
        Node* n2 = leastWeighted->getNode2();
        n1->removeEdge(leastWeighted);
        n2->removeEdge(leastWeighted);

        //merge nodes, after merging, the edges will still in order
        merged= merge(n1,n2);


        //free memory
        delete leastWeighted;


    }

    //return lastly merged node, ie root of the tree
    return merged;

}






Node* RAG::merge(Node* n1, Node* n2)
{
    /**
     * @brief Merge to Nodes.
     * @param n1 First node.
     * @param n2 Second node.
     * @return A Node object, which the the parent node of n1 and n2.
     *
     * This method merges two node into a parent node. It tracks the borders,
     * merges the regionModel update edges, and sort the heap after each update.
     */


    //create new node
    Node* new_ = new Node();

    //update parent/child relation
    new_->setLeftChild(n1);
    new_->setRightChild(n2);
    n1->setParent(new_);
    n2->setParent(new_);

    //tracking the borders
    std::vector<int> boarderIndexXN1 = n1->getBoarderIndexX();
    std::vector<int> boarderIndexXN2 = n2->getBoarderIndexX();
    boarderIndexXN1.insert(boarderIndexXN1.end(), boarderIndexXN2.begin(),boarderIndexXN2.end());
    std::sort(boarderIndexXN1.begin(), boarderIndexXN1.end());
    auto lastX = std::unique(boarderIndexXN1.begin(), boarderIndexXN1.end());
    boarderIndexXN1.erase( lastX, boarderIndexXN1.end());
    new_->setBoarderIndexX( boarderIndexXN1 );

    std::vector<int> boarderIndexYN1 = n1->getBoarderIndexY();
    std::vector<int> boarderIndexYN2 = n2->getBoarderIndexY();
    boarderIndexYN1.insert( boarderIndexYN1.begin(), boarderIndexYN2.begin(),boarderIndexYN2.end() );
    std::sort( boarderIndexYN1.begin(), boarderIndexYN1.end() );
    auto lastY = std::unique( boarderIndexYN1.begin(), boarderIndexYN1.end() );
    boarderIndexYN1.erase( lastY, boarderIndexYN1.end() );
    new_ ->setBoarderIndexY( boarderIndexYN1 );


    //merge models:
    regionModel* mergedModel = n1->getModel()->merge(n2->getModel());
    new_->setModel(mergedModel);

    //At this point we might want to delete the model associated to
    //the merged nodes if we do not want to keep this information:
    //delete n1->getModel();
    //delete n2->getModel();


    //update edges ===============

    //get edges that connectes to each of the nodes
    std::vector<Edge*> edges1 = n1->getEdges();
    std::vector<Edge*> edges2 = n2->getEdges();

    //switch edges to the newly created node and update edge weights
    for (size_t i=0;i<edges1.size();i++){
        edges1[i]->replace(n1,new_);
        //set weight of edge based on order
        edges1[i]->setWeight(edges1[i]->getNode1()->getModel()->getOrder(edges1[i]->getNode2()->getModel()));
        //update heap with Heapsort algorithm
        edges.update(edges1[i]);
    }
    for (size_t i=0;i<edges2.size();i++){
        edges2[i]->replace(n2,new_);
        //set weight of edge based on order
        edges2[i]->setWeight(edges2[i]->getNode1()->getModel()->getOrder(edges2[i]->getNode2()->getModel()));

        //update heap with Heapsort algorithm
        edges.update(edges2[i]);
    }


    // if a node is connected to n1 and n2, then there would be a duplicated edge
    // in new_, we need to delete the duplicated edges

    //add edges to newedges as soon as they are not duplicated,
    //which is assessed by using the hash table newedges_
    std::vector<Edge*> newedges;
    QMap< QPair<Node*,Node*>, Edge* > newedges_;

    //for the edges coming from one of the nodes...
    for (size_t i=0;i<edges1.size();i++){

        //add them to the set to keep track of possible duplicates of the edges of the other node
        newedges_.insert(QPair<Node*,Node*>(edges1[i]->getNode1(),edges1[i]->getNode2()),edges1[i]);

        //add to new edges
        newedges.push_back(edges1[i]);
    }


    for (size_t i=0;i<edges2.size();i++){
        //is this edge a duplicate from one coming from node 1?
        QMap< QPair<Node*,Node*>, Edge* >::iterator it1;
        QMap< QPair<Node*,Node*>, Edge* >::iterator it2;
        it1=newedges_.find(QPair<Node*,Node*>(edges2[i]->getNode1(),edges2[i]->getNode2()));
        it2=newedges_.find(QPair<Node*,Node*>(edges2[i]->getNode2(),edges2[i]->getNode1()));


        if (it1==newedges_.end() && it2==newedges_.end() ){

            //not duplicated, can add it safely
            newedges.push_back(edges2[i]);

        } else {

            //it is duplicated, delete it and update the nodes
            Edge* duplicated = edges2[i];

            /// efficient perimeter computation:
            ////////////
            //to whom is it duplicated?
            Edge* equivalent;
            if (it1!=newedges_.end())
                equivalent = it1.value();
            else
                equivalent = it2.value();
            equivalent->setLength(equivalent->getLength()+duplicated->getLength());
            ////////////

            duplicated->getNode1()->removeEdge(duplicated);
            duplicated->getNode2()->removeEdge(duplicated);

            //remove from heap
            edges.remove(duplicated);

            delete duplicated;
        }

    }



    //add new edges to node
    for (size_t i=0;i<newedges.size();i++){
        new_->addEdge(newedges[i]);
    }



// =============== It is better to remove this part ? =======================
    //remove all edges incident to the nodes since now they
    //point to other new node


    n1->removeAllEdges();
    n2->removeAllEdges();

    //uncomment to remove from set of nodes of current RAG if we want to keep track of them
    nodes.remove(n1);
    nodes.remove(n2);
    //and add the new node to rag
    nodes.insert(new_);




    return new_;


}



