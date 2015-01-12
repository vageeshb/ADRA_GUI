#include "cameraconnectdialog.h"
#include "ui_cameraconnectdialog.h"

CameraConnectDialog::CameraConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraConnectDialog)
{
    ui->setupUi(this);
}

CameraConnectDialog::~CameraConnectDialog()
{
    delete ui;
}

int CameraConnectDialog::getCameraNumber() {
    return ui->cameraNumber->text().toInt();
}
