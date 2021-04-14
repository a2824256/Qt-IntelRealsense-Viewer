#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H
#include <QObject>
#include <QImage>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
class CameraWorker : public QObject
{
    Q_OBJECT
public:
    CameraWorker();
    ~CameraWorker();
    rs2::pipeline p;
public slots:
    void doWork();

signals:
    void resultReady(const QString &result);
    void SigRTRGB(QImage rbg);
};

#endif // CAMERAWORKER_H
