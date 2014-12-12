#ifndef POP3_H
#define POP3_H

#include <QObject>
#include <QSslSocket>
#include <QSsl>
#include <QString>
#include <QByteArray>
#include <QRegExp>

class Pop3
{
    QString login;
    QString password;
    QString host;
    int port;
    QSslSocket* socket;
    QSsl::SslProtocol sslProtolol;
public:
    Pop3(QString& login_,QString& password_,QString& host_,int port_,QSsl::SslProtocol sslProtolol_);
    ~Pop3();
    bool connectToHost();
    bool sendUser();
    bool sendPass();
    void sendQuit();
    bool sendDele(int number);
    void sendNoop();
    QByteArray sendList();
    QByteArray sendRetr(int number);
    QByteArray sendTop(int number);
    QByteArray processingRequest(QString request);
};

#endif // POP3_H
