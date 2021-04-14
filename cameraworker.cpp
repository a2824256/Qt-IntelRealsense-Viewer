#include "cameraworker.h"
#include <QDebug>
#include <mainwindow.h>
CameraWorker::CameraWorker()
{
}


CameraWorker::~CameraWorker()
{
    p.stop();
}


void CameraWorker::doWork(){
    p.start();
    /* 获取内参-start */
    //rs2_intrinsics intr
    auto const i = p.get_active_profile().get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_intrinsics();
    qDebug() << i.width << endl;
    /* 获取内参-end */
    rs2::frameset frames;
    qDebug() << "camera start" << endl;
    while (true)
    {
        frames = p.wait_for_frames();
        rs2::frame color = frames.get_color_frame();
//        rs2::depth_frame depth = frames.get_depth_frame();
        const int w = color.as<rs2::video_frame>().get_width();
        const int h = color.as<rs2::video_frame>().get_height();

        Mat mat(Size(w, h), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        emit SigRTRGB(image);
    }
    p.stop();
    qDebug() << "worker exit" << endl;
}

