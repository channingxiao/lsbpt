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

#include "probabilitymodel.h"

probabilityModel::probabilityModel()
{
    this->setArea(1);

}

probabilityModel::probabilityModel(const std::vector<double> &probabilities){

    this->classProbabilities = probabilities;

    // set class cost
    for (size_t c=0;c<probabilities.size();c++) {
        this->setClassCost(c,-log(probabilities[c]));
    }

    this->setArea(1);

}



probabilityModel::~probabilityModel()
{

}

probabilityModel *probabilityModel::merge(regionModel *other)
{
    //std::cout << " call merge probability model." << std::endl;
    probabilityModel* merged = new probabilityModel();

    probabilityModel* other_ = (probabilityModel*) other;

    //merge class probabilities
    unsigned long N1 = this->getArea();
    unsigned long N2 = other->getArea();
    merged->setArea(N1+N2);

    // merge probability
    for (int short c=0; c<this->getNClasses(); c++){
        float f = N1/((float)(N1+N2))* classProbabilities[c] + N2/((float)(N1+N2))* other_->getClassProbability(c);
        merged->setClassProbability(c,f);

        // merge class costs
      //  double addition =  classCosts[c] + other_->getClassCost(c);
     //   merged->setClassCost(c,addition);
    }


    //merge class costs
    for (int c=0; c< classCosts.size() ;c++){
        double addition =  classCosts[c] + other_->getClassCost(c);
        merged->setClassCost(c,addition);
    }


    return merged;

}

std::vector<double> probabilityModel::getProbability(){

   // std::vector<double> temp = classProbabilities;
    return this->classProbabilities;
}









 probabilityModel* probabilityModel::getModel(){
     return this;
 }


double probabilityModel::getOrder(regionModel *other)
{


    probabilityModel* other_ = (probabilityModel*) other;


    float probSameClass = 0;
    for (size_t i=0;i<classProbabilities.size();i++){
        probSameClass+= this->getClassProbability(i)*other_->getClassProbability(i);
    }

    double cost_diff_class;
    cost_diff_class=-log(probSameClass);


    return cost_diff_class;

}

probabilityModel *probabilityModel::clone()
{

    probabilityModel* cloned = new probabilityModel();

    cloned->setClassCosts(this->classCosts);

    cloned->setClassProbabilities(this->classProbabilities);

    cloned->setArea(this->area);


    return cloned;

}

double probabilityModel::computeRegionClassCost(unsigned short class_)
{

    return getClassCost(class_);


}

double probabilityModel::computeRegionCost()
{


    //not defined

    return 0;

}

unsigned short probabilityModel::getNClasses()
{
    return classProbabilities.size();
}

std::vector<double> &probabilityModel::getClassProbabilities()
{
    return classProbabilities;
}

void probabilityModel::setClassProbability(unsigned short class_, double value)
{
    if (class_>=classProbabilities.size())
        classProbabilities.resize(class_+1);

    classProbabilities[class_]=value;
}

void probabilityModel::setClassProbabilities(std::vector<double> value)
{
    this->classProbabilities=value;
}

double probabilityModel::getClassProbability(unsigned short class_)
{
    return classProbabilities[class_];
}

double probabilityModel::getLowestCost()
{
    double lowest = classCosts[0];
    //acumulate class costs
    for (int short c=1;c<classCosts.size();c++){
        if (classCosts[c]<lowest){
            lowest=classCosts[c];
        }
    }
    return lowest;
}

unsigned short probabilityModel::getLowestCostClass()
{
    double lowest = classCosts[0];
    unsigned short class_ = 0;
    //acumulate class costs
    for (int short c=1;c<classCosts.size();c++){
        if (classCosts[c]<lowest){
            lowest=classCosts[c];
            class_=c;
        }
    }
    return class_;
}


std::vector<double> probabilityModel::getClassCosts() const
{
    return classCosts;
}


void probabilityModel::setClassCosts(std::vector<double> value)
{
    classCosts = value;
}

void probabilityModel::setClassCostsWithProbability(std::vector<double> probability){

    for (size_t c=0;c<probability.size();c++) this->setClassCost(c,-log(probability[c]));

}



void probabilityModel::setClassCost(unsigned short class_, double value)
{
    if (class_>=classCosts.size())
        classCosts.resize(class_+1);

    classCosts[class_]=value;

}

double probabilityModel::getClassCost(unsigned short class_)
{
    return classCosts[class_];
}


double probabilityModel::cutCost(bool useStdCut ){

    if( useStdCut ) return 0;
    double lowest = classCosts[0];
    //acumulate class costs
    for (int short c=1;c<classCosts.size();c++){
        if (classCosts[c]<lowest){
            lowest=classCosts[c];
        }
    }
    return lowest;
}
