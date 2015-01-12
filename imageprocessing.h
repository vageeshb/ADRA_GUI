#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>
#include <QDebug>
#include "opencv2/opencv.hpp"

using namespace cv;
class ImageProcessing
{
public:
    ImageProcessing();
    ~ImageProcessing();
    QImage MatToQImage(Mat &image);
    QImage DetectPeopleWithFilter(Mat &image);
    QImage DetectPeople(Mat &image);
    Mat QImageToMat( const QImage &inImage, bool inCloneImageData);
private:
    HOGDescriptor hog;
    std::vector<Rect> found, found_filtered;
    size_t i, j;
    Rect r;
};

#endif // IMAGEPROCESSING_H
