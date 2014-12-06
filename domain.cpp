#include "domain.h"

Domain::Domain(QString _name, QString _pop3host, int _pop3PortEncr, int _pop3PortNoEncr,
                              QString _imaphost, int _imapPortEncr, int _imapPortNoEncr):
    name(_name),
    pop3Host(_pop3host),pop3PortEncr(_pop3PortEncr), pop3PortNoEncr(_pop3PortNoEncr),
    imapHost(_imaphost), imapPortEncr(_imapPortEncr), imapPortNoEncr(_imapPortNoEncr), selected(false)
{
    checkBox= new QCheckBox;
    checkBox->setChecked(false);
    checkBox->setText("");

}
Domain::Domain(const Domain &_domain)
{
    pop3Host=_domain.pop3Host;
    pop3PortEncr=_domain.pop3PortEncr;
    pop3PortNoEncr=_domain.pop3PortNoEncr;

    imapHost=_domain.imapHost;
    imapPortEncr=_domain.imapPortEncr;
    imapPortNoEncr=_domain.imapPortNoEncr;

    name=_domain.name;

    selected=_domain.selected;

    checkBox= new QCheckBox;
    checkBox->setChecked(selected);
    checkBox->setText("");

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
    out <<domain_.name<<domain_.imapHost<<domain_.imapPortEncr<<domain_.imapPortNoEncr<<
         domain_.pop3Host<<domain_.pop3PortEncr<<domain_.pop3PortNoEncr<<domain_.selected;

    return out;
}
QDataStream & operator >>(QDataStream & in, Domain& domain_ ){
    in >>domain_.name>>domain_.imapHost>>domain_.imapPortEncr>>domain_.imapPortNoEncr>>
         domain_.pop3Host>>domain_.pop3PortEncr>>domain_.pop3PortNoEncr>>domain_.selected;

    return in;


}
void Domain::UpdateSelection(){
    if (checkBox->isChecked()){
        setSelected(true);
    }
    else
        setSelected(false);
}
