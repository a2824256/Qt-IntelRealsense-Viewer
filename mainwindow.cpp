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
