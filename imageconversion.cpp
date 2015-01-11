#include "imageconversion.h"

ImageConversion::ImageConversion()
{

}

ImageConversion::~ImageConversion()
{

}

QImage ImageConversion::MatToQImage(cv::Mat &inMat) {
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
