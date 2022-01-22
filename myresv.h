#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#ifndef MYRESV_H
#define MYRESV_H

#include <QThread>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

class ClientWidget;

class myResv : public QThread
{
    Q_OBJECT
public:
    explicit myResv(QObject *parent = nullptr);

    QByteArray m_buffer;
    qint64 isStart;
    qint64 dataSize;
    qint64 cmd;
    qint64 min;
    qint64 fileMin;

    QFile file;
    QFileInfo fileInfo;
    QString fileName;
    QString fileSuffix;
    QByteArray buf;
    QByteArray name;
    qint64 Size;//文件名包头长度
    QString str;//分辨率字符串

public slots:
    void stringSwitch();

protected:
    void run();

signals:
    void show();
    void finish();
    void heart_Start();
    void heart_Resv();
    void chat();

private:
    ClientWidget *pClient;


};

#endif // MYRESV_H
