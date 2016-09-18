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








#include "histogrammodel.h"
#include "math.h"
#include "QDebug"



histogramModel::histogramModel(unsigned short bands, unsigned short bins) : histograms(bands, std::vector<float>(bins,0)), meanSpectrum(bands), std(bands,0)
{
    this->setArea(1);
    this->nbands=bands;
    this->nbins=bins;

}

histogramModel::histogramModel(const std::vector<float> &spectrum, unsigned nBins, const std::vector<double> &min, const std::vector<double> &max){
    this->setArea(1);
    this->nbands=spectrum.size();
    this->nbins=nBins;
    this->meanSpectrum = spectrum;
    this->histograms.resize(nbands);
    for(int i=0; i<nbands; i++){
        this->histograms[i].resize(nbins);
    }
    for(size_t i=0; i<spectrum.size(); i++){
        unsigned short bin = ( spectrum[i] - min[i] )/( 1 + max[i] - min[i])*nbins;
        increaseHistogramValue(i,bin);
    }
    std.resize(nbands);

}








double histogramModel::getOrder(regionModel *other)
{

    histogramModel* other_ = (histogramModel*)other;
    float acum=0;


    //#pragma omp parallel for ordered reduction(+:acum)
    //#pragma omp parallel for reduction(+:acum)
    for (int short b=0;b<nbands;b++){

        std::vector< float > otherHist = other_->getBand(b);
        float emd;
        emd = statistics::EMD(histograms[b],otherHist);
        //#pragma omp ordered
        acum+=emd;

    }

    float meanVal = acum/((float)nbands);
    return meanVal;

}




histogramModel *histogramModel::getModel(){
    return this;
}


histogramModel *histogramModel::merge(regionModel *other)
{
    histogramModel* other_ = (histogramModel*) other;
    histogramModel* merged_ = new histogramModel(nbands,nbins);

    unsigned long N1 = this->getArea();
    unsigned long N2 = other->getArea();
    merged_->setArea(N1+N2);


    //#pragma omp parallel for
    for (int short b = 0; b < this->nbands; b++){ //for every band

        //merge histograms:
        for (int i = 0; i<this->nbins ;i++){ //for every bin
            merged_->setHistogramValue(b,i,(N1*histograms[b][i] + N2*other_->getValue(b,i))/((float) N1+N2));
        }

        //merge mean spectra:
        float f = N1/((float)(N1+N2))* meanSpectrum[b] + N2/((float)(N1+N2))* other_->getMeanSpectrumAt(b);
        merged_->setMeanSpectrumAt(b,f);

        // merge std
        float sigma = sqrt((N1*pow(std[b],2) + N2*pow(other_->getStd()[b],2)
                            +N1*pow(meanSpectrum[b]-merged_->getMeanSpectrumAt(b),2)
                            +N2*pow(other_->getMeanSpectrumAt(b)-merged_->getMeanSpectrumAt(b),2))/(float)(N1+N2));
        merged_->setStd(b,sigma);

    }


    /*
    //#pragma omp parallel for
    for (int short b= 0;b<nbands;b++){
        //merge mean spectra:
        float f = N1/((float)(N1+N2))* meanSpectrum[b] + N2/((float)(N1+N2))* other_->getMeanSpectrumAt(b);
        merged_->setMeanSpectrumAt(b,f);

        // merge std
        float sigma = sqrt((N1*pow(std[b],2) + N2*pow(other_->getStd()[b],2)
                            +N1*pow(meanSpectrum[b]-merged_->getMeanSpectrumAt(b),2)
                            +N2*pow(other_->getMeanSpectrumAt(b)-merged_->getMeanSpectrumAt(b),2))/(float)(N1+N2));
        merged_->setStd(b,sigma);

    }



   \\merge std
    for (int short b=0; b<nbands; b++) {
        float sigma = sqrt((N1*pow(std[b],2) + N2*pow(other_->getStd()[b],2)
                            +N1*pow(meanSpectrum[b]-merged_->getMeanSpectrumAt(b),2)
                            +N2*pow(other_->getMeanSpectrumAt(b)-merged_->getMeanSpectrumAt(b),2))/(float)(N1+N2));
        merged_->setStd(b,sigma);
    }
*/



    //release histograms upon merging
    this->releaseHistogram();
    other_->releaseHistogram();
    return merged_;

}



void histogramModel::setHistogramValue(unsigned short band, unsigned short bin, float p)
{
    histograms[band][bin] = p;
}

void histogramModel::increaseHistogramValue(unsigned short band, unsigned short bin)
{
    histograms[band][bin] = histograms[band][bin]+1;
}

void histogramModel::increaseHistogramValueBy(unsigned short band, unsigned short bin, float v)
{
    histograms[band][bin] = histograms[band][bin]+v;
}

float histogramModel::getValue(unsigned short band, unsigned short bin)
{
    return histograms[band][bin];
}




const std::vector<float> &histogramModel::getBand(unsigned short b)
{
    return histograms[b];
}

unsigned short histogramModel::getNBands()
{
    return nbands;
}

unsigned short histogramModel::getNBins()
{
    return nbins;
}

void histogramModel::normalizeBand(unsigned short b)
{
        //get sum
        float acum = 0;
        for (int short n=0;n<nbins;n++)
            acum+=histograms[b][n];

        //normalize
        for (int short n=0;n<nbins;n++)
            histograms[b][n]=histograms[b][n]/acum;

}

std::vector<float> &histogramModel::getSpectrum()
{
    return meanSpectrum;
}

std::vector<float> &histogramModel::getStd()
{
    return this->std;
}


void histogramModel::setMeanSpectrumAt(unsigned short band, float value)
{
    meanSpectrum[band]=value;
}

void histogramModel::setStd(unsigned short band, float value){
    std[band] = value;
}

float histogramModel::getMeanSpectrumAt(unsigned short band)
{
    return meanSpectrum[band];
}


// compute the region cost
double histogramModel::cutCost( bool useStdCut)
{
    if( !useStdCut ) return 0;
    float stdCost = 0;
    for(int short b = 0; b < nbands ; b++){
        stdCost += this->area * this->std[b];
    }

    return stdCost; // we need to replace this 1000 with a parameter

}






histogramModel *histogramModel::clone()
{
    histogramModel* cloned = new histogramModel(nbands,nbins);

    cloned->setArea(this->area);
    return cloned;

}




void histogramModel::releaseHistogram()
{
    histograms.clear();
}





unsigned short histogramModel::getNClasses()
{
    return 0;
}


void histogramModel::printHistogram(){

    std::cout<<"The histogram of the region is :" << endl;
    for(size_t i=0; i<this->histograms.size(); i++){
        for(size_t j=0; j< this->histograms[i].size(); j++){
            std::cout<< this->histograms[i][j] << " , ";
        }
        std::cout<<endl<<endl;
    }
    std::cout << endl;
    return;

 }



std::vector<float> histogramModel::getMeanSpectrum()
{
    return meanSpectrum;
}


