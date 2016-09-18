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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "image.h"


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_selectFileName_clicked();
    void on_Go_clicked();
    void on_selectDirectory_clicked();
    void on_actionHoover_Calculator_triggered();
    void on_actionImage_Cropper_triggered();
    void on_selectDirectoryProbabilities_clicked();
    void on_actionProbability_File_Cropper_triggered();

private:
    Ui::MainWindow *ui;
    image myimage;

};



#endif // MAINWINDOW_H



