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

#ifndef HOOVERCALCULATOR_H
#define HOOVERCALCULATOR_H

#include <QDialog>
#include <QFileDialog>
#include <hoovermetrics.h>

using namespace std;

namespace Ui {
class HooverCalculator;
}

class HooverCalculator : public QDialog
{
    Q_OBJECT

public:
    explicit HooverCalculator(QWidget *parent = 0);
    ~HooverCalculator();

private slots:

    void on_ComputeHoover_clicked();

    void on_SelectReference_clicked();

    void on_selectTilingSeg_clicked();

    void on_selectHooverComparison_clicked();


private:
    Ui::HooverCalculator *ui;

    std::string fileName_HooverReference;
    std::string fileName_HooverTilingSeg;
    std::string fileName_HooverComparison;



};

#endif // HOOVERCALCULATOR_H
