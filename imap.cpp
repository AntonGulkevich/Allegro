#include "Imap.h"

Imap::Imap(QString &login_, QString &password_, QString &host_, int port_,QSsl::SslProtocol sslProtolol_)
    :login(login_),
     password(password_),
     host(host_),
     port(port_),
     socket(new QSslSocket()),
     sslProtolol(sslProtolol_),
     identificator(1)
{
}

Imap::~Imap(){
    delete socket;
}

bool Imap::connectToHost(){
    socket->setProtocol(sslProtolol);
    socket->connectToHostEncrypted(host,port);
    socket->waitForConnected();
    if(socket->state()==QSslSocket::ConnectedState) return true;
    else return false;
}

bool Imap::sendDele(int number){
    QString response = processingRequest(identificatorCommand()+" store "+QString::number(number+1)+" +flags \\deleted\r\n");
    QRegExp ok(".*OK.*");
    ok.indexIn(response);
    processingRequest(identificatorCommand()+" EXPUNGE\r\n");
    if(ok.cap(0).isEmpty()) return false;
    return true;
}

void Imap::sendNoop(){
    processingRequest(identificatorCommand()+" NOOP\r\n");
}

QByteArray Imap::processingRequest(QString request){
    QByteArray response;
    qint64 writeResult = socket->write(request.toUtf8());
    if (writeResult < 0) return "";
    if (writeResult >= 0 && !socket->waitForBytesWritten()) return "";
    quint64 bytesAvailable = 0;
    do{
        QByteArray all(socket->readAll());
        response.append(all);
        socket->waitForReadyRead(1000);
        bytesAvailable = socket->bytesAvailable();
    } while (bytesAvailable!=0);
    return response;
}

bool Imap::sendLogin(){
    QString response(processingRequest(identificatorCommand()+" Login "+login+" "+password+"\r\n"));
    if(response.isEmpty()) response = processingRequest(identificatorCommand()+" Login "+login+" "+password+"\r\n");
    QRegExp ok(".*A[0-9]{3} OK.*");
    ok.indexIn(response);
    if(!ok.cap(0).isEmpty()) return true;
    return false;
}

void Imap::sendLogout(){
    processingRequest(identificatorCommand()+" Logout\r\n");
}
QString Imap::identificatorCommand()
{
    if(identificator==999) identificator=1;
    QString end = QString::number(identificator);
    for(int i = 0;i<4-end.count();i++){
        end = "0"+end;
    }
    end = "A"+end;
    identificator++;
    return end;
}

QByteArray Imap::sendSelectInbox(){
    QByteArray response = processingRequest(identificatorCommand()+" Select inbox\r\n");
     if(response.isEmpty()) response = processingRequest(identificatorCommand()+" Select inbox\r\n");
    return response;
}

QByteArray Imap::sendFetchHead(int number){
    QByteArray response = processingRequest(identificatorCommand()+" Fetch "+QString::number(number)+" body[header]\r\n");
     if(response.isEmpty()) response = processingRequest(identificatorCommand()+" Fetch "+QString::number(number)+" body[header]\r\n");
    return response;
}

QByteArray Imap::sendFetchMessage(int number)
{
    QByteArray response = processingRequest(identificatorCommand()+" Fetch "+QString::number(number)+" body[]\r\n");
    if(response.isEmpty()) response = processingRequest(identificatorCommand()+" Fetch "+QString::number(number)+" body[]\r\n");
    response = response.remove(response.count()-29,29);
    return response;
}
