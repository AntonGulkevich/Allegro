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

Domain::~Domain(){

}

void Domain::setSelection(bool state){
    selected= state;
}
bool Domain::isSelected(){
    return selected;
}
