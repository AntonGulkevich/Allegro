#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "domain.h"

class Account
{
    QString email;
    QString password;
    Domain *domain;
    QString domain_name;
public:
    Account (const QString &_email,const QString &_password);
    ~Account();

};

#endif // ACCOUNT_H
