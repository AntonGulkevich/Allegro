#include "pop3.h"

pop3::pop3(QString login_, QString password_, QString host_, int port_, int timeout_):
    login(login_),
    password(password_),
    host(host_),
    port(port_),
    timeout(timeout_),
    socket(new QSslSocket(this))
{
    /*    QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName("177.234.14.150");
        proxy.setPort(80);
        proxy.setUser("username");
        proxy.setPassword("password");
        socket->setProxy(proxy);
    */
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

pop3::pop3():
    login("login"),
    password("password"),
    host("host"),
    port(0),
    timeout(30000),
    socket(new QSslSocket(this))
{
}


pop3::~pop3(){
    delete socket;
}

void pop3::stateChanged(QAbstractSocket::SocketState socketState) {
    qDebug() << "stateChanged " << socketState;
}

void pop3::errorReceived(QAbstractSocket::SocketError socketError) {
    qDebug() << "error " << socketError;
}

void pop3::disconnected() {
    qDebug() << "disconneted";
    qDebug() << "error " << socket->errorString();
}

void pop3::connected() {
    qDebug() << "Connected ";
}

QByteArray pop3::processingRequest(QString request){
    QByteArray response;
    qint64 writeResult = socket->write(request.toUtf8());
    if (writeResult < 0) return "";
    if (writeResult >= 0 && !socket->waitForBytesWritten(timeout)) return "";
    if (!socket->waitForReadyRead(timeout)) return "";
    quint64 bytesAvailable = 0;
    do {
        QByteArray all(socket->readAll());
        response.append(all);
        if(!socket->waitForReadyRead(500)) break;
        bytesAvailable = socket->bytesAvailable();
    } while (bytesAvailable!=0);
    return response;
}

bool pop3::sendUser(){
    QString response = processingRequest("USER "+login+"\r\n");
    qDebug() << response;
    if(response.startsWith("+OK")) return true;
    return false;
}

bool pop3::sendPass(){
    QString response = processingRequest("PASS "+password+"\r\n");
    qDebug() << response;
    if(response.startsWith("+OK")) return true;
    return false;
}

bool pop3::sendQuit(){
    QString response = processingRequest("QUIT\r\n");
    qDebug() << response;
    if(response.startsWith("+OK")) return true;
    return false;
}

bool pop3::connectToHost(){
    socket->setProtocol(QSsl::SslV3);
    socket->connectToHostEncrypted("pop.yandex.com",995);
    socket->waitForConnected();
    if(socket->state()==QSslSocket::ConnectedState) return true;
    return false;
}

bool pop3::sendList(){
    QString response = processingRequest("UIDL \r\n");
    qDebug() << response;
    if(response.startsWith("+OK")) return true;
    return false;
}

bool pop3::sendRetr(int number){
    QByteArray response = processingRequest("TOP "+QString::number(number)+"\r\n");
/*    QFile file;
    file.setFileName("C:\\Users\\Сергей\\Desktop\\test\\"+QString::number(number)+".txt");
    if(file.open(QFile::WriteOnly)){
        QDataStream data(&file);
        data << response;
        file.close();
    }
    */
    QRegExp fromReg("\\nFrom: .*<*([a-zA-Z0-9\\.\\-]*@[a-zA-Z0-9\\.\\-]*[\\.][a-zA-Z0-9\\.\\-]*)>*.*[\\r]");
    fromReg.setMinimal(true);
    fromReg.indexIn(response,0);
    msg.setFrom(fromReg.cap(1));
    QRegExp toReg("\\nTo: .*<*([a-zA-Z0-9\\.\\-]*@[a-zA-Z0-9\\.\\-]*[\\.][a-zA-Z0-9\\.\\-]*)>*.*[\\r]");
    toReg.setMinimal(true);
    toReg.indexIn(response,0);
    msg.setTo(toReg.cap(1));
    parsingPart(response,number);
    return true;
}

void pop3::parsingMessage(QByteArray message, int number){
    QRegExp multipartReg("Content-Type: .*multipart.*boundary=\"(.*)\".*[\\r]");
    multipartReg.setMinimal(true);
    multipartReg.indexIn(message,0);
    QString boundary = multipartReg.cap(1);
    if(!multipartReg.cap(1).isEmpty()){
        parsingPart(message,number);
        return;
    }
    //    QFile file;
        QRegExp contentTypeReg("Content-Type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*charset=\"*([a-zA-Z0-9\\.\\-]*)\"*.*[\\r]");
        contentTypeReg.setMinimal(true);
        contentTypeReg.indexIn(message,0);
        QString contentType = contentTypeReg.cap(1);
        QString contentSubtype = contentTypeReg.cap(2);
        QString charset = contentTypeReg.cap(3);
        QRegExp contentTransferEncodingReg("Content-Transfer-Encoding: .*([a-zA-Z0-9\\.\\-]*).*[\\r]");
        contentTransferEncodingReg.setMinimal(true);
        contentTransferEncodingReg.indexIn(message,0);
        QString contentTransferEncoding = contentTransferEncodingReg.cap(1);
        qDebug() << QString::number(message.indexOf("\r\n\r\n"));
        message=message.right(message.count()-message.indexOf("\r\n\r\n"));
        msg.appendPart(message,contentTransferEncoding,charset,contentType,contentSubtype);
        msg.setNumber(number);
}

void pop3::parsingPart(QByteArray response, int number){
    QRegExp multipartReg("Content-Type: .*multipart.*boundary=\"(.*)\".*[\\r]");
    multipartReg.setMinimal(true);
    multipartReg.indexIn(response,0);
    QString boundary = multipartReg.cap(1);
    if(multipartReg.cap(1).isEmpty()){
        parsingMessage(response,number);
    } else {
        QByteArray temp;
        int t = 0;
        t = response.indexOf(boundary,t);
        ++t;
        t = response.indexOf(boundary,t);
        while(true){
            qDebug() << t;
            int begin = t + boundary.size();
            ++t ;
            t = response.indexOf(boundary,t);
            int end = t - 2;
            if(end==-3) break;
            temp = response;
            temp.remove(0,begin);
            temp = temp.left(end-begin);
            qDebug() << temp;
            parsingMessage(temp,number);
    }
    }

}

/*
 *      QString msg;
        QByteArray temp;

        if(contentType=="text"){
           // if(contentSubtype=="html"){
                if((contentTransferEncoding=="8bit")||(contentTransferEncoding=="7bit")||(contentTransferEncoding=="binary")){
                    temp=message;
                    if((!charset.isEmpty())&&(charset!="utf-8")) msg = QTextCodec::codecForName(charset.toUtf8())->toUnicode(temp);
                    else msg = QString::fromUtf8(temp);
                    msg=msg.right(msg.count()-msg.indexOf("\r\n\r\n"));
                }
                if(contentTransferEncoding=="base64"){
                    msg = QString::fromUtf8(message);
                    msg=msg.right(msg.count()-msg.indexOf("\r\n\r\n"));
                    temp.append(msg);
                    temp = QByteArray::fromBase64(temp);
                    if((!charset.isEmpty())&&(charset!="utf-8")) msg = QTextCodec::codecForName(charset.toUtf8())->toUnicode(temp);
                    else msg = QString::fromUtf8(temp);
                }
            }
        //}
        file.setFileName("C:\\Users\\Сергей\\Desktop\\"+QString::number(number)+".html");
        if((file.open(QFile::WriteOnly))&&(!temp.isEmpty())){
            if((!charset.isEmpty())&&(charset!="utf-8")) file.write(QTextCodec::codecForName(charset.toUtf8())->fromUnicode(msg));
            else file.write(msg.toLocal8Bit());
            file.close();
        }
*/
