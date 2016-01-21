/*
 * (C) Copyright 2013-2015 Gaoee. All rights reserved.
 *
 * @brief
 * @file
 * @version 1.0
 * @author  Leon
 * @note
 *      -Create by Leon<hityixiaoyang@gmail.com> on 2016-1-20
 */

#include "ObjDetectThread.h"
#include <QDebug>
#include <QDirIterator>

#include "CVTools.h"
ObjDetectThread::ObjDetectThread(): QThread()
{
    ifStop = false;
}

#if 0
void ObjDetectThread::run()
{
    qDebug() << "thread runnig";
    ///devel/git/osc/opencv-test/files/egtest01/frame00000.jpg
    ///devel/git/osc/opencv-test/files/egtest01/frame01820.jpg

    //QDirIterator it(dirStr, QStringList() << filterStr, QDir::Files, QDirIterator::Subdirectories);
    uint count = 0;

    // 8UC1(Gray)
    Mat frMat;
    Mat bkgMat;
    // 8UC3
    Mat frameMat;

    // Erode kernel
    Mat kernel_ero = getStructuringElement(MORPH_RECT, Size(2,2));

#if 0
    for(unsigned int index = 0; (!ifStop) && (index <= 1820); index++){
        QString fname;
        fname.sprintf("frame%05d.jpg",index);
        QString filename = dirStr+fname;

        // 8UC3
        frameMat = imread(filename.toStdString(),CV_LOAD_IMAGE_COLOR);
#else
    VideoCapture capture("/devel/git/osc/opencv-test/files/768x576.avi");
    if(!capture.isOpened()){
        qWarning() << "open video failed: " << capture.isOpened();
        return ;
    }

    while(!ifStop){
        if(!capture.read(frameMat)){
            return ;
        }

#endif

        if(count == 0)
        {
            // 第一帧, 转化成单通道图像再处理
            cvtColor(frameMat, frMat, CV_BGR2GRAY);
            cvtColor(frameMat, bkgMat, CV_BGR2GRAY);
            // 直方图均衡化
            //equalizeHist( frMat, frMat );
            //equalizeHist( bkgMat, bkgMat );
        }
        else{
            // 更新前景
            cvtColor(frameMat, frMat, CV_BGR2GRAY);
            // 直方图均衡化
            //equalizeHist( frMat, frMat );
            /* Take the difference from the current frame to the moving average */
            absdiff(frMat, bkgMat, frMat);
            //高斯滤波，平滑图像
            //cvSmooth(frMat, frMat, CV_GAUSSIAN, 3, 0, 0);
            /* Convert the image to black and white */
            threshold(frMat, frMat, 30, 255.0, CV_THRESH_BINARY);
            // 腐蚀去噪
            //erode(frMat, frMat, kernel_ero);
            //更新背景
            cvtColor(frameMat, bkgMat, CV_BGR2GRAY);
            // 背景直方图均衡化
            //equalizeHist( bkgMat, bkgMat );
        }

        //emit procImageOrg(QImage(filename));
        //if(!(frameMat).empty())
        //    emit procImageOrg(CVTools::Mat2QImage(frameMat));
        //if(!bkgMat.empty())
        //    emit procImageBkg(CVTools::Mat2QImage(bkgMat));
        if(!frMat.empty())
            emit procImageFr(CVTools::Mat2QImage(frMat));

        count++;
    }

    qDebug() << "thread stoped";
}
#else
void ObjDetectThread::run()
{
    uint count = 0;
    // 8UC1(Gray)
    Mat frMat;
    Mat bkgMat;
    Mat nxtMat;
    Mat diffMat1;
    Mat diffMat2;

    // 8UC3
    Mat frameMat;
    // Erode kernel
    Mat kernel_ero = getStructuringElement(MORPH_RECT, Size(2,2));

    VideoCapture capture("/devel/git/osc/opencv-test/files/768x576.avi");
    if(!capture.isOpened()){
        qWarning() << "open video failed: " << capture.isOpened();
        return ;
    }

    while(!ifStop){
        if(!capture.read(frameMat)){
            return ;
        }

        if(count == 0)
        {
            // 第一帧, 转化成单通道图像再处理
            cvtColor(frameMat, bkgMat, CV_BGR2GRAY);

            if(!capture.read(frameMat)){
                return ;
            }
            cvtColor(frameMat, frMat, CV_BGR2GRAY);

            if(!capture.read(frameMat)){
                return ;
            }
            cvtColor(frameMat, nxtMat, CV_BGR2GRAY);
        }
        else{
            frMat = nxtMat.clone();
            cvtColor(frameMat, nxtMat, CV_BGR2GRAY);

            // 直方图均衡化
            //equalizeHist( frMat, frMat );

            /* Take the difference from the current frame to the moving average */
            absdiff(nxtMat, bkgMat, diffMat1);
            absdiff(nxtMat, frMat, diffMat2);
            bitwise_and(diffMat1, diffMat2, diffMat1);
            //高斯滤波，平滑图像
            //cvSmooth(frMat, frMat, CV_GAUSSIAN, 3, 0, 0);

            /* Convert the image to black and white */
            threshold(diffMat2, diffMat2, 50, 255.0, CV_THRESH_BINARY);
            // 腐蚀去噪
            // erode(diffMat1, diffMat1, kernel_ero);

            //更新背景
            bkgMat = frMat.clone();

            emit procImageBkg(CVTools::Mat2QImage(diffMat2));
            emit procImageFr(CVTools::Mat2QImage(diffMat1));
        }

        count++;
    }
}
#endif

void ObjDetectThread::stop()
{
    ifStop = true;
}

void ObjDetectThread::setDirFilter(QString dir, QString filter)
{
    this->dirStr = dir;
    this->filterStr = filter;
}
