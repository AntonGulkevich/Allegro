#ifndef Imap_H
#define Imap_H

#include <QObject>
#include <QSslSocket>
#include <QSsl>
#include <QString>
#include <QByteArray>
#include <QRegExp>
#include <QDebug>

class Imap
{
    QString login;
    QString password;
    QString host;
    int port;
    QSslSocket* socket;
    QSsl::SslProtocol sslProtolol;
    int identificator;

public:
    Imap(QString& login_,QString& password_,QString& host_,int port_,QSsl::SslProtocol sslProtolol_);
    ~Imap();
    bool connectToHost();
    bool sendLogin();
    void sendLogout();
    QString identificatorCommand();
    QByteArray sendSelectInbox();
    QByteArray sendFetchHead(int number);
    QByteArray sendFetchMessage(int number);
    bool sendDele(int number);
    void sendNoop();
    QByteArray sendList();
    QByteArray processingRequest(QString request);
};

#endif // Imap_H
