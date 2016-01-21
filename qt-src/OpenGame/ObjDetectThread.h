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

#ifndef OBJDETECTTHREAD_H
#define OBJDETECTTHREAD_H

#include <QThread>
#include <QString>
#include <QImage>
#include <QObject>
class ObjDetectThread : public QThread
{
    Q_OBJECT
private:

public:
    ObjDetectThread();
    void stop();
    void setDirFilter(QString dir, QString filter);

    QString dirStr;
    QString filterStr;
    bool ifStop;

    // QThread interface
protected:
    void run() override;
signals:
    void procImageOrg(QImage img);
    void procImageBkg(QImage img);
    void procImageFr(QImage img);
};

#endif // OBJDETECTTHREAD_H
