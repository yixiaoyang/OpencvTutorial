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

#ifndef CVTOOLS_H
#define CVTOOLS_H

#include <QImage>

#include <opencv2/opencv.hpp>

using namespace cv;

class CVTools
{
public:
    static QImage Mat2QImage(const Mat& image);
    static int detectMotion(const Mat &motion, Mat &result, Mat &result_cropped,
                            int x_start, int x_stop, int y_start, int y_stop,
                            int max_deviation, Scalar &color);
};

#endif // CVTOOLS_H
