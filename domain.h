#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

class Domain
{
private:
    QString name;
    QString pop3TslHost;
    QString pop3SslHost;
    int pop3SslPort;
    int pop3TslPort;


    QString imapTslHost;
    QString imapSslHost;
    int imapTslPort;
    int imapSslPort;

    bool selected;

public:
    ~Domain();
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
