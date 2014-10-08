#include "account.h"

#include <QDebug>

Account::Account(const QString &_email, const QString &_password, const Domain &_domain) :
    email(_email), password (_password)
{
    domain_name=email.right(email.length()-email.indexOf("@")-1);
    domain_name=domain_name.left(domain_name.length()-domain_name.indexOf(".")+1);

    domain= new Domain(_domain);
}
Account::~Account(){
    if(domain)
        delete domain;
}

