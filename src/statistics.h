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
Class that provides static functions for statistics
*/


#ifndef STATISTICS_H
#define STATISTICS_H


#include <vector>
#include "math.h"

#include <iostream>

#include <limits>

using namespace std;

class statistics
{
public:
    statistics();


    static float bhatt(const std::vector<float> &X, const std::vector<float> &Y);

    static float bhatt(float X[], float Y[], unsigned short n);

    static float EMD(const std::vector<float>& X, const std::vector<float>& Y);

    static float abs(float v);

    static float correlation(const std::vector<float> &X, const std::vector<float> &Y);

    class distribution {
        std::vector<double> p;
        double min;
        double max;
    public:
        double getValAt(double value){

            if (value>max || value < min)
                return 0;

            int lowerBin;
            int upperBin;

            double fraction = (value-min)/(max-min)*((double)p.size()-1);

            upperBin=ceil(fraction);
            lowerBin=upperBin-1;

            double alpha; //how much of previous bin
            double beta; //how much of next bin

            alpha = 1-(fraction - lowerBin);
            beta = 1-(upperBin - fraction);

            if (lowerBin==-1)
                return beta*p[upperBin];


            return alpha*p[lowerBin] + beta*p[upperBin];


        }

        double getProb(double from, double to){
            return (getValAt(from)+getValAt(to))/2.0*(to-from);
        }



        void push(double v){p.push_back(v);}
        double getValueAtBin(unsigned short b){return p[b];}

        unsigned short getNbins(){return p.size();}

        double getMin() const;
        void setMin(double value);
        double getMax() const;
        void setMax(double value);
    };


};

#endif // STATISTICS_H
