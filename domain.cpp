#include "domain.h"

Domain::Domain(QString _name,

               QString _pop3SSLhost,
               int _pop3SSLport,

               QString _pop3TSLhost,
               int _pop3TSLport,

               QString _imapTSLhost,
               int _imapTSLport,

               QString _imapSSLHost,
               int _imapSSLport):
    name(_name),
    pop3SslHost(_pop3SSLhost),pop3SslPort(_pop3SSLport),
    pop3TslHost(_pop3TSLhost), pop3TslPort(_pop3TSLport),
    imapSslHost(_imapSSLHost), imapSslPort(_imapSSLport),
    imapTslHost(_imapTSLhost), imapTslPort(_imapTSLport)
{
    selected= false;
}

Domain::Domain(const Domain &_domain){
    pop3TslHost=_domain.pop3TslHost;
    pop3TslPort=_domain.pop3TslPort;
    pop3SslHost=_domain.pop3SslHost;
    pop3SslPort=_domain.pop3SslPort;

    imapSslHost=_domain.imapSslHost;
    imapSslPort=_domain.imapSslPort;
    imapTslHost=_domain.imapTslHost;
    imapTslPort=_domain.imapTslPort;

    name=_domain.name;
}

Domain::~Domain(){

}

void Domain::setSelection(bool state){
    selected= state;
}
bool Domain::isSelected(){
    return selected;
}
