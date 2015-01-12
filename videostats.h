#ifndef VIDEOSTATS_H
#define VIDEOSTATS_H

#include <QMetaType>

class VideoStats
{
public:
    VideoStats();
    VideoStats(const VideoStats &stats);
    VideoStats(int w, int h, int f);
    ~VideoStats();
    int getWidth();
    int getHeight();
    int getFps();
    void setWidth(int w);
    void setHeight(int h);
    void setFps(int f);
private:
    int width;
    int height;
    int fps;
};

Q_DECLARE_METATYPE(VideoStats);

#endif // VIDEOSTATS_H
