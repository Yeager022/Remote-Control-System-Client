#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QTimer>
#include <QPainter>
#include <Qscreen>
#include <QPixmap>
#include <QImage>
#include <QThread>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QHostAddress>
#include <QPalette>
#include <QDateTime>
#include <QThread>
#include <QDir>
#include <QMessageBox>
#include "myresv.h"
#include "the_switch.h"
#include "heart_beat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);

    QTcpSocket *tcpSocket;
    QString ip;//ip
    qint16 port;//端口

    qint64 n = 1;//用于截图保存命名

    //记录鼠标左右键，用于传输
    QString mouse;
    int x = 0;
    int y = 0;
    float screenX = 1920;//分辨率
    float screenY = 1080;//分辨率

    //图片接收
    QPixmap pixmap;
//    QImage img;
    QString data;

    myResv *thread;//线程对象
    The_Switch *thread2;//线程对象
    Heart_Beat *thread3;//线程对象

    //文件
    QFile file;
    QStringList dir;
    QString filePath;//文件路径
    QString fileName; //文件名
    qint64 fileSize; //文件大小
    qint64 sendSize; //已发送文件大小
    qint64 dataSize;//数据头长度
    qint64 Size;
    qint64 cmd;//类型
    QByteArray temp;//用于暂存
    QByteArray temp2;
    int z;//用于限制显示重连

    //聊天信息
    QString message;

    void initialize();//初始化

    void state();//连接时和断开时

    //关闭窗口
    void closeEvent(QCloseEvent *event);


    //鼠标事件
    //鼠标单击
    void mousePressEvent(QMouseEvent *ev);
    //鼠标双击
    void mouseDoubleClickEvent(QMouseEvent *ev);

    //鼠标抬起
    void mouseReleaseEvent(QMouseEvent *ev);

    //鼠标移动
    void mouseMoveEvent(QMouseEvent *ev);

    //通过event事件分发器，拦截 鼠标按下事件
    bool event(QEvent *e);

public slots:

    void stopThread();//结束线程

    void myPicture();//显示图片

    void finished();//提示文件接收

    void heart_First();//收到心跳请求后，第一次发送

    void heart_Second();//收到确认后操作

    void chatMessage();//收到聊天信息

private slots:
    void on_btn_Begin_clicked();

    void on_btn_End_clicked();

    void on_btn_Send_clicked();

    void on_btn_Catch_clicked();

    void on_btn_Search_clicked();

    void on_btn_Message_clicked();

signals:
    void mousePress();
    void heart_Back();//收到确认

private:
    Ui::ClientWidget *ui;


};
#endif // CLIENTWIDGET_H
