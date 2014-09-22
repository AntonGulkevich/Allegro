#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "domain.h"

class Account
{
    QString email;
    QString password;

    Domain *_domain;
public:
    Account();
};

#endif // ACCOUNT_H
