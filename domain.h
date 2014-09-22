#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

class Domain
{
private:
    QString name;
    QString pop3TslHost;
    QString pop3SslHost;
    int pop3TslPort;
    int pop3SslPort;

    QString imapTslHost;
    QString imapSslHost;
    int imapTslPort;
    int imapSslPort;

public:
    Domain();
};

#endif // DOMAIN_H
