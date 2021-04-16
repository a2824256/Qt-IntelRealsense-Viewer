#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QThread>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QThread workerThread;
private:
    double recs[6];
signals:
    void SigStartCamera();
private slots:
    void on_pushButton_clicked();
    void SigUpdateFrame(QImage image);
    void SigUpdateRecs(double rvecs_1, double rvecs_2, double rvecs_3, double tvecs_1, double tvecs_2, double tvecs_3);
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
