#ifndef CAMERACONNECTDIALOG_H
#define CAMERACONNECTDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class CameraConnectDialog;
}

class CameraConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraConnectDialog(QWidget *parent, std::vector<int> devices);
    ~CameraConnectDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CameraConnectDialog *ui;
};

#endif // CAMERACONNECTDIALOG_H
