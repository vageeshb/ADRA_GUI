#ifndef IMAGECONVERSION_H
#define IMAGECONVERSION_H

#include <QImage>
#include <QDebug>
#include "opencv2/opencv.hpp"

class ImageConversion
{
public:
    ImageConversion();
    ~ImageConversion();
    QImage MatToQImage(cv::Mat &image);
    cv::Mat QImageToMat( const QImage &inImage, bool inCloneImageData);
};

#endif // IMAGECONVERSION_H
