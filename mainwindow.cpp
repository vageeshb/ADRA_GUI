#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAdd_Camera, SIGNAL(triggered()), this, SLOT(addCamera()));

    // Get list of connected devices
    listOfDevices.push_back(0);
    /*cap = new VideoCapture();
    int count = 0;
    for(int i=0; i < 10; i++) {
        if(cap->open(i)) {
            count++;
            listOfDevices.push_back(i);
            cap->release();
        }
        else
            break;
    }
    delete cap;
    ui->logBrowser->append("Number of devices found: " + QString::number(count)) ;*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCamera() {
    CameraConnectDialog *camConnect = new CameraConnectDialog(this, listOfDevices);
    int retCode = camConnect->exec();
    if(retCode == QDialog::Accepted) {
        CameraWindow *w = new CameraWindow(this, camConnect->getCameraNumber());
        w->show();
    }
}
