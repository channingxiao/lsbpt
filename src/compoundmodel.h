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








#ifndef COMPOUNDMODEL_H
#define COMPOUNDMODEL_H

#include "regionModel.h"
#include "histogrammodel.h"
#include "probabilitymodel.h"


class compoundModel : public regionModel
{
public:
    compoundModel();
    compoundModel( histogramModel * histogramModelTemp, probabilityModel * probabilityModelTemp );
    compoundModel( histogramModel * histogramModelTemp);

    virtual ~compoundModel();

    regionModel* merge(regionModel* other);
    compoundModel* getModel();

    //return the order with respect to other model (a measure of similarity)
    double getOrder(regionModel* other);
  //  double getOrder(regionModel *other, bool areaWeighted, double areaExponent, double alpha, bool ifUseMinimumToMerge, float floor );
    //
    compoundModel* clone();
    double cutCost(bool useStdCut);

    void setNode(Node* n);
    void setHistogramModel(histogramModel* hist_model);
    histogramModel* getHistogramModel();
    float getMeanSpectrumAt(unsigned short band);
    unsigned short getLowestCostClass();

    void printHistogram(){

        hist_model->printHistogram();
    }


    void setProbModel(probabilityModel* prob_model);
    probabilityModel* getProbModel();

    std::vector<double> getProbability();
    std::vector<float> getMeanSpectrum();



    double alpha;
    double lambda;


    static double areaExponent;
    static bool areaWeighted;
    static long floor;
    static bool ifUseMinimumToMerge;
    static double probabilityModelWeight;


private:

    histogramModel* hist_model;
    probabilityModel* prob_model;

};

#endif // COMPOUNDMODEL_H
