/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWidget
{
public:
    QLabel *label;
    QPushButton *btn_End;
    QPushButton *btn_Begin;
    QTextEdit *textEditShow;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditPort;
    QLineEdit *lineEditIP;
    QLabel *label_Show;
    QPushButton *btn_Send;
    QPushButton *btn_Catch;
    QLabel *label_4;
    QLineEdit *lineEditPhoto;
    QPushButton *btn_Search;
    QTextEdit *textEditChat;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btn_Message;

    void setupUi(QWidget *ClientWidget)
    {
        if (ClientWidget->objectName().isEmpty())
            ClientWidget->setObjectName(QString::fromUtf8("ClientWidget"));
        ClientWidget->resize(1440, 900);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ClientWidget->sizePolicy().hasHeightForWidth());
        ClientWidget->setSizePolicy(sizePolicy);
        ClientWidget->setMinimumSize(QSize(1440, 900));
        ClientWidget->setMaximumSize(QSize(1440, 900));
        label = new QLabel(ClientWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 10, 311, 101));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(30);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        btn_End = new QPushButton(ClientWidget);
        btn_End->setObjectName(QString::fromUtf8("btn_End"));
        btn_End->setGeometry(QRect(1170, 20, 131, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(12);
        btn_End->setFont(font1);
        btn_Begin = new QPushButton(ClientWidget);
        btn_Begin->setObjectName(QString::fromUtf8("btn_Begin"));
        btn_Begin->setGeometry(QRect(1040, 20, 111, 31));
        btn_Begin->setFont(font1);
        textEditShow = new QTextEdit(ClientWidget);
        textEditShow->setObjectName(QString::fromUtf8("textEditShow"));
        textEditShow->setGeometry(QRect(1300, 170, 131, 471));
        textEditShow->setReadOnly(true);
        label_2 = new QLabel(ClientWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 40, 121, 31));
        label_2->setFont(font1);
        label_3 = new QLabel(ClientWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 10, 121, 31));
        label_3->setFont(font1);
        lineEditPort = new QLineEdit(ClientWidget);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));
        lineEditPort->setGeometry(QRect(630, 20, 374, 21));
        lineEditIP = new QLineEdit(ClientWidget);
        lineEditIP->setObjectName(QString::fromUtf8("lineEditIP"));
        lineEditIP->setGeometry(QRect(630, 50, 374, 21));
        label_Show = new QLabel(ClientWidget);
        label_Show->setObjectName(QString::fromUtf8("label_Show"));
        label_Show->setGeometry(QRect(10, 130, 1280, 720));
        sizePolicy.setHeightForWidth(label_Show->sizePolicy().hasHeightForWidth());
        label_Show->setSizePolicy(sizePolicy);
        label_Show->setMinimumSize(QSize(1280, 720));
        label_Show->setMaximumSize(QSize(1280, 720));
        label_Show->setFrameShape(QFrame::Panel);
        label_Show->setFrameShadow(QFrame::Plain);
        btn_Send = new QPushButton(ClientWidget);
        btn_Send->setObjectName(QString::fromUtf8("btn_Send"));
        btn_Send->setGeometry(QRect(1170, 70, 111, 31));
        btn_Send->setFont(font1);
        btn_Catch = new QPushButton(ClientWidget);
        btn_Catch->setObjectName(QString::fromUtf8("btn_Catch"));
        btn_Catch->setGeometry(QRect(1040, 70, 111, 31));
        btn_Catch->setFont(font1);
        label_4 = new QLabel(ClientWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(490, 70, 141, 31));
        label_4->setFont(font1);
        lineEditPhoto = new QLineEdit(ClientWidget);
        lineEditPhoto->setObjectName(QString::fromUtf8("lineEditPhoto"));
        lineEditPhoto->setGeometry(QRect(630, 80, 281, 21));
        btn_Search = new QPushButton(ClientWidget);
        btn_Search->setObjectName(QString::fromUtf8("btn_Search"));
        btn_Search->setGeometry(QRect(920, 80, 41, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        btn_Search->setFont(font2);
        textEditChat = new QTextEdit(ClientWidget);
        textEditChat->setObjectName(QString::fromUtf8("textEditChat"));
        textEditChat->setGeometry(QRect(1300, 680, 131, 131));
        textEditChat->setFont(font1);
        textEditChat->setReadOnly(false);
        label_5 = new QLabel(ClientWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1320, 640, 81, 31));
        label_5->setFont(font1);
        label_6 = new QLabel(ClientWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1320, 130, 81, 31));
        label_6->setFont(font1);
        btn_Message = new QPushButton(ClientWidget);
        btn_Message->setObjectName(QString::fromUtf8("btn_Message"));
        btn_Message->setGeometry(QRect(1300, 820, 131, 28));
        btn_Message->setFont(font1);

        retranslateUi(ClientWidget);

        QMetaObject::connectSlotsByName(ClientWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientWidget)
    {
        ClientWidget->setWindowTitle(QCoreApplication::translate("ClientWidget", "ServerWidget", nullptr));
        label->setText(QCoreApplication::translate("ClientWidget", "\350\277\234\347\250\213\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        btn_End->setText(QCoreApplication::translate("ClientWidget", "\346\265\213\350\257\225\345\277\203\350\267\263\351\207\215\350\277\236", nullptr));
        btn_Begin->setText(QCoreApplication::translate("ClientWidget", "\345\274\200\345\247\213\350\277\236\346\216\245", nullptr));
        label_2->setText(QCoreApplication::translate("ClientWidget", "\346\234\215\345\212\241\345\231\250IP\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("ClientWidget", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditPort->setText(QCoreApplication::translate("ClientWidget", "8888", nullptr));
        lineEditIP->setText(QCoreApplication::translate("ClientWidget", "127.0.0.1", nullptr));
        label_Show->setText(QString());
        btn_Send->setText(QCoreApplication::translate("ClientWidget", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        btn_Catch->setText(QCoreApplication::translate("ClientWidget", "\344\270\200\351\224\256\346\210\252\345\233\276", nullptr));
        label_4->setText(QCoreApplication::translate("ClientWidget", "\346\210\252\345\233\276\344\277\235\345\255\230\344\275\215\347\275\256\357\274\232", nullptr));
        lineEditPhoto->setText(QCoreApplication::translate("ClientWidget", "\350\257\267\345\205\210\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        btn_Search->setText(QCoreApplication::translate("ClientWidget", "\346\265\217\350\247\210", nullptr));
        label_5->setText(QCoreApplication::translate("ClientWidget", "\345\217\221\351\200\201\344\277\241\346\201\257", nullptr));
        label_6->setText(QCoreApplication::translate("ClientWidget", "\351\200\232\347\237\245\345\214\272\345\237\237", nullptr));
        btn_Message->setText(QCoreApplication::translate("ClientWidget", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientWidget: public Ui_ClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
