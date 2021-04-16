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
//    void SigRecs(double *vecs);
    void SigRecs(double rvecs_1, double rvecs_2, double rvecs_3, double tvecs_1, double tvecs_2, double tvecs_3);
};

#endif // CAMERAWORKER_H
