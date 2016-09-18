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








#include "compoundmodel.h"
#include "QDebug"

double compoundModel::areaExponent;
bool compoundModel::areaWeighted;
long compoundModel::floor;
bool compoundModel::ifUseMinimumToMerge = false;
double compoundModel::probabilityModelWeight = 0;


compoundModel::compoundModel()
{
    hist_model=0;
    prob_model =0;
    this->area=1;
    alpha = 0; // show be set as a parameter
}

compoundModel::compoundModel( histogramModel * histogramModelTemp, probabilityModel * probabilityModelTemp ){
    this->hist_model = histogramModelTemp;
    this->prob_model = probabilityModelTemp;
    this->area=1;
    alpha = 0; // show be set as a parameter

}

compoundModel::compoundModel( histogramModel * histogramModelTemp)
{
    this->hist_model = histogramModelTemp;
    prob_model =0;
    this->area=1;
    alpha = 0; // show be set as a parameter

}


compoundModel::~compoundModel()
{
    delete hist_model;
    delete prob_model;

}




regionModel *compoundModel::merge(regionModel *other)
{

    compoundModel* other_ = (compoundModel*) other;

    compoundModel* merged = new compoundModel();


    if (this->hist_model!=0){
        histogramModel* merged_hist = this->hist_model->merge(other_->getHistogramModel());
        merged->setHistogramModel(merged_hist);
    }

    if (this->prob_model!=0){
        probabilityModel* merged_prob = this->prob_model->merge(other_->getProbModel());
        merged->setProbModel(merged_prob);
    }

    merged->setArea(this->getArea()+other->getArea());

    return merged;

}


compoundModel* compoundModel::getModel(){
    return this;
}

std::vector<double> compoundModel::getProbability(){

    if( this->prob_model == NULL) std::cout << "Probability model not exist." << endl;
    //std::vector<double> temp = this->prob_model->getProbability();
    return this->prob_model->getProbability();

}

std::vector<float> compoundModel::getMeanSpectrum()
{
    return this->hist_model->getMeanSpectrum();
}



/*

double compoundModel::getOrder(regionModel *other)
{

    compoundModel* other_ = (compoundModel*) other;
    double out;

    //compute dissimilarity between histograms
    double hist_disimilarity = this->getHistogramModel()->getOrder(other_->getHistogramModel());

    //compute dissimilarity based on class probabilities,
    //if available
    double cost_diff_class = 0;

    if (this->prob_model!=0)
        cost_diff_class=this->getProbModel()->getOrder(other_->getProbModel());
    else {
        cost_diff_class=0;
        alpha=0;
    }


    //get area of both nodes
    long N1 = this->getArea();
    long N2 = other_->getArea();
    long Nmin = N1 < N2 ? N1 : N2;
    long Nmax = N1 > N2 ? N1 : N2;

    //if use area weight
    if (globalSettings::areaWeighted){ //not area weighted
         out = pow((double)Nmin,globalSettings::areaExponent)*((alpha)*cost_diff_class+(1.0-alpha)*(hist_disimilarity));
    } else { //area weighted
        out = alpha*cost_diff_class + (1.0-alpha)*hist_disimilarity;
    }

    // if use minimum to merge strategy
    double floorCost = 0;
    if( globalSettings::ifUseMinimumToMerge ){
        if (Nmax > globalSettings::floor) floorCost = globalSettings::floor;

    }


    return out;

}

*/



double compoundModel::getOrder(regionModel *other)
{

    compoundModel* other_ = (compoundModel*) other;
    double out;

    //compute dissimilarity between histograms
    double hist_disimilarity = this->getHistogramModel()->getOrder(other_->getHistogramModel());

    //compute dissimilarity based on class probabilities,
    //if available
    double cost_diff_class = 0;

    alpha = this->probabilityModelWeight;
    if (this->prob_model!=0)
        cost_diff_class=this->getProbModel()->getOrder(other_->getProbModel());
    else {
        cost_diff_class=0;
        alpha=0;
    }


    //get area of both nodes
    long N1 = this->getArea();
    long N2 = other_->getArea();
    long Nmin = N1 < N2 ? N1 : N2;
    long Nmax = N1 > N2 ? N1 : N2;

    //if use area weight
    if (this->areaWeighted){ //not area weighted
         out = pow((double)Nmin,this->areaExponent)*((alpha)*cost_diff_class+(1.0-alpha)*(hist_disimilarity));
    } else { //area weighted
        out = alpha*cost_diff_class + (1.0-alpha)*hist_disimilarity;
    }

    // if use minimum to merge strategy
    double floorCost = 0;
    if( this->ifUseMinimumToMerge ){
        if (Nmax > this->floor) floorCost = this->floor;
    }


    return out;

}



/*


double compoundModel::getOrder(regionModel *other, bool areaWeighted, double areaExponent, double alpha, bool ifUseMinimumToMerge, float floor )
{

    compoundModel* other_ = (compoundModel*) other;
    double out;

    //compute dissimilarity between histograms
    double hist_disimilarity = this->getHistogramModel()->getOrder(other_->getHistogramModel());

    //compute dissimilarity based on class probabilities,
    //if available
    double cost_diff_class = 0;

    if (this->prob_model!=0)
        cost_diff_class=this->getProbModel()->getOrder(other_->getProbModel());
    else {
        cost_diff_class=0;
        alpha=0;
    }


    //get area of both nodes
    long N1 = this->getArea();
    long N2 = other_->getArea();
    long Nmin = N1 < N2 ? N1 : N2;
    long Nmax = N1 > N2 ? N1 : N2;

    //if use area weight
    if(areaWeighted){ //not area weighted
         out = pow((double)Nmin,areaExponent)*((alpha)*cost_diff_class+(1.0-alpha)*(hist_disimilarity));
    } else { //area weighted
        out = alpha*cost_diff_class + (1.0-alpha)*hist_disimilarity;
    }

    // if use minimum to merge strategy
    double floorCost = 0;
    if( ifUseMinimumToMerge ){
        if (Nmax > floor) floorCost = floor;

    }


    return (out + floorCost);

}

*/



compoundModel *compoundModel::clone()
{

    compoundModel* cloned_model = new compoundModel();

    if (this->hist_model!=0){
        histogramModel*  cloned_hist_model = this->hist_model->clone();
        cloned_model->setHistogramModel(cloned_hist_model);
    }

    cloned_model->setArea(this->area);

    return cloned_model;


}

double compoundModel::cutCost( bool useStdCut )
{
    if( useStdCut ){
    return this->hist_model->cutCost( useStdCut );
    } else {
    return this->prob_model->cutCost( useStdCut );
    }

}





void compoundModel::setNode(Node *n)
{

    //std::cout<<"hey"<<std::endl;
    this->node=n;
    if (hist_model!=0)
        hist_model->setNode(n);
}



void compoundModel::setHistogramModel(histogramModel *hist_model)
{
    this->hist_model=hist_model;

}

histogramModel* compoundModel::getHistogramModel()
{
    return hist_model;

}

float compoundModel::getMeanSpectrumAt(unsigned short band){
    return hist_model->getMeanSpectrumAt(band);
}


unsigned short compoundModel::getLowestCostClass(){
    return this->prob_model->getLowestCostClass();
}

void compoundModel::setProbModel(probabilityModel *prob_model)
{
    this->prob_model=prob_model;

}

probabilityModel *compoundModel::getProbModel()
{
    return prob_model;
}



