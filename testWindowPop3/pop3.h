#ifndef POP3_H
#define POP3_H

#include <QObject>
#include <QSslSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDataStream>
#include <QRegExp>
#include <qtextcodec.h>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "message.h"

class pop3 : public QObject
{
    Q_OBJECT
public:
    pop3(QString login_,QString password_,QString host_,int port_,int timeout_);
    pop3();
    ~pop3();
    Message msg;

signals:

public slots:
    bool sendUser();
    bool sendPass();
    bool sendQuit();
    bool connectToHost();
    bool sendList(QTableWidget *table, int start);
    bool sendRetr(int number);
    bool sendTop(int number, QTableWidget *table);
    void sendNoop();
private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    QByteArray processingRequest(QString request);
    void parsingMessage(QByteArray message,int number);
    void parsingPart(QByteArray response, int number);
private:
    QString login;
    QString password;
    QString host;
    int port;
    int timeout;
    int countMessage;
    QSslSocket * socket;
};

#endif // POP3_H
