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





#ifndef HISTOGRAMMODEL_H
#define HISTOGRAMMODEL_H

#include "regionModel.h"
#include "node.h"
#include "statistics.h"
#include <iostream>
#include <vector>
using namespace std;

#include <omp.h>

class histogramModel : public regionModel
{
public:

    histogramModel(unsigned short bands, unsigned short bins);
    histogramModel(const std::vector<float> &spectrum, unsigned nBins, const std::vector<double> &min, const std::vector<double> &max);
    virtual ~histogramModel(){
    }

    double getOrder(regionModel* other);
   // double getOrder(regionModel *other, bool areaWeighted, double areaExponent, double alpha, bool ifUseMinimumToMerge, float floor ){}


    histogramModel*  merge(regionModel* other);
    histogramModel* getModel();

    void setHistogramValue(unsigned short band, unsigned short bin, float p);

    void increaseHistogramValue(unsigned short band, unsigned short bin);
    void increaseHistogramValueBy(unsigned short band, unsigned short bin, float v);

    float getValue(unsigned short band, unsigned short bin);


    const std::vector<float> &getBand(unsigned short b); // get the histogram of band b

    unsigned short getNBands(); // get the number of bands
    unsigned short getNBins();

    void normalizeBand(unsigned short band); // nomalized histograme for band b

    std::vector<float>& getSpectrum();  // return the whole std::vector of mean specture
    std::vector<float>& getStd();

    void setMeanSpectrumAt(unsigned short band, float value);
    void setStd(unsigned short band, float value);
    float getMeanSpectrumAt(unsigned short band);
    std::vector<float> getMeanSpectrum();

    unsigned short getLowestCostClass(){}

    double cutCost( bool useStdCut);

    histogramModel* clone();


    void releaseHistogram();

    unsigned short getNClasses();

    //static float numberRegionsReg;
    void printHistogram();

    std::vector<double> getProbability(){}


protected:

    std::vector< std::vector<float> > histograms;
    std::vector<float> meanSpectrum;
    std::vector<float> std;


    unsigned short nbands;
    unsigned short nbins;




};

#endif // HISTOGRAMMODEL_H
