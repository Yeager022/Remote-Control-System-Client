#include "myresv.h"
#include "clientwidget.h"


myResv::myResv(QObject *parent) : QThread(parent)
{
    //初始化
    pClient = (ClientWidget*)parent;
    min = 2*sizeof(qint64);
    fileMin = 3*sizeof(qint64) + sizeof(QString);
    dataSize = 0;
    cmd = 0;
    buf = 0;
}

void myResv::run()
{
    connect(pClient->tcpSocket, &QTcpSocket::readyRead, [=](){
       stringSwitch();

    });
}

//将字符串恢复
void myResv::stringSwitch()
{
    //初始化
    dataSize = 0;
    buf = 0;
    cmd = 0;

    buf = pClient->tcpSocket->readAll();
    m_buffer.append(buf);
    unsigned int total = m_buffer.size();

    while(total)
    {
        QDataStream packet(m_buffer);
        packet.setVersion(QDataStream::Qt_5_14);
        if(total < min)
        {
            break;
        }
        packet >> dataSize >> cmd;
        if(total < dataSize)//数据长度不够
        {
            break;
        }
        qDebug() << "头部初始化完毕！";
        qDebug() << dataSize;
        qDebug() << cmd;

        switch (cmd)
        {
        case 0:
        {
            break;
        }
        case -1://心跳触发
        {
            QByteArray screenDetails = m_buffer.mid(min,dataSize-min);
            str = QString(screenDetails);
            if(str == NULL)
            {
                qDebug() << "接收分辨率失败";
                return;
            }
            qDebug() << "开始触发心跳";
            emit heart_Start();
            break;
        }
        case -2://心跳接收
        {
            qDebug() << "接收心跳";
            emit heart_Resv();
            break;
        }
        case 1://图片
        {
            qDebug() << "接收图片";
            QByteArray data = m_buffer.mid(min,dataSize-min);
            QString str = QString(data);
            if(str == NULL)
            {
                qDebug() << "转换失败";
                return;
            }
            QByteArray byte_array = QByteArray::fromBase64(str.toLocal8Bit());
            QDataStream data_stream(&byte_array,QIODevice::ReadOnly);
            data_stream >> pClient->pixmap;
            qDebug() << "转换成功";
            emit show();
            break;
        }


        case 2://文件
        {
            name = m_buffer.mid(min, dataSize-min);
            unsigned int total = name.size();
            while(total)
            {
                QDataStream packet(name);
                packet.setVersion(QDataStream::Qt_5_14);
                packet >> Size >> fileName;
                qDebug() << "文件名长度为：" << Size;
                if(total < Size)
                {
                    break;
                }

                qDebug()<<"收到文件: " << fileName;
                qDebug()<<"文件大小为： " << dataSize;

                file.setFileName(fileName);
                //打开文件
                bool isOK = file.open(QIODevice::WriteOnly);
                if(false == isOK)
                {
                    qDebug() << "打开错误";
                    break;
                }

                QByteArray data = m_buffer.mid(min+Size, dataSize-min-Size);
                file.write(data);
                file.close();
                qDebug() << "文件接收完成！";
                emit finish();
                break;
            }

            break;
        }

        case 3: //聊天信息
        {
            qDebug() << "接收聊天信息";
            QByteArray data = m_buffer.mid(min, dataSize - min);
            QString str = QString(data);
            if (str == NULL)
            {
                qDebug() << "转换失败";
                return;
            }
            qDebug() << "转换成功";
            pClient->message = str;
            emit chat();
            break;
        }

        }

        //缓存多余数据
        buf = m_buffer.right(total - dataSize);
        total = buf.size();
        //更新多余数据
        m_buffer = buf;

    }


}

