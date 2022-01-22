#include "the_switch.h"
#include "clientwidget.h"

The_Switch::The_Switch(QObject *parent) : QThread(parent)
{
    pClient = (ClientWidget*)parent;

}

void The_Switch::run()
{
    connect(pClient, SIGNAL(mousePress()), this, SLOT(send_Mouse()));
}

void The_Switch::send_Mouse()
{
    //初始化
    headSize = 0;
    cmd = 0;
    temp = 0;
    buf = 0;
    QString res = pClient->mouse;//获取鼠标左右键
    QByteArray buf = res.toUtf8();

    QDataStream output(&temp,QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_14);
    headSize = buf.size();
    qDebug() << headSize;
    //2标明为鼠标单击
    cmd = 2;

    output << qint64(headSize) << qint64(cmd);
    headSize += temp.size();
    output.device()->seek(0);
    output << headSize;
    qint64 len = pClient->tcpSocket->write(temp);
    if(len > 0)//头部信息发送成功
    {
        qDebug() << "头部信息发送成功！";
        for(int i = 0; i < 10000; i++);
    }
    temp.resize(0);//清空临时存储的包头
    temp = buf;//放入数据
    pClient->tcpSocket->write(temp);
    temp.resize(0);//清空
    qDebug() << i++;
}
