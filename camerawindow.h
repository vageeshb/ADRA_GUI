#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include "videostats.h"
#include "camerathread.h"

using namespace cv;

namespace Ui {
class CameraWindow;
}

class CameraWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent, int deviceNumber);
    void start();
    ~CameraWindow();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void updateImage(QImage img);
    void updateStats(VideoStats stats);
private:
    Ui::CameraWindow *ui;
    int deviceNumber;
    CameraThread *ct;
};

#endif // CAMERAWINDOW_H
