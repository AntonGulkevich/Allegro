#include "basepop3.h"

BasePop3::BasePop3(QString& login_,QString& password_,QString& host_,int port_,QSsl::SslProtocol sslProtolol_)
    :login(login_),
     password(password_),
     host(host_),
     port(port_),
     sslProtolol(sslProtolol_)
{
}

BasePop3::~BasePop3()
{
    delete protocol;
    delete timer;
}

void BasePop3::parsTop(Message &message, QByteArray &responseArr){
    QString response(responseArr);
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
            }else buff.append(temp);
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
    message.fromMes.append(fromMes);
    message.from.append(fromReg.cap(2));
    QRegExp dateReg("Date: ([^\\r\\n]*) ([+-][^\\r\\n]{4})");
    dateReg.indexIn(response,0);
    if(dateReg.cap(0).isEmpty()){
        dateReg.setPattern("Date: ([^\\r\\n]*) ([^\\r\\n]{3})");
        dateReg.indexIn(response,0);
    }
    QDateTime dateTime;
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
    QRegExp toReg("\\nTo: .*<*([a-zA-Z0-9\\.\\-]*@[a-zA-Z0-9\\.\\-]*[\\.][a-zA-Z0-9\\.\\-]*)>*.*[\\r]");
    toReg.setMinimal(true);
    toReg.indexIn(response,0);
    message.to.append(toReg.cap(1));
    message.date.append(dateTime.toString("ddd, dd MMM yyyy hh:mm:ss"));
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
    message.head.append(head);
}

void BasePop3::run()
{
    protocol = new Pop3(login,password,host,port,sslProtolol);
    if(!protocol->connectToHost()){
        QString error("Ошибка соединения");
        emit Error(error);
        return;
    }
    if(!protocol->sendUser()){
        QString error("Некорректный логин");
        emit Error(error);
        return;
    } else {
        QString message("Логин подтверждён");
        emit Error(message);
    }
    if(!protocol->sendPass()){
        QString error("Некорректный пароль");
        emit Error(error);
        return;
    } else{
        QString message("Пароль подтверждён");
        emit Error(message);
    }
    timer = new QTimer();
    countReal = 0;
    connect(timer, SIGNAL(timeout()),this,SLOT(updateTCP()));
    timer->start(20000);
}

void BasePop3::updateTCP(){
    protocol->sendNoop();
    timer->start(30000);
}

void BasePop3::get20Message()
{
    int start = countReal;
    countReal+=20;
    QString response = QString::fromUtf8(protocol->sendList());
    if(!response.startsWith("+OK")){
        QString error("Сервер не отвечает");
        emit Error(error);
        return;
    }
    QStringList list = response.split("\r\n");
    //int countMessage = list.takeFirst().split(" ").at(1).toInt();
    int countMessage=list.count()-3;
    if((start>countMessage)||(start<0)) return;
    QRegExp strList("([0-9]*) (.*)");
    strList.setMinimal(false);

    for(int i =0;i<start;i++){
        list.takeFirst();
    }
    list.takeFirst();

    for(int i =0; i<20;i++){
        QString str = list.takeFirst();
        if(str==".") break;
        strList.indexIn(str,0);
        Message msg;
        msg.number = strList.cap(1).toInt();
        msg.uidl.append(strList.cap(2));
        QByteArray top = protocol->sendTop(msg.number);
        parsTop(msg,top);
        emit MessageTopOK(msg);
    }
}

void BasePop3::getMessage(int number){
    QByteArray response = protocol->sendRetr(number);
    Message msg;
    msg.number=number;
    parsingPart(msg,response);
    emit MessageOK(msg);
}

void BasePop3::deleteMessage(int number)
{
    if(!protocol->sendDele(number)){
        QString error("Ошибка соединения");
        emit Error(error);
    } else {
        QString message("Письмо удалено");
        emit Error(message);
    }
    protocol->sendQuit();
    protocol->connectToHost();
    protocol->sendUser();
    protocol->sendPass();
}

void BasePop3::update()
{
    countReal=0;
    get20Message();
}

void BasePop3::parsingMessage(Message& msg,QByteArray message){
    QRegExp multipartReg("Content-Type: .*multipart.*boundary=\"(.*)\".*[\\r]");
    multipartReg.setMinimal(true);
    multipartReg.indexIn(message,0);
    if(!multipartReg.cap(1).isEmpty()){
        parsingPart(msg,message);
        return;
    }
        QRegExp contentTypeReg("Content-Type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*charset=\"*([a-zA-Z0-9\\.\\-]*)\"*.*[\\r]");
        contentTypeReg.setMinimal(true);
        contentTypeReg.indexIn(message,0);
        if(contentTypeReg.cap(0).isEmpty()){
            contentTypeReg.setPattern("Content-type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*charset=\"*([a-zA-Z0-9\\.\\-]*)\"*.*[\\r]");
            contentTypeReg.indexIn(message,0);
        }


        if(contentTypeReg.cap(0).isEmpty()){
            contentTypeReg.setPattern("Content-Type: ([a-zA-Z0-9\\.\\-]*)[/]([a-zA-Z0-9\\.\\-]*).*name=\"([a-zA-Z0-9\\.\\-\\_]*)\"[\\r]");
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
        message=message.right(message.count()-message.indexOf("\r\n\r\n"));
        msg.messagePartList.append(message);
        msg.transferEncodingPartList.append(contentTransferEncoding);
        msg.textEncodingPartList.append(charset);
        msg.contentTypePartList.append(contentType);
        msg.contentSubtypePartList.append(contentSubtype);
}

void BasePop3::parsingPart(Message& msg,QByteArray response){
    QRegExp multipartReg("Content-[Tt]ype: .*multipart.*boundary=\"(.*)\".*[\\r]");
    multipartReg.setMinimal(true);
    multipartReg.indexIn(response,0);
    QString boundary = multipartReg.cap(1);
    if(multipartReg.cap(1).isEmpty()){
        parsingMessage(msg,response);
    } else {
        QByteArray temp;
        int t = 0;
        t = response.indexOf(boundary,t);
        ++t;
        t = response.indexOf(boundary,t);
        while(true){
            int begin = t + boundary.size();
            ++t ;
            t = response.indexOf(boundary,t);
            int end = t - 2;
            if(end==-3) break;
            temp = response;
            temp.remove(0,begin);
            temp = temp.left(end-begin);
            parsingMessage(msg,temp);
    }
    }
}
