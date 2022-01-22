#include "heart_beat.h"

Heart_Beat::Heart_Beat(QObject *parent) : QThread(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        if(count > 29)//若15秒未收到响应，则会触发
        {
            count = 0;
            timer->stop();
            emit heart_Wrong();
            return;
        }
        count++;
        emit heart_Request();
    });

}

void Heart_Beat::heart_Start()
{
    timer->start(500);
}

void Heart_Beat::heart_Reset()
{
    count = 0;//清零
    qDebug() << "TCP正常在线";
}

Heart_Beat::~Heart_Beat()
{
    delete timer;
}
