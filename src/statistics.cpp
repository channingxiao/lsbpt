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








#include "statistics.h"

statistics::statistics()
{
}



float statistics::bhatt(const std::vector<float>& X, const std::vector<float>& Y)
{


     //Battacharyya coefficient
     float BC=0;
     for (size_t i=0;i<X.size();i++){
         BC+=sqrt(X[i]*Y[i]);
     }

     if (BC!=0)
        BC = - log(BC);
    else
        BC=std::numeric_limits<float>::infinity();  //large coefficient

     return BC;
}

float statistics::bhatt(float X[], float Y[], unsigned short n)
{
    //Battacharyya coefficient
    float BC=0;
    for (int short i=0;i<n;i++){
        BC+=sqrt(X[i]*Y[i]);
    }


    if (BC!=0)
       BC = - log(BC);
   else
       BC=std::numeric_limits<float>::infinity();


    return BC;
}




float statistics::EMD(const std::vector<float>& X, const std::vector<float>& Y){

    float Xac[X.size()];
    float Yac[X.size()];

    //transform into cummulative distributions
    Xac[0]=X[0];
    Yac[0]=Y[0];
    for (size_t i=1;i<X.size();i++){
        Xac[i]=X[i]+Xac[i-1];
    }
    for (size_t i=1;i<Y.size();i++){
        Yac[i]=Y[i]+Yac[i-1];
    }

    //compute emd (Rubner et al. 1998)
    float emd = 0;

    for (size_t i=0;i<X.size();i++){

       emd+= abs(Xac[i]-Yac[i]);

    }


    float normalizer = 1.0/((float)X.size());

    return emd*normalizer;

}






float statistics::abs(float v)
{
    if (v>=0)
        return v;
    else
        return -1*v;
}


float statistics::correlation(const std::vector<float> &X, const std::vector<float> &Y)
{
    //correlation coefficient

    unsigned short n = X.size();

    //x bar
    float xbar = 0;
    for (int short  i = 0;i<n;i++)
        xbar+=X[i];
    xbar=xbar/((float)n);

    //y bar
    float ybar = 0;
    for (int short  i = 0;i<n;i++)
        ybar+=Y[i];
    ybar=ybar/((float)n);

    //covariance (no need to divide by n)
    float cov = 0;
    for (int short  i = 0;i<n;i++)
        cov += (X[i]-xbar)*(Y[i]-ybar);

    //sigmaX (no need to divide by n)
    float sigmaX = 0;
    for (int short  i = 0;i<n;i++)
        sigmaX += (X[i]-xbar)*(X[i]-xbar);

    //sigmaY (no need to divide by n)
    float sigmaY = 0;
    for (int short  i = 0;i<n;i++)
        sigmaY += (Y[i]-ybar)*(Y[i]-ybar);

    return cov/(sqrt(sigmaX*sigmaY));

}

double statistics::distribution::getMin() const
{
    return min;
}

void statistics::distribution::setMin(double value)
{
    min = value;
}

double statistics::distribution::getMax() const
{
    return max;
}

void statistics::distribution::setMax(double value)
{
    max = value;
}
