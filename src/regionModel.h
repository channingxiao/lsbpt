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
Represents an abstract node with its elementary functionality for
the region merging algorithm.
*/


#ifndef MODEL_H
#define MODEL_H

#include <vector>
using namespace std;

class Node;

class regionModel
{
public:

    virtual ~regionModel(){}
    virtual regionModel* merge(regionModel* other)=0;
    virtual regionModel* getModel()=0;


    //return the order with respect to other model (a measure of similarity)
    virtual double getOrder(regionModel* other)=0;
 //   virtual double getOrder(regionModel *other, bool areaWeighted, double areaExponent, double alpha, bool ifUseMinimumToMerge, float floor )=0;

    //virtual std::vector<float>& getSpectrum();
    virtual float getMeanSpectrumAt(unsigned short band) = 0;
    virtual unsigned short getLowestCostClass() = 0;


    virtual regionModel* clone()=0;
    virtual double cutCost(bool useStdCut) = 0;


    virtual void setNode(Node* n);
    Node* getNode();
    void setArea(unsigned long a);

    unsigned long getArea();

    virtual void printHistogram()=0;

    virtual std::vector<double> getProbability()=0;
    virtual std::vector<float> getMeanSpectrum()=0;
     bool useStdCut ;

protected:

    Node* node;
    unsigned long area;

};

#endif // MODEL_H
