#ifndef BASEPOP3_H
#define BASEPOP3_H

#include <QObject>
#include <QTimer>
#include <pop3.h>
#include <message.h>
#include "quotedprintable.h"
#include <qtextcodec.h>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QDateTime>
#include <QLocale>


class BasePop3 : public QObject
{
    Q_OBJECT

    Pop3* protocol;
    int countReal;
    QTimer *timer;
    QString login;
    QString password;
    QString host;
    int port;
    QSsl::SslProtocol sslProtolol;
public:
    BasePop3(QString& login_,QString& password_,QString& host_,int port_,QSsl::SslProtocol sslProtolol_);
    ~BasePop3();
    void parsTop(Message& message,QByteArray& responseArr);
    void parsingPart(Message& msg,QByteArray response);
    void parsingMessage(Message& msg,QByteArray message);
signals:
    void Error(QString Message);
    void MessageOK(Message message);
    void MessageTopOK(Message top);

public slots:
    void run();
    void updateTCP();
    void getMessage(int number);
    void deleteMessage(int number);
    void get20Message();
    void update();
};

#endif // BASEPOP3_H
