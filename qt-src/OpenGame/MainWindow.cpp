/*
 * (C) Copyright 2013-2015 Gaoee. All rights reserved.
 *
 * @brief
 * @file    MainWindow.cpp
 * @version 1.0
 * @author  Leon
 * @note
 *      -Create by Leon<hityixiaoyang@gmail.com> on 2016-1-20
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objDetectThread.setDirFilter("/devel/git/osc/opencv-test/files/egtest01/", "*.jpg");

    QObject::connect(&objDetectThread,SIGNAL(procImageBkg(QImage)),this,SLOT(slot_procImageBkg(QImage)));
    QObject::connect(&objDetectThread,SIGNAL(procImageOrg(QImage)),this,SLOT(slot_procImageOrg(QImage)));
    QObject::connect(&objDetectThread,SIGNAL(procImageFr(QImage)),this,SLOT(slot_procImageFr(QImage)));

}

MainWindow::~MainWindow()
{
    if(objDetectThread.isRunning()){
        objDetectThread.stop();
        objDetectThread.wait();
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(objDetectThread.isRunning()){
        objDetectThread.stop();
    }else{
        objDetectThread.ifStop = false;
        objDetectThread.start();
    }
}

void MainWindow::slot_procImageOrg(QImage img)
{
}

void MainWindow::slot_procImageBkg(QImage img)
{
    if(img.isNull()){
        return ;
    }
    ui->label_bkg->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::slot_procImageFr(QImage img)
{
    if(img.isNull()){
        return ;
    }
    ui->label_fr->setPixmap(QPixmap::fromImage(img));
}
