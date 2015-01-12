#include "camerathread.h"

CameraThread::CameraThread(QObject *parent, int deviceNumber) : QThread(parent)
{
    stop = false;
    this->deviceNumber = deviceNumber;
    conv = new ImageProcessing();
    filter = false;
    detect = false;
}

CameraThread::~CameraThread()
{
    mux.lock();
    stop = true;
    this->sleep(1);
    cap.release();
    condition.wakeOne();
    mux.unlock();
    wait();
}

void CameraThread::updateDetect(bool checked) {
    detect = checked;
}

void CameraThread::updateFiltered(bool checked) {
    filter = checked;
}

void CameraThread::run() {
    QElapsedTimer timer;
    timer.start();
    cap.open(deviceNumber);

    stats.setWidth(cap.get(CV_CAP_PROP_FRAME_WIDTH));
    stats.setHeight(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    stats.setFps(0);

    qDebug() << "Initialiazing Camera [" << deviceNumber << "]";
    qDebug() << "Frame Size: " << cap.get(CV_CAP_PROP_FRAME_WIDTH) << "x" << cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    emit processedSizes(stats);
    frameCount = 0;

    if(cap.isOpened()) {
        while(!stop) {
            frameCount++;
            cap.read(frame);
            if(frame.data) {
                if(detect) {
                    if(filter)
                        img = conv->DetectPeopleWithFilter(frame);
                    else
                        img = conv->DetectPeople(frame);
                }
                else
                    img = conv->MatToQImage(frame);

                if(timer.elapsed() >= 1000) {
                    stats.setFps(frameCount);
                    emit processedStats(stats);
                    frameCount = 0;
                    timer.restart();
                }
                emit processedImage(img);
            }
        }
    }
}

void CameraThread::msleep(int ms) {
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

void CameraThread::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

bool CameraThread::isStopped() const{
    return this->stop;
}
