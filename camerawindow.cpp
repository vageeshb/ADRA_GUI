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
    connect(ct, SIGNAL(processedSizes(VideoStats)), this, SLOT(updateWindow(VideoStats)));
    connect(this, SIGNAL(updateDetect(bool)), ct, SLOT(updateDetect(bool)));
    connect(this, SIGNAL(updateFiltered(bool)), ct, SLOT(updateFiltered(bool)));
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

void CameraWindow::updateWindow(VideoStats stats) {
    int w = stats.getWidth(), h = stats.getHeight();

    this->setMinimumSize(w, h + 100);
    this->setMaximumSize(w, h + 100);
    this->statusBar()->setSizeGripEnabled(false);
    ui->centralwidget->resize(w, h + 100);
}

void CameraWindow::updateStats(VideoStats stats) {
    int w = stats.getWidth(), h = stats.getHeight();
    ui->lblSize->setText(QString::number(w) + " X " + QString::number(h));
    ui->lblFPS->setText(QString::number(stats.getFps()));
}


void CameraWindow::on_chkFiltered_clicked(bool checked)
{
    emit updateFiltered(checked);
}

void CameraWindow::on_chkDetect_clicked(bool checked)
{
    emit updateDetect(checked);
}
