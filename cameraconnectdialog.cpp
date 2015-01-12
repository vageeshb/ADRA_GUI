#include "cameraconnectdialog.h"
#include "ui_cameraconnectdialog.h"

CameraConnectDialog::CameraConnectDialog(QWidget *parent, std::vector<int> devices) :
    QDialog(parent),
    ui(new Ui::CameraConnectDialog)
{
    ui->setupUi(this);
    for(std::vector<int>::iterator it = devices.begin(); it != devices.end(); ++it) {
        ui->deviceBox->addItem(QString::number(*it));
    }
}

CameraConnectDialog::~CameraConnectDialog()
{
    delete ui;
}

int CameraConnectDialog::getCameraNumber() {
    return ui->deviceBox->currentText().toInt();
}
