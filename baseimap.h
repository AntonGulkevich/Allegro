#ifndef BaseImap_H
#define BaseImap_H

#include <QObject>
#include <QTimer>
#include <imap.h>
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


class BaseImap : public QObject
{
    Q_OBJECT
    Imap* protocol;
    int countReal;
    QTimer *timer;
    QString login;
    QString password;
    QString host;
    int port;
    QSsl::SslProtocol sslProtolol;
    int countTemp;
public:
    BaseImap(QString& login_,QString& password_,QString& host_,int port_,QSsl::SslProtocol sslProtolol_);
    ~BaseImap();
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

#endif // BaseImap_H
