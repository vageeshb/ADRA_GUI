#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include "cameraconnectdialog.h"

using namespace cv;

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
    void addCamera();

private:
    Ui::MainWindow *ui;
    CameraConnectDialog *dialog;
    VideoCapture *cap;
    vector<int> listOfDevices;
};

#endif // MAINWINDOW_H
