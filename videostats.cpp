#include "videostats.h"

VideoStats::VideoStats() {

}

VideoStats::VideoStats(const VideoStats &stats) {
    width = stats.width;
    height = stats.height;
    fps = stats.fps;
}

VideoStats::VideoStats(int w, int h, int f)
{
    width = w;
    height = h;
    fps = f;
}

VideoStats::~VideoStats()
{

}

void VideoStats::setFps(int f) {
    fps = f;
}

void VideoStats::setHeight(int h) {
    height = h;
}

void VideoStats::setWidth(int w) {
    width = w;
}

int VideoStats::getHeight() {
    return height;
}

int VideoStats::getWidth() {
    return width;
}

int VideoStats::getFps() {
    return fps;
}
