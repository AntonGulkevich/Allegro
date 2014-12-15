#include "account.h"

#include <QDebug>

Account::Account(const QString &_email, const QString &_password) :
    email(_email), password (_password)
{
    domain_name=email.right(email.length()-email.indexOf("@")-1);
    //domain_name=domain_name.left(domain_name.length()-domain_name.indexOf(".")+1);
}
Account::~Account(){

}
Account::Account(){

}

QString Account::getDomainName(){
    return domain_name;
}
void Account::setDomain(Domain *_domain){
    domain= _domain;
}
QString Account::GetLogin(){
    return email;
}

QString Account::GetPassword(){
    return password;
}
QString Account::GetPop3Host(){
    return domain->GetPop3Host();
}

QString Account::GetImapHost(){
    return domain->GetImapHost();
}

QString Account::GetSmtpHost(){
    return domain->GetSmtpHost();
}

int Account::GetPop3PortEncr(){
    return domain->GetPop3PortEncr();
}

int Account::GetImapPortEncr(){
    return domain->GetImapPortEncr();
}

int Account::GetSmtpPortEncr(){
    return domain->GetSmtpPortEncr();
}


