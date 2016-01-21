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

#include "CVTools.h"

static QVector<QRgb> colorTable;

QImage CVTools::Mat2QImage(const Mat& mat)
{
    QImage img;

    if(mat.type()==CV_8UC1){
        if(colorTable.empty()){
            for (int i=0; i<256; i++)
                colorTable.push_back(qRgb(i,i,i));
        }
        img = QImage((const unsigned char *)(mat.data), mat.cols, mat.rows,
                mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }else if(mat.type()==CV_8UC3){
        cvtColor(mat, mat, CV_BGR2RGB);
        img = QImage((const unsigned char *)(mat.data), mat.cols, mat.rows,
                mat.step, QImage::Format_RGB888);
    } else {
        img = QImage((const unsigned char *)(mat.data), mat.cols, mat.rows,
                mat.step, QImage::Format_RGB888);
    }
    return img;
}



// Check if there is motion in the result matrix
// count the number of changes and return.
inline int CVTools::detectMotion(const Mat & motion, Mat & result, Mat & result_cropped,
                 int x_start, int x_stop, int y_start, int y_stop,
                 int max_deviation,
                 Scalar & color)
{
    // calculate the standard deviation
    Scalar mean, stddev;
    meanStdDev(motion, mean, stddev);
    // if not to much changes then the motion is real (neglect agressive snow, temporary sunlight)
    if(stddev[0] < max_deviation)
    {
        int number_of_changes = 0;
        int min_x = motion.cols, max_x = 0;
        int min_y = motion.rows, max_y = 0;

        // loop over image and detect changes
        for(int j = y_start; j < y_stop; j+=2){ // height
            for(int i = x_start; i < x_stop; i+=2){ // width
                // check if at pixel (j,i) intensity is equal to 255
                // this means that the pixel is different in the sequence
                // of images (prev_frame, current_frame, next_frame)
                int val = static_cast<int>(motion.at<uchar>(j,i));
                if(val == 255)
                {
                    number_of_changes++;
                    if(min_x>i) min_x = i;
                    if(max_x<i) max_x = i;
                    if(min_y>j) min_y = j;
                    if(max_y<j) max_y = j;
                }
            }
        }
        if(number_of_changes){
            //check if not out of bounds
            if(min_x-10 > 0) min_x -= 10;
            if(min_y-10 > 0) min_y -= 10;
            if(max_x+10 < result.cols-1) max_x += 10;
            if(max_y+10 < result.rows-1) max_y += 10;
            // draw rectangle round the changed pixel
            Point x(min_x,min_y);
            Point y(max_x,max_y);
            Rect rect(x,y);
            Mat cropped = result(rect);
            cropped.copyTo(result_cropped);
            rectangle(result,rect,color,1);
        }
        return number_of_changes;
    }
    return 0;
}
