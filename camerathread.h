#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include "imageconversion.h"
#include "videostats.h"
using namespace cv;

class CameraThread : public QThread
{
    Q_OBJECT
public:
    CameraThread(QObject *parent = 0, int deviceNumber = 0);
    ~CameraThread();
    void Play();
    void Stop();
    bool isStopped() const;
protected:
    void run();
    void msleep(int ms);

signals:
    void processedImage(const QImage &image);
    void processedStats(const VideoStats &stats);

private:
    int deviceNumber;
    QMutex mux;
    QWaitCondition condition;
    Mat frame;
    VideoCapture cap;
    int frameCount;
    QImage img;
    bool stop;
    ImageConversion conv;
    VideoStats stats;

};

#endif // CAMERATHREAD_H
