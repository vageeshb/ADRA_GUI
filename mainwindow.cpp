#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAdd_Camera, SIGNAL(triggered()), this, SLOT(addCamera()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCamera() {
    CameraConnectDialog *camConnect = new CameraConnectDialog(this);
    int retCode = camConnect->exec();
    if(retCode == QDialog::Accepted) {
        CameraWindow *w = new CameraWindow(this, camConnect->getCameraNumber());
        w->show();
    }
}
