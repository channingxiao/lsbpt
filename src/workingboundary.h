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


#ifndef WORKINGBOUNDARY_H
#define WORKINGBOUNDARY_H


class WorkingBoundary
{
public:
    WorkingBoundary();
    WorkingBoundary(int directionTemp, long indexTemp, long minTemp, long maxTemp);


    int direction; //<* 0 represents horizontal, 1 represents verticle
    long index;
    long min;
    long max;
};

#endif // WORKINGBOUNDARY_H
