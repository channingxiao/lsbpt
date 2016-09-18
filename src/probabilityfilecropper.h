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


#ifndef PROBABILITYFILECROPPER_H
#define PROBABILITYFILECROPPER_H

#include <QMainWindow>
#include <iostream>
using namespace std;

namespace Ui {
class ProbabilityFileCropper;
}


class ProbabilityFileCropper : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProbabilityFileCropper(QWidget *parent = 0);
    ~ProbabilityFileCropper();

private slots:
    void on_selectProbabiltyFile_clicked();

    void on_selectDirectory_clicked();

    void on_cut_clicked();

private:
    Ui::ProbabilityFileCropper *ui;
    std::string probabilityFileName;
    std::string directoryName;
    int imageWidth;
    int imageHeight;
    int numClasses;
    int width;
    int height;
    int startX;
    int startY;
    int numBlocksX;
    int numBlocksY;


};

#endif // PROBABILITYFILECROPPER_H
