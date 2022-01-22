#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#ifndef MYSEND_H
#define MYSEND_H

#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QTcpSocket>
#include <QDataStream>
#include <QMessageBox>

class ClientWidget;
class The_Switch : public QThread
{
    Q_OBJECT
public:
    explicit The_Switch(QObject *parent = nullptr);

    qint64 i = 0;

    QString res;

    QByteArray buf;

    qint64 headSize = 0;//数据头长度

    qint64 cmd;//类型

    QByteArray temp;//用于暂存

    qint64 isStart;//判断头部发送

public slots:
    void send_Mouse();

protected:
    void run();

private:
    ClientWidget *pClient;


signals:
//    void isDone();

};

#endif // MYSEND_H
