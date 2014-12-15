#include "domain.h"

Domain::Domain(QString _name, QString _pop3host, int _pop3PortEncr,
                              QString _imaphost, int _imapPortEncr,
                              QString _smtphost, int _smtpPortEncr, int _count):
    name(_name),
    pop3Host(_pop3host),pop3PortEncr(_pop3PortEncr),
    imapHost(_imaphost), imapPortEncr(_imapPortEncr),
    smtpHost(_smtphost), smtpPortEncr(_smtpPortEncr), selected(false), count(_count)
{
    checkBox= new QCheckBox;
    checkBox->setChecked(false);
    checkBox->setText("");
    count=0;

}
Domain::Domain(const Domain &_domain)
{
    pop3Host=_domain.pop3Host;
    pop3PortEncr=_domain.pop3PortEncr;

    imapHost=_domain.imapHost;
    imapPortEncr=_domain.imapPortEncr;

    smtpHost=_domain.smtpHost;
    smtpPortEncr=_domain.smtpPortEncr;

    name=_domain.name;

    selected=_domain.selected;

    checkBox= new QCheckBox;
    checkBox->setChecked(selected);
    checkBox->setText("");

    count=0;

}
Domain::~Domain(){
    delete checkBox;

}
void Domain::setSelected(bool state){
    selected= state;
}
bool Domain::isSelected(){
    return selected;
}
QString Domain::getName(){
    return name;
}
QCheckBox * Domain::getChechBoxPtr(){
    setSelected(isSelected());
    return checkBox;
}
QDataStream & operator<<(QDataStream & out, const Domain& domain_)
{
    out <<domain_.name<<domain_.imapHost<<domain_.imapPortEncr<<
         domain_.pop3Host<<domain_.pop3PortEncr<<
         domain_.smtpHost<<domain_.smtpPortEncr<<domain_.selected;

    return out;
}
QDataStream & operator >>(QDataStream & in, Domain& domain_ ){
    in >>domain_.name>>domain_.imapHost>>domain_.imapPortEncr>>
         domain_.pop3Host>>domain_.pop3PortEncr>>
         domain_.smtpHost>>domain_.smtpPortEncr>>domain_.selected;

    return in;


}
void Domain::UpdateSelection(){
    if (checkBox->isChecked()){
        setSelected(true);
    }
    else
        setSelected(false);
}

void Domain::IncCount(){
    count++;
}

int Domain::GetCount(){
    return count;
}
void Domain::SetZeroCount(){
    count=0;
}
QString Domain::GetPop3Host(){
    return pop3Host;
}

QString Domain::GetImapHost(){
    return imapHost;
}

QString Domain::GetSmtpHost(){
    return smtpHost;
}

int Domain::GetPop3PortEncr(){
    return pop3PortEncr;
}

int Domain::GetImapPortEncr(){
    return imapPortEncr;
}

int Domain::GetSmtpPortEncr(){
    return smtpPortEncr;
}
