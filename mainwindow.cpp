#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAdd_Camera, SIGNAL(triggered()), this, SLOT(addCamera()));

    // Get list of connected devices
    cap = new VideoCapture();
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
    ui->logBrowser->append("Number of devices found: " + QString::number(count)) ;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cap;
}

void MainWindow::addCamera() {
    CameraConnectDialog *cam = new CameraConnectDialog(this, listOfDevices);
    cam->show();
}
