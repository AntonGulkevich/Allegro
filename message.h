#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <QList>
#include <qtextcodec.h>
#include <QFile>
#include <quotedprintable.h>
#include <QWebView>
#include <QTextEdit>

class Message
{
public:
    Message();
    ~Message();
    void setFrom(QString from_);
    QString getFrom();
    void setTo(QString to_);
    QString getTo();
    void setUidl(QString uidl_);
    QString getUidl();
    void appendPart(QByteArray message_,QString transferEncoding_,QString textEncoding_,QString contentTypePartList_,QString contentSubtypePartList_);
    void setNumber(int number_);
    int getNumber();
    void print(QWebView *web,QTextEdit *from,QTextEdit *to);
private:
    QString from;
    QString to;
    QList<QByteArray> messagePartList;
    QList<QString> transferEncodingPartList;
    QList<QString> textEncodingPartList;
    QList<QString> contentTypePartList;
    QList<QString> contentSubtypePartList;
    QString uidl;
    int number;
};

#endif // MESSAGE_H
