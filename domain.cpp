#include "domain.h"

Domain::Domain(QString _name,

               QString _pop3host,
               int _pop3port,

               QString _imaphost,
               int _imapport):
    name(_name),
    pop3Host(_pop3host),pop3Port(_pop3port),
    imapHost(_imaphost), imapPort(_imapport)
{
    selected= false;
}

Domain::Domain(const Domain &_domain){
    pop3Host=_domain.pop3Host;
    pop3Port=_domain.pop3Port;

    imapHost=_domain.imapHost;
    imapPort=_domain.imapPort;

    name=_domain.name;
}

Domain::~Domain(){

}
Domain::Domain(){

}

void Domain::setSelection(bool state){
    selected= state;
}
bool Domain::isSelected(){
    return selected;
}
