#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    //初始化
    initialize();

    //tcp连接和断开时的操作
    state();

}

//初始化
void ClientWidget::initialize()
{
    ui->setupUi(this);
    ui->btn_End->setEnabled(false);
    ui->btn_Send->setEnabled(false);
    ui->btn_Message->setEnabled(false);
    ui->btn_Catch->setEnabled(false);
    tcpSocket = NULL;
    setWindowTitle("远程控制系统");

    //分配空间， 指定父对象
    tcpSocket = new QTcpSocket(this);
}

//连接和断开
void ClientWidget::state()
{
    connect(tcpSocket, &QTcpSocket::connected, [=](){
        ui->textEditShow->setText("正在等待服务端建立连接...");

        ui->btn_End->setEnabled(true);
        ui->btn_Begin->setEnabled(false);
        ui->btn_Send->setEnabled(true);
        ui->btn_Message->setEnabled(true);
        ui->btn_Catch->setEnabled(true);

        //分配线程空间
        thread = new myResv(this);
        thread2 = new The_Switch(this);
        thread3 = new Heart_Beat(this);

        //启动线程
        thread->start();
        thread2->start();
        thread3->start();

        connect(thread, SIGNAL(show()), this, SLOT(myPicture()));
        connect(thread, SIGNAL(finish()), this, SLOT(finished()));
        connect(thread, SIGNAL(heart_Start()), this, SLOT(heart_First()));
        connect(thread, SIGNAL(heart_Resv()), this, SLOT(heart_Second()));
        connect(thread, SIGNAL(chat()), this, SLOT(chatMessage()));

    });

    //断开连接
    connect(tcpSocket, &QTcpSocket::disconnected, [=](){
        ui->textEditShow->append("与服务器断开连接！");

        //关闭线程，下次连接需要重新开启
        stopThread();

        //断开连接
        tcpSocket->disconnectFromHost();

        ui->btn_Begin->setEnabled(true);
        ui->btn_End->setEnabled(false);
        ui->btn_Send->setEnabled(false);
        ui->btn_Message->setEnabled(false);
        ui->btn_Catch->setEnabled(false);


    });
}

//结束线程
void ClientWidget::stopThread()
{
    if(thread->isRunning())
    {
        //停止线程
        thread->quit();

        //等待线程处理完手头工作
        thread->wait();
    }
    if(thread2->isRunning())
    {
        //停止线程
        thread2->quit();

        //等待线程处理完手头工作
        thread2->wait();
    }
    if(thread3->isRunning())
    {
        //停止线程
        thread3->quit();

        //等待线程处理完手头工作
        thread3->wait();
    }

}

void ClientWidget::on_btn_Begin_clicked()
{
    //获取服务器IP和端口
    ip = ui->lineEditIP->text();
    port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(ip, port);

    //
}

void ClientWidget::on_btn_End_clicked()
{
    //关闭线程，下次连接需要重新开启
    stopThread();
    //主动断开连接
    tcpSocket->disconnectFromHost();

}

//选择截图存放路径
void ClientWidget::on_btn_Search_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, "请选择文件路径...", "./");
    if (!file_path.isEmpty())
    {
        ui->lineEditPhoto->setText(file_path);
    }

}

//一键截图
void ClientWidget::on_btn_Catch_clicked()
{
    QString file_path = ui->lineEditPhoto->text();
    if (file_path.isEmpty())
    {
        //路径为空，不可保存
        QMessageBox::critical(NULL, "错误", "请先选择路径！");
        return;
    }
    QString num = QString::number(n, 10);
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui->label_Show->winId());
    file_path = file_path + "/Screen" + num +".jpg";
    p.save(file_path, "jpg");
    n += 1;

}

//聊天功能
void ClientWidget::on_btn_Message_clicked()
{
    //初始化
    dataSize = 0;
    cmd = 0;
    temp = 0;
    QString message = ui->textEditChat->toPlainText();
    QByteArray buf = message.toUtf8();

    QDataStream output(&temp, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_14);
    dataSize = buf.size();
    qDebug() << dataSize;
    cmd = 3;//3标明为聊天信息

    output << qint64(dataSize) << qint64(cmd);
    dataSize += temp.size();
    output.device()->seek(0);
    output << dataSize;
    qint64 len = tcpSocket->write(temp);
    if (len > 0)//头部信息发送成功
    {
        for (int i = 0; i < 10000; i++);
        ui->textEditShow->append("我：");
        ui->textEditShow->append(message);
        temp.resize(0);
    }
    else
    {
        QMessageBox::critical(NULL, "错误", "头部信息发送失败！");
        return;
    }
    temp = buf;//放入数据
    tcpSocket->write(temp);
    temp.resize(0);//清空

    ui->textEditChat->setText(NULL);

}

//聊天信息接收
void ClientWidget::chatMessage()
{
    ui->textEditShow->append("服务端:");
    ui->textEditShow->append(message);
}

//发送文件
void ClientWidget::on_btn_Send_clicked()
{
    dir = QFileDialog::getOpenFileNames(this,"open","../");
    if(false == dir.isEmpty())//如果选择文件路径有效
    {
        for(int i = 0; i < dir.size(); ++i)
        {
            filePath = dir.at(i);
            fileName.clear();
            fileSize = 0;
            //获取文件信息
            QFileInfo info(filePath);
            fileName = info.fileName();
            fileSize = info.size();

            sendSize = 0;

            //只读方式打开文件
            //指定文件名
            file.setFileName(filePath);
            //打开文件
            bool isOK = file.open(QIODevice::ReadOnly);
            if(false == isOK)
            {
                QMessageBox::critical(NULL, "错误","只读方式打开失败！");
                return;
            }

            //提示打开文件的路径
            ui->textEditShow->append(filePath);

            //初始化
            dataSize = 0;
            cmd = 0;
            temp = 0;
            temp2 = 0;
            Size = 0;

            QDataStream output(&temp,QIODevice::WriteOnly);
            output.setVersion(QDataStream::Qt_5_14);
            dataSize = fileSize;
            qDebug() << dataSize;
            cmd = 1;

            QDataStream name(&temp2,QIODevice::WriteOnly);
            name.setVersion(QDataStream::Qt_5_14);
            name << qint64(Size) << QString(fileName);
            Size += temp2.size();
            name.device()->seek(0);
            name << Size;


            output<< qint64(dataSize)<< qint64(cmd);//以流方式写入
            dataSize += temp.size();//上一行的长度
            dataSize += Size;
            output.device()->seek(0);//回到数据流的开始位置
            output << dataSize;
            qint64 len = tcpSocket->write(temp);
            if(len > 0)//头部信息发送成功
            {
                for(int i = 0; i< 10000; i++);
                ui->textEditShow->append("文件正在发送，请稍等...");
                temp.resize(0);
            }
            else
            {
                QMessageBox::critical(NULL, "错误","头部信息发送失败！");
                file.close();
                return;
            }


            qint64 len2 = 0;
            len2 = tcpSocket->write(temp2);
            if(len2 > 0)
            {
                for(int i = 0; i< 10000; i++);
                temp2.resize(0);
            }
            else
            {
                QMessageBox::critical(NULL, "错误", "文件名发送失败！");
                file.close();
                return;
            }

            //发送数据
            temp = file.readAll();
            tcpSocket->write(temp);
            tcpSocket->write(temp2);
            temp.resize(0);
            temp2.resize(0);

        }
    }
    ui->textEditShow->append("文件发送完毕！");
    file.close();

}

//提示文件接收
void ClientWidget::finished()
{
    QString str1 = QString("'%1'接收完成!").arg(thread->fileName);
    QString str2 = QString("大小为：%1KB").arg(thread->dataSize/1024);
    ui->textEditShow->append(str1);
    ui->textEditShow->append(str2);
}

//图片显示
void ClientWidget::myPicture()
{
    //显示图片
    int width = ui->label_Show->width();
    int height = ui->label_Show->height();
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    if(pixmap.isNull())
    {
        qDebug() << "图片为空！";
        QMessageBox::critical(NULL, "错误", "图片接收失败！");
        return;
    }
    ui->label_Show->setPixmap(pixmap);
}

//心跳处理
void ClientWidget::heart_First()
{
    thread3->heart_Start();

    //接收对方分辨率
    screenX = QString(thread->str).section("##", 0, 0).toInt();
    screenY = QString(thread->str).section("##", 1, 1).toInt();
    qDebug() << "目标分辨率为： " << screenX << "*" << screenY;

    connect(thread3, &Heart_Beat::heart_Request, [=](){
        //初始化
        dataSize = 0;
        cmd = 0;
        temp = 0;

        QDataStream output(&temp,QIODevice::WriteOnly);
        output.setVersion(QDataStream::Qt_5_14);
        qDebug() << "心跳请求发出";
        cmd = -1;//-1说明为心跳消息

        output<< qint64(dataSize)<< qint64(cmd);//以流方式写入
        dataSize += temp.size();//上一行的长度
        output.device()->seek(0);//回到数据流的开始位置
        output << dataSize;
        qint64 len = tcpSocket->write(temp);
        if(len > 0)//头部信息发送成功
        {
            for(int i = 0; i< 10000; i++);
            temp.resize(0);
        }

    });

}

void ClientWidget::heart_Second()
{
    thread3->heart_Reset();//接到返回消息后，重置累计次数
    z = 0;
    connect(thread3, &Heart_Beat::heart_Wrong, [=](){
        if(tcpSocket->isOpen())
        {
            //获取服务器IP和端口
            if(z == 0)
            {
                tcpSocket->connectToHost(QHostAddress(ip), port);
                QMessageBox::information(NULL, "连接","检测到连接断开，已经尝试重连...");
                z = 1;
            }

        }
    });//若tcp未关闭检测到断开就重连
}

//关闭窗口
void ClientWidget::closeEvent(QCloseEvent *event)
{
    if(tcpSocket->isOpen())
    {
        QMessageBox msg;
        msg.setText(tr("警告"));
        msg.setInformativeText(tr("确定关闭程序吗？如果有文件正在传输，请确认传输完毕后再关闭程序"));
        msg.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Cancel);
        int ret = msg.exec();
        switch (ret)
        {
        case QMessageBox::Yes:
            //主动断开连接
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        }
    }

}





//鼠标操作
//鼠标单击
void ClientWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        //x 和 y是相对控件的坐标， globalX 和globalY是相对屏幕的坐标
        QString str = QString("鼠标左键单击，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;

    }

    if(ev->button() == Qt::RightButton)
    {
        //x 和 y是相对控件的坐标， globalX 和globalY是相对屏幕的坐标
        QString str = QString("鼠标右键单击，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
    }
}

//鼠标双击
void ClientWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    //左键才打印双击
    if(ev->button() == Qt::LeftButton)
    {
        QString str = QString("鼠标双击，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
    }

}

//鼠标抬起
void ClientWidget::mouseReleaseEvent(QMouseEvent *ev)
{

    QString str = QString("鼠标抬起，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
    qDebug() << str;

}

//鼠标移动
void ClientWidget::mouseMoveEvent(QMouseEvent *ev)
{
    QString str = QString("鼠标正在移动，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
    qDebug() << str;

}

bool ClientWidget::event(QEvent *e)
{
    //如果是鼠标按下事件，在event事件分发中做拦截操作
    if(e->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "鼠标事件被event拦截";
        //QEvent 是 QMouseEvent的父类，可以将e转换
        QMouseEvent * ev = static_cast<QMouseEvent *>(e);//利用C++中的类型转换方式
        //坐标等比例缩放
        x = ev->x()-10;
        if(x < 0)
        {
            x = 0;
        }
        float changeX = screenX/1280;
        qDebug() << "changex" << changeX;
        x = x*changeX;
        y = ev->y()-130;
        if(y < 0)
        {
            y = 0;
        }
        float changeY = screenY/720;
        y = y*changeY;
        qDebug() << "screenX = " << x;
        qDebug() << "screenY = " << y;
        if(ev->button() == Qt::LeftButton)
        {
            if(ev->x() >= 10 && ev->x() <= 1290 && ev->y() >= 130 && ev->y() <= 850)
            {
                mouse = QString("Left##%1##%2").arg(x).arg(y);
                emit mousePress();

                QString str = QString("鼠标左键按下，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
                qDebug() << str;
            }
        }

        if(ev->button() == Qt::RightButton)
        {
            if(ev->x() >= 10 && ev->x() <= 1290 && ev->y() >= 130 && ev->y() <= 850)
            {
                mouse = QString("Right##%1##%2").arg(x).arg(y);
                emit mousePress();

                QString str = QString("鼠标右键按下，x = %1  y = %2 globalX = %3  globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
                qDebug() << str;
            }


        }


        return true;//代表用户自己处理这个事件，不想下分发
    }

    //其他未拦截事件 交给父类处理
    return QWidget::event(e);
}

