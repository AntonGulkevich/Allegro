#include "pop3.h"
#include <QDateTime>
#include <QLocale>


pop3::pop3(QString login_, QString password_, QString host_, int port_, int timeout_):
    login(login_),
    password(password_),
    host(host_),
    port(port_),
    timeout(timeout_),
    socket(new QSslSocket(this)),
    countMessage(0)
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
        if(!socket->waitForReadyRead(80)) break;
        bytesAvailable = socket->bytesAvailable();
    } while (bytesAvailable!=0);
//    qDebug() << response;
//    qDebug() << response.size();
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

bool pop3::sendList(QTableWidget *table, int start){
    QString response = QString::fromUtf8(processingRequest("UIDL \r\n"));
    qDebug() << response;
    if(!response.startsWith("+OK")) return false;
    QStringList list = response.split("\r\n");
    countMessage = list.takeFirst().split(" ").at(1).toInt();
    qDebug() << "hhhuuuiii" << start << countMessage;
    if(start>countMessage) return false;
    QRegExp strList("([0-9]*) (.*)");
    strList.setMinimal(false);
    for(int i =0;i<start;i++){
        list.takeFirst();
    }
    for(int i =0; i<20;i++){
        QString str = list.takeFirst();
        if(str==".") break;
        strList.indexIn(str,0);
        if(strList.cap(0).isEmpty()) break;
        table->setRowCount(table->rowCount()+1);
        QTableWidgetItem *item = new QTableWidgetItem(strList.cap(1));
        table->setItem(table->rowCount()-1,4,item);
        sendTop(strList.cap(1).toInt(),table);
        qDebug() << i;
    }
    return true;
}

bool pop3::sendTop(int number, QTableWidget *table){
    QByteArray response = processingRequest("TOP "+QString::number(number)+" 0\r\n");
//    QRegExp fromReg("\\nFrom: (.*) <*([a-zA-Z0-9\\.\\-\\+]*@[a-zA-Z0-9\\.\\-]*[\\.][a-zA-Z0-9\\.\\-]*)>*.*[\\r]");

    QRegExp fromReg("\\nFrom:(.*)[ <]<*([a-zA-Z0-9\\.\\-\\+\\_]*@[a-zA-Z0-9\\.\\-]*[\\.][a-zA-Z0-9\\.\\-]*)>*.*[\\r\\n]");


    fromReg.setMinimal(true);
    fromReg.indexIn(response,0);

    QRegExp strSubjectReg("(=\\?([^\\?\\r\\n]*)\\?([^\\?\\r\\n]*)\\?([^\\?\\r\\n]*)\\?=)");

    int t = strSubjectReg.indexIn(fromReg.cap(1),0);
    QString fromMes;
    if(!strSubjectReg.cap(0).isEmpty()){

        QByteArray buff;
        while(!strSubjectReg.cap(0).isEmpty()){
            QByteArray temp;
            temp.append(buff);
            temp.append(strSubjectReg.cap(4).toUtf8());
            buff.clear();
            if((temp.right(1)=="=")||(strSubjectReg.cap(3)=="Q")||(strSubjectReg.cap(3)=="q")){
                if((strSubjectReg.cap(3)=="B")||(strSubjectReg.cap(3)=="b")) temp = QByteArray::fromBase64(temp);
                if((strSubjectReg.cap(3)=="Q")||(strSubjectReg.cap(3)=="q")) temp = QuotedPrintable::decode(temp);
                QString msg;
                if((strSubjectReg.cap(2)!="utf-8")&&(strSubjectReg.cap(2)!="UTF-8")) msg = QTextCodec::codecForName(strSubjectReg.cap(2).toUtf8())->toUnicode(temp);
                else msg = QString::fromUtf8(temp);
                fromMes.append(msg);
            } else buff.append(temp);
            t++;
            t = strSubjectReg.indexIn(fromReg.cap(1),t);
        }
        strSubjectReg.indexIn(fromReg.cap(1),0);
        if(!buff.isEmpty()){
            buff = QByteArray::fromBase64(buff);
            QString msg;
            if((strSubjectReg.cap(2)!="utf-8")&&(strSubjectReg.cap(2)!="UTF-8")) msg = QTextCodec::codecForName(strSubjectReg.cap(2).toUtf8())->toUnicode(buff);
            else msg = QString::fromUtf8(buff);
            fromMes.append(msg);
        }

    }
 else {
    QRegExp noEncordingStr(" (\"(.*)\")| ([^\"]*)");
    noEncordingStr.indexIn(fromReg.cap(1),0);
    if(!noEncordingStr.cap(2).isEmpty())
    fromMes.append(noEncordingStr.cap(2));
    else
    fromMes.append(noEncordingStr.cap(3));
}


    /*strSubjectReg.indexIn(fromReg.cap(1),0);
    QString fromMes;
    if(!strSubjectReg.cap(0).isEmpty()){
        QByteArray temp = strSubjectReg.cap(4).toUtf8();

        if(strSubjectReg.cap(3)=="B") temp = QByteArray::fromBase64(temp);
        if(strSubjectReg.cap(3)=="Q") temp = QuotedPrintable::decode(temp);

        QString msg;
        if((strSubjectReg.cap(2)!="utf-8")&&(strSubjectReg.cap(2)!="UTF-8")) msg = QTextCodec::codecForName(strSubjectReg.cap(2).toUtf8())->toUnicode(temp);
        else msg = QString::fromUtf8(temp);

        fromMes.append(msg);

    } else {
        QRegExp noEncordingStr("(\"(.*)\")|( (.*) )");
        noEncordingStr.indexIn(fromReg.cap(1),0);
        if(!noEncordingStr.cap(2).isEmpty())
        fromMes.append(noEncordingStr.cap(2));
        else
        fromMes.append(noEncordingStr.cap(4));
    }

*/



//    fromMes.append("           "+fromReg.cap(2));
//    fromMes = fromReg.cap(2);
    QTableWidgetItem *from = new QTableWidgetItem(fromMes);
    table->setItem(table->rowCount()-1,0,from);
    from = new QTableWidgetItem(fromReg.cap(2));
    table->setItem(table->rowCount()-1,1,from);



    // Date: Fri, 05 Dec 2014 14:27:32 +0000



    //Date: Sun, 02 Nov 2014 16:50:03 +0300
    QRegExp dateReg("Date: ([^\\r\\n]*) ([+-][^\\r\\n]{4})");
    dateReg.indexIn(response,0);
    if(dateReg.cap(0).isEmpty()){
        dateReg.setPattern("Date: ([^\\r\\n]*) ([^\\r\\n]{3})");
        dateReg.indexIn(response,0);
    }
    QDateTime dateTime;
//    dateTime=QDateTime::currentDateTime();
//    QLocale loc(QLocale::C);
//    dateTime = loc.toDateTime(dateReg.cap(1),"ddd, dd MMM yyyy hh:mm:ss");
    QLocale loc(QLocale::C);
    dateTime = loc.toDateTime(dateReg.cap(1),"ddd,  dd MMM yyyy hh:mm:ss");
    if(dateTime.toMSecsSinceEpoch()==0)
        dateTime = loc.toDateTime(dateReg.cap(1),"ddd,  d MMM yyyy hh:mm:ss");
    if(dateTime.toMSecsSinceEpoch()==0)
        dateTime = loc.toDateTime(dateReg.cap(1),"ddd, dd MMM yyyy hh:mm:ss");
    if(dateTime.toMSecsSinceEpoch()==0)
        dateTime = loc.toDateTime(dateReg.cap(1),"ddd, d MMM yyyy hh:mm:ss");

    if(dateTime.toMSecsSinceEpoch()==0)
        dateTime = loc.toDateTime(dateReg.cap(1),"d MMM yyyy hh:mm:ss");
    int sm=0;
    if(dateReg.cap(2)=="PDT") sm=-7;
    if(dateReg.cap(2)=="GMT") sm=0;
    bool g;
    dateReg.cap(2).toInt(&g,10);
    if(g) sm=dateReg.cap(2).toInt()/100;
    dateTime = dateTime.addSecs((-sm+3)*3600);
    QTableWidgetItem *date = new QTableWidgetItem(dateTime.toString("ddd, dd MMM yyyy hh:mm:ss"));
    table->setItem(table->rowCount()-1,5,date);




//    QRegExp toReg("\\nTo: .*<*([a-zA-Z0-9\\.\\-]*@[a-zA-Z0-9\\.\\-]*[\\.][a-zA-Z0-9\\.\\-]*)>*.*[\\r]");
//    toReg.setMinimal(true);
//    toReg.indexIn(response,0);
    QTableWidgetItem *to = new QTableWidgetItem("terabait20xx@yandex.ru");
    table->setItem(table->rowCount()-1,2,to);
    QRegExp subjectReg("Subject: ([^=]*=\\?([^\\?\\r\\n]*)\\?([^\\?\\r\\n]*)\\?([^\\?\\r\\n]*)\\?=)*");
    subjectReg.setMinimal(false);
    subjectReg.indexIn(response,0);
    int k = strSubjectReg.indexIn(subjectReg.cap(0),0);
    QString head;
    if(strSubjectReg.cap(0).isEmpty()){
        QRegExp subjectReg2("Subject: (.*)[\\r\\n]");
        subjectReg2.setMinimal(true);
        subjectReg2.indexIn(response,0);
        head.append(subjectReg2.cap(1));
    }
    QByteArray buff;
    while(!strSubjectReg.cap(0).isEmpty()){
        QByteArray temp;
        temp.append(buff);
        temp.append(strSubjectReg.cap(4).toUtf8());
        buff.clear();
        if((temp.right(1)=="=")||(strSubjectReg.cap(3)=="Q")||(strSubjectReg.cap(3)=="q")){
            if((strSubjectReg.cap(3)=="B")||(strSubjectReg.cap(3)=="b")) temp = QByteArray::fromBase64(temp);
            if((strSubjectReg.cap(3)=="Q")||(strSubjectReg.cap(3)=="q")) temp = QuotedPrintable::decode(temp);
            QString msg;
            if((strSubjectReg.cap(2)!="utf-8")&&(strSubjectReg.cap(2)!="UTF-8")) msg = QTextCodec::codecForName(strSubjectReg.cap(2).toUtf8())->toUnicode(temp);
            else msg = QString::fromUtf8(temp);
            head.append(msg);
        } else buff.append(temp);
        k++;
        k = strSubjectReg.indexIn(subjectReg.cap(0),k);
    }
    strSubjectReg.indexIn(subjectReg.cap(0),0);
    if(!buff.isEmpty()){
        buff = QByteArray::fromBase64(buff);
        QString msg;
        if((strSubjectReg.cap(2)!="utf-8")&&(strSubjectReg.cap(2)!="UTF-8")) msg = QTextCodec::codecForName(strSubjectReg.cap(2).toUtf8())->toUnicode(buff);
        else msg = QString::fromUtf8(buff);
        head.append(msg);
    }



//Subject: =?UTF-8?B?0J/RgNC10LLRgNCw0YLQuNGC0LUgJDUg0LIgJDEgMDAwIDAwMCDQsiA=?=
    //=?UTF-8?B?0YLRg9GA0L3QuNGA0LDRhSDRgdC/0LjQvS3RjdC90LQt0LPQvtGDINC90LAg?=
    //=?UTF-8?B?JDEgMDAwIDAwMA==?=



            QTableWidgetItem *item = new QTableWidgetItem(head);
            table->setItem(table->rowCount()-1,3,item);


    /*
     * Subject: =?utf-8?B?QXNpcnJpcywg0YHQvtGB0YLQvtGP0LvRgdGPINCy0YvRhdC+0LQgRmFyIENy?=
 =?utf-8?B?eSA0ISDQn9GN0LnQs9Cw0L0g0JzQuNC9INC20LTQtdGCINCy0LDRgSDQsiDQ?=
 =?utf-8?B?mtC40YDQsNGC0LUh?=

    */

    return true;
}

bool pop3::sendRetr(int number){
    QByteArray response = processingRequest("TOP "+QString::number(number)+"\r\n");
    QFile file;
    file.setFileName("C:\\Users\\Сергей\\Desktop\\test\\"+QString::number(number)+".txt");
    if(file.open(QFile::WriteOnly)){
        QDataStream data(&file);
        data << response;
        file.close();
    }

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
        if(contentTypeReg.cap(0).isEmpty()){
            contentTypeReg.setPattern("Content-type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*charset=\"*([a-zA-Z0-9\\.\\-]*)\"*.*[\\r]");
            contentTypeReg.indexIn(message,0);
        }
        if(contentTypeReg.cap(0).isEmpty()){
            contentTypeReg.setPattern("Content-Type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*name=\"([a-zA-Z0-9\\.\\-]*)\"[\\r]");
            contentTypeReg.indexIn(message,0);
        }
        if(contentTypeReg.cap(0).isEmpty()){
            contentTypeReg.setPattern("Content-Type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*[\\r]");
            contentTypeReg.indexIn(message,0);
        }
        QString contentType = contentTypeReg.cap(1);
        QString contentSubtype = contentTypeReg.cap(2);
        QString charset;
        if(contentTypeReg.cap(3).isEmpty()) charset = "utf-8";
        else charset = contentTypeReg.cap(3);
        QRegExp contentTransferEncodingReg("Content-Transfer-Encoding: .*([a-zA-Z0-9\\.\\-]*).*[\\r]");
        contentTransferEncodingReg.setMinimal(true);
        contentTransferEncodingReg.indexIn(message,0);
        QString contentTransferEncoding = contentTransferEncodingReg.cap(1);
  //     qDebug() << QString::number(message.indexOf("\r\n\r\n"));
        message=message.right(message.count()-message.indexOf("\r\n\r\n"));
        qDebug() << message << contentTransferEncoding << charset << contentType << contentSubtype;
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
void pop3::sendNoop(){
    QByteArray response = processingRequest("NOOP\r\n");
    qDebug() << response;
}
