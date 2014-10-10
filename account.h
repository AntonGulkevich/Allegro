#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "domain.h"

class Account
{
private:
    QString email;
    QString password;
    Domain *domain;
    QString domain_name;
    enum state{
        good,
        bad,
        error,
    };
public:
    Account();
    Account (const QString &_email,const QString &_password);
    ~Account();
    QString getDomainName();
    void setDomain(Domain* _domain);

};

#endif // ACCOUNT_H
