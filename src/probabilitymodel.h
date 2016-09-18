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


#ifndef PROBABILITYMODEL_H
#define PROBABILITYMODEL_H

#include "regionModel.h"
#include <vector>
#include "math.h"
#include <iostream>

using namespace std;

class probabilityModel : public regionModel
{
public:
    probabilityModel();
    probabilityModel(const std::vector<double> &probabilities);
    virtual ~probabilityModel();


    probabilityModel *merge(regionModel* other);


    double getOrder(regionModel* other);

    probabilityModel *clone();



    double computeRegionClassCost(unsigned short class_);
    double computeRegionCost();


    unsigned short getNClasses();


    std::vector<double>& getClassProbabilities();
    void setClassProbability(unsigned short class_, double value);
    void setClassProbabilities(std::vector<double> value);
    double getClassProbability(unsigned short class_);

    std::vector<double> getClassCosts() const;
    void setClassCosts(std::vector<double> value);
    void setClassCostsWithProbability(std::vector<double> probability);

    void setClassCost(unsigned short class_, double value);
    double getClassCost(unsigned short class_);




    double getLowestCost();
    unsigned short getLowestCostClass();

    probabilityModel* getModel();


    std::vector<double> getProbability(); ///return the probability std::vector



    double cutCost(bool useStdCut );

    float getMeanSpectrumAt(unsigned short band){}
    std::vector<float> getMeanSpectrum(){}

    void printHistogram(){}















private:

    std::vector<double> classProbabilities;
    //acumulated cost of every class
    std::vector<double> classCosts;

};

#endif // PROBABILITYMODEL_H
