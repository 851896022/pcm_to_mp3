#include "wholeminute.h"

#include <QDebug>
wholeMinute::wholeMinute(QObject *parent) : QObject(parent)
{

    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(sendSignal()));
    timer->start(800);
}

void wholeMinute::sendSignal()
{
    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();//当前的小时
    int minute = current_time.minute();//当前的分
    int second = current_time.second();//当前的秒
    int msec = current_time.msec();//当前的毫秒
    if(second==0)
    {
        int min=(hour*60)+minute;
        emit wholeMinuteSignal(min);
    }
    if(msec<810)
    {
        int sec=(hour*3600)+(minute*60)+second;
        emit wholeSecondSignal(sec);
    }

}

