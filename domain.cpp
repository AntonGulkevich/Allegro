#include "domain.h"

Domain::Domain(QString _name, QString _pop3host, int _pop3PortEncr, int _pop3PortNoEncr,
                              QString _imaphost, int _imapPortEncr, int _imapPortNoEncr):
    name(_name),
    pop3Host(_pop3host),pop3PortEncr(_pop3PortEncr), pop3PortNoEncr(_pop3PortNoEncr),
    imapHost(_imaphost), imapPortEncr(_imapPortEncr), imapPortNoEncr(_imapPortNoEncr), selected(false)
{

    t = new QWidget;
    box = new QBoxLayout(QBoxLayout::LeftToRight);
    box->setSpacing(0);
    box->setMargin(0);
    checkBox= new QCheckBox;
    checkBox->setChecked(false);
    checkBox->setText("");
    box->addWidget(checkBox,1, Qt::AlignCenter);
    t->setLayout(box);

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

    t = new QWidget;
    box = new QBoxLayout(QBoxLayout::LeftToRight);
    box->setSpacing(0);
    box->setMargin(0);
    checkBox= new QCheckBox;
    checkBox->setChecked(false);
    checkBox->setText("");
    box->addWidget(checkBox,1, Qt::AlignCenter);
    t->setLayout(box);
}
Domain::~Domain(){
    delete box;
    delete checkBox;
    delete t;
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
void Domain::setCheckBox(QCheckBox *box){
    checkBox= box;
}
QCheckBox * Domain::getChechBoxPtr(){
    return checkBox;
}
QBoxLayout * Domain::getLayPtr(){
    return box;
}
QWidget* Domain::getWidgetPtr(){
    return t;
}
