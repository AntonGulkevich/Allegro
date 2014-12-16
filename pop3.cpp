#include "pop3.h"

Pop3::Pop3(QString &login_, QString &password_, QString &host_, int port_,QSsl::SslProtocol sslProtolol_)
    :login(login_),
     password(password_),
     host(host_),
     port(port_),
     socket(new QSslSocket()),
     sslProtolol(sslProtolol_)
{
}

Pop3::~Pop3(){
    delete socket;
}

bool Pop3::connectToHost(){
    socket->setProtocol(sslProtolol);
    socket->connectToHostEncrypted(host,port);
    socket->waitForConnected();
    if(socket->state()==QSslSocket::ConnectedState) return true;
    else return false;
}

bool Pop3::sendUser(){
    QString response (processingRequest("USER "+login+"\r\n"));
    QRegExp ok(".*OK.*OK.*");
    ok.setMinimal(true);
    ok.indexIn(response);
    if(ok.cap(0).isEmpty()) return false;
    return true;
}

bool Pop3::sendPass(){
    QString response = processingRequest("PASS "+password+"\r\n");
    if(response.startsWith("+OK")) return true;
    return false;
}

void Pop3::sendQuit(){
    processingRequest("QUIT\r\n");
}

bool Pop3::sendDele(int number){
    QString response = processingRequest("DELE "+QString::number(number)+"\r\n");
    if(response.startsWith("+OK")) return true;
    return false;
}

void Pop3::sendNoop(){
    processingRequest("NOOP\r\n");
}

QByteArray Pop3::sendList(){
    QByteArray response = processingRequest("UIDL \r\n");
    return response;
}

QByteArray Pop3::sendRetr(int number){
    QByteArray response = processingRequest("RETR "+QString::number(number)+"\r\n");
    if(response.isEmpty()) response = processingRequest("RETR "+QString::number(number)+"\r\n");
    return response;
}

QByteArray Pop3::sendTop(int number){
    QByteArray response = processingRequest("TOP "+QString::number(number)+" 0\r\n");
    if(response.isEmpty()) response = processingRequest("TOP "+QString::number(number)+" 0\r\n");
    return response;
}

QByteArray Pop3::processingRequest(QString request){
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
