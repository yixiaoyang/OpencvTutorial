/*
 * (C) Copyright 2013-2015 Gaoee. All rights reserved.
 *
 * @brief
 * @file    MainWindow.h
 * @version 1.0
 * @author  Leon
 * @note
 *      -Create by Leon<hityixiaoyang@gmail.com> on 2016-1-20
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ObjDetectThread.h"
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void slot_procImageOrg(QImage img);
    void slot_procImageBkg(QImage img);
    void slot_procImageFr(QImage img);

private:
    Ui::MainWindow *ui;

    ObjDetectThread objDetectThread;
};

#endif // MAINWINDOW_H
