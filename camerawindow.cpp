#include "camerawindow.h"
#include "ui_camerawindow.h"

CameraWindow::CameraWindow(QWidget *parent, int number) :
    QMainWindow(parent),
    ui(new Ui::CameraWindow)
{
    ui->setupUi(this);
    QString t = this->windowTitle();
    this->setWindowTitle(t + "[" + QString::number(number) + "]");
    ct = new CameraThread(0, number);
    connect(ct, SIGNAL(processedImage(QImage)), this, SLOT(updateImage(QImage)));
    connect(ct, SIGNAL(processedStats(VideoStats)), this, SLOT(updateStats(VideoStats)));
    ct->Play();
}

void CameraWindow::closeEvent(QCloseEvent *) {
    ct->deleteLater();
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::updateImage(QImage img) {
    if(!img.isNull()) {
        ui->imageViewer->setPixmap(QPixmap::fromImage(img));
    }
}

void CameraWindow::updateStats(VideoStats stats) {
    ui->imageViewer->resize(stats.getWidth(), stats.getHeight());
    ui->lblWidth->setText(QString::number(stats.getWidth()) + " X " + QString::number(stats.getHeight()));
    ui->lblFPS->setText(QString::number(stats.getFps()));
}
