#ifndef QUOTEDPRINTABLE_H
#define QUOTEDPRINTABLE_H

#include <QByteArray>

class QuotedPrintable
{
public:
    static QByteArray& encode(const QByteArray &input);
    static QByteArray& decode(const QByteArray &input);
};

#endif // QUOTEDPRINTABLE_H
