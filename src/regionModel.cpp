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








#include "regionModel.h"




void regionModel::setNode(Node *n)
{
    this->node=n;
}

Node *regionModel::getNode()
{
    return node;
}

void regionModel::setArea(unsigned long a)
{
    this->area=a;
}

unsigned long regionModel::getArea()
{
    return area;
}
