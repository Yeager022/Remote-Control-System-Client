#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#ifndef HEART_BEAT_H
#define HEART_BEAT_H

#include <QThread>
#include <QTimer>
#include <QDebug>

class Heart_Beat : public QThread
{
    Q_OBJECT
public:
    explicit Heart_Beat(QObject *parent = nullptr);
    ~Heart_Beat();

    void beat();

public slots:
    void heart_Start();
    void heart_Reset();

private:
    int count = 0;
    QTimer *timer;

signals:
    void dead();
    void heart_Wrong();
    void heart_Request();


};

#endif // HEART_BEAT_H
