#ifndef THREADPOP3_H
#define THREADPOP3_H
#include <QThread>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QList>
#include <QWebView>
#include <message.h>

#include "basepop3.h"

class ThreadPop3 : public QObject
{
    Q_OBJECT
    BasePop3 * base;
    QThread * thread;
    QTableWidget *tabl;
    QWebView * vie;
public:
    ThreadPop3(QTableWidget * table,QWebView * view);
signals:
    void get20MessageSignal();
    void getMessageSignal(int number);
public slots:
    void getMessageTop(Message top);
    void getMessage(Message msg);
};


#endif // THREADPOP3_H
