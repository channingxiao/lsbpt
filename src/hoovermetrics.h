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



#ifndef HOOVERMETRICS_H
#define HOOVERMETRICS_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "io.h"
using namespace std;


void computeTable(std::vector<std::vector<int> > &image_1,
                  std::vector<std::vector<int> > &image_2,
                  std::vector<std::vector<int> > *hooverTable,
                  std::vector<int> *image_1_regions,
                  std::vector<int> *image_2_regions);


void regionsClassification(std::vector<int> &image_1_regions,
                           std::vector<int> &image_2_regions,
                           std::vector<std::vector<int> > &hooverTable,
                           std::vector<int> *regionType_1,
                           std::vector<int> *regionType_2,
                           float tolerance);

void computerHooverMetrics(std::vector<int> &image_1_regions,
                           std::vector<int> &image_2_regions,
                           std::vector<int> &regionType_1,
                           std::vector<int> &regionType_2);


void paintHoover( std::vector<std::vector<int> > &image, std::vector<int> &regionType, std::string fileName_save);

void hooverCompare(std::string fileName1, std::string fileName2,std::string fileName_save, float tolerance);



#endif // HOOVERMETRICS_H
