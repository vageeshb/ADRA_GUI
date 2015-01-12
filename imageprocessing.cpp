#include "imageprocessing.h"

ImageProcessing::ImageProcessing()
{
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

ImageProcessing::~ImageProcessing()
{

}

QImage ImageProcessing::DetectPeopleWithFilter(Mat &inMat) {
    found.clear();
    found_filtered.clear();

    hog.detectMultiScale(inMat, found, 0,
                    Size(8, 8),
                    Size(32, 32),
                    1.05, 2);
    // Filter the found features
    for (i=0; i<found.size(); i++) {
        r = found[i];
        for (j=0; j<found.size(); j++)
            if (j!=i && (r & found[j])==r)
                break;
        if (j==found.size())
            found_filtered.push_back(r);
    }
    for (i=0; i<found_filtered.size(); i++) {
        r = found_filtered[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.06);
        r.height = cvRound(r.height*0.9);
        rectangle(inMat, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
    }
    return MatToQImage(inMat);
}

QImage ImageProcessing::DetectPeople(Mat &inMat) {
    found.clear();
    found_filtered.clear();

    hog.detectMultiScale(inMat, found, 0,
                    Size(8, 8),
                    Size(32, 32),
                    1.05, 2);

    // Mark the found features with a rectangle
    for (i=0; i<found.size(); i++) {
        r = found_filtered[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.06);
        r.height = cvRound(r.height*0.9);
        rectangle(inMat, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
    }
    return MatToQImage(inMat);
}

QImage ImageProcessing::MatToQImage(cv::Mat &inMat) {
    switch(inMat.type()) {
        case CV_8UC4: {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
            return image;
        }
        case CV_8UC3: {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
            return image.rgbSwapped();
        }
        case CV_8UC1: {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
        }
        default:
            qWarning() << "OpenCV Image type not handled:" << inMat.type();
            break;
    }
    return QImage();
}
cv::Mat QImageToMat( const QImage &inImage, bool inCloneImageData = true )
{
  switch ( inImage.format() )
  {
     // 8-bit, 4 channel
     case QImage::Format_RGB32:
     {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

        return (inCloneImageData ? mat.clone() : mat);
     }

     // 8-bit, 3 channel
     case QImage::Format_RGB888:
     {
        if ( !inCloneImageData )
           qWarning("Conversion requires cloning since we use a temporary QImage");

        QImage   swapped = inImage.rgbSwapped();

        return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
     }

     // 8-bit, 1 channel
     case QImage::Format_Indexed8:
     {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

        return (inCloneImageData ? mat.clone() : mat);
     }

     default:
        qWarning() << "QImage format not handled: " << inImage.format();
        break;
  }

  return cv::Mat();
}
