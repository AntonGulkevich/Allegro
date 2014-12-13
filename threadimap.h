#ifndef THREADImap_H
#define THREADImap_H
#include <QThread>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QList>
#include <QWebView>
#include <message.h>
#include <QTextEdit>

#include "baseimap.h"

class ThreadImap : public QObject
{
    Q_OBJECT
    BaseImap * base;
    QThread * thread;
    QTableWidget *tabl;
    QWebView * vie;
    QTextEdit * statu;
    QTableWidget * filetabl;
    QList<QByteArray> * filelis;
public:
    ThreadImap(QList<QByteArray> *filelist,QTableWidget * table,QWebView * view,QTextEdit * status,QTableWidget *fileTable,QString& login,QString& password,QString& host,int port,QSsl::SslProtocol ssl);
signals:
    void get20MessageSignal();
    void getMessageSignal(int number);
    void update();
    void deleteMessage(int number);
public slots:
    void getMessageTop(Message top);
    void getMessage(Message msg);
    void getError(QString messsage);
};


#endif // THREADImap_H
