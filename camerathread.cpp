#include "camerathread.h"

CameraThread::CameraThread(QObject *parent, int deviceNumber) : QThread(parent)
{
    stop = false;
    this->deviceNumber = deviceNumber;
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

void CameraThread::run() {
    QElapsedTimer timer;
    timer.start();
    cap.open(deviceNumber);

    stats.setWidth(cap.get(CV_CAP_PROP_FRAME_WIDTH));
    stats.setHeight(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    stats.setFps(0);

    qDebug() << cap.get(CV_CAP_PROP_FRAME_WIDTH) << "x" << cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    emit processedStats(stats);
    frameCount = 0;

    if(cap.isOpened()) {
        while(!stop) {
            frameCount++;
            cap.read(frame);
            img = conv.MatToQImage(frame);
            if(timer.elapsed() >= 1000) {
                stats.setFps(frameCount / timer.elapsed());
                emit processedStats(stats);
                frameCount = 0;
                timer.restart();
            }
            emit processedImage(img);
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
