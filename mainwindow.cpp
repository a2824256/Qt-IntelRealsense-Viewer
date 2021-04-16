#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include "cameraworker.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CameraWorker *worker = new CameraWorker;
    worker->moveToThread(&workerThread);
    connect(this, &MainWindow::SigStartCamera, worker, &CameraWorker::doWork);
    connect(worker, &CameraWorker::SigRTRGB, this,  &MainWindow::SigUpdateFrame);
    connect(worker, &CameraWorker::SigRecs, this, &MainWindow::SigUpdateRecs);
    workerThread.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    workerThread.terminate();
    workerThread.wait();
    qDebug() << "camera thread exit" << endl;
}


void MainWindow::on_pushButton_clicked()
{
    emit SigStartCamera();
}

void MainWindow::SigUpdateFrame(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::SigUpdateRecs(double rvecs_1, double rvecs_2, double rvecs_3, double tvecs_1, double tvecs_2, double tvecs_3)
{
    this->recs[0] = rvecs_1;
    this->recs[1] = rvecs_2;
    this->recs[2] = rvecs_3;
    this->recs[3] = tvecs_1;
    this->recs[4] = tvecs_2;
    this->recs[5] = tvecs_3;
//    qDebug() << "recs";
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = "rvecs:" + QString::number(this->recs[0], '.', 8) + "," + QString::number(this->recs[1], '.', 8) + "," + QString::number(this->recs[2], '.', 8) + "\n";
    str +=  "tvecs:" + QString::number(this->recs[3], '.', 8) + "," + QString::number(this->recs[4], '.', 8) + "," + QString::number(this->recs[5], '.', 8) + "\n";
    str = ui->textEdit->toPlainText() + str;
    ui->textEdit->setText(str);
}
