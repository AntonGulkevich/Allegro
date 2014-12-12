#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include <QVariant>
struct Message
{
public:
    Message();
    Message(const Message & original);
    ~Message();
    QString from;
    QString fromMes;
    QString to;
    QString head;
    QString date;
    QList<QByteArray> messagePartList;
    QList<QString> transferEncodingPartList;
    QList<QString> textEncodingPartList;
    QList<QString> contentTypePartList;
    QList<QString> contentSubtypePartList;
    QString uidl;
    int number;
};

#endif // MESSAGE_H
