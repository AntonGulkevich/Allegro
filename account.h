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
    Account (const QString &_email,const QString &_password, const Domain &_domain);
    ~Account();

};

#endif // ACCOUNT_H
