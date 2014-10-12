#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

class Domain
{
private:
    QString name;

    QString pop3Host;
    int pop3Port;

    QString imapHost;
    int imapPort;

    bool selected;

public:
    ~Domain();
    Domain();
    Domain(const Domain &_domain);
    Domain(QString _name, QString _pop3host, int _pop3port, QString _imaphost, int _imapport);
    void setSelection(bool state);
    bool isSelected();
};

#endif // DOMAIN_H
