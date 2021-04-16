#include <QDebug>
#include <mainwindow.h>
#include <opencv2/aruco.hpp>

#include <cameraworker.h>
using namespace std;
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
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    vector<int> ids;
    vector<vector<cv::Point2f>> corners;
    /* 配置相机内参-start */
    float *coeffs = new float[5];
    float cameraArray[3][3] = {{i.fx, 0, i.ppx}, {0, i.fy, i.ppy}, {0, 0, 1}};
//    double vecs[6];
    double vecs[6];
    memcpy(coeffs, i.coeffs, sizeof(float)*5);
    cv::Mat cameraMatrix(3, 3, CV_32FC1, cameraArray), distCoeffs(1, 5, CV_32FC1, coeffs);
    /* 配置相机内参-end */
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
        qDebug() <<"w:"<< w;
        qDebug() <<"h"<< h;
        Mat mat(Size(w, h), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
        cv::aruco::detectMarkers(mat, dictionary, corners, ids);
        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(mat, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, 0.045, cameraMatrix, distCoeffs, rvecs, tvecs);
            for(int i=0; i<ids.size(); i++){
               cv::aruco::drawAxis(mat, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.05);
               double TempVecs[6] = {rvecs[i][0], rvecs[i][1], rvecs[i][2], tvecs[i][0], tvecs[i][1], tvecs[i][2]};
               memcpy(vecs, TempVecs, sizeof(double)*6);
            }
        }
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        emit SigRTRGB(image);
        emit SigRecs(vecs[0], vecs[1], vecs[2], vecs[3], vecs[4], vecs[5]);
    }
    p.stop();
    qDebug() << "worker exit" << endl;
}
