#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

class Domain
{
private:
    QString name;
    QString pop3TslHost;
    QString pop3SslHost;
    QString imapTslHost;
    QString imapSslHost;
    int imapTslPort;
    int imapSslPort;
    int pop3SslPort;
    int pop3TslPort;

    bool selected;

public:
    ~Domain();
    Domain();
    Domain(const Domain &_domain);
    Domain(QString _name,

           QString _pop3SSLhost,
           int _pop3SSLport,

           QString _pop3TSLhost,
           int _pop3TSLport,

           QString _imapTSLhost,
           int _imapTSLport,

           QString _imapSSLHost,
           int _imapSSLport);
    void setSelection(bool state);
    bool isSelected();
};

#endif // DOMAIN_H
