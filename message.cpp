#include "message.h"

Message::Message()
    :from(),
     to(),
     messagePartList(),
     transferEncodingPartList(),
     textEncodingPartList(),
     uidl(),
     number(0)
{}

Message::~Message(){
}

void Message::setFrom(QString from_){
    from=from_;
}

void Message::setTo(QString to_){
    to=to_;
}

void Message::setUidl(QString uidl_){
    uidl=uidl_;
}

QString Message::getFrom(){
    return from;
}

QString Message::getTo(){
    return to;
}

QString Message::getUidl(){
    return uidl;
}

void Message::appendPart(QByteArray message_, QString transferEncoding_, QString textEncoding_, QString contentTypePartList_, QString contentSubtypePartList_){
    messagePartList.append(message_);
    transferEncodingPartList.append(transferEncoding_);
    textEncodingPartList.append(textEncoding_);
    contentTypePartList.append(contentTypePartList_);
    contentSubtypePartList.append(contentSubtypePartList_);
}

void Message::setNumber(int number_){
    number=number_;
}

int Message::getNumber(){
    return number;
}

void Message::print(QWebView *web){
    web->setHtml(QString("<html><body></body></html>"));
//    qDebug() << "from - " << from;
//    qDebug() << "to - " << to;
//    qDebug() << "uidl - " << uidl;
//    qDebug() << "number - " << QString::number(number);
//    QString full;
//    from->setText(this->from);
//    to->setText(this->to);
//    qDebug() << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    while(!messagePartList.isEmpty()){

        QString charset = textEncodingPartList.takeFirst();
        QString transferEncoding = transferEncodingPartList.takeFirst();
     //   qDebug() << "transferEncodingPartList - " << transferEncoding;
      //  qDebug() << "textEncodingPartList - " << charset;
      //  qDebug() << "contentTypePartList - " << contentTypePartList.takeFirst();
      //  qDebug() << "contentSubtypePartList - " << contentSubtypePartList.takeFirst();
//        qDebug() << "messagePartList - ";

        QByteArray message = messagePartList.takeFirst();
        if((transferEncoding=="quoted-printable")||(transferEncoding=="Quoted-Printable")) message =  QuotedPrintable::decode(message);
        if(transferEncoding=="base64") message =  QByteArray::fromBase64(message);
        QString tempType = contentTypePartList.takeFirst();
        QString tempSubType = contentSubtypePartList.takeFirst();

        QString msg;
        if((!charset.isEmpty())&&(charset!="utf-8")&&(charset!="UTF-8")&&(tempType=="text")) msg = QTextCodec::codecForName(charset.toUtf8())->toUnicode(message);
        else msg = QString::fromUtf8(message);
//        qDebug() << msg;
//        full.append(msg);
        //if(contentTypePartList.takeFirst()=="text")
        if((tempType=="text")){
            if(tempSubType == "html")
            web->setHtml(msg);
            else{
                msg = "<html><body>"+msg+"</body></html>";
//                qDebug() << msg<<"\n\n\n\n\n\n\n\n";
                web->setHtml(msg);
            }
        }

        /*
        QFile file;
        file.setFileName("C:\\Users\\РЎРµСЂРіРµР№\\Desktop\\test\\"+QString::number(number)+".html");
        file.open(QFile::Append);
        if((transferEncoding=="quoted-printable")||(transferEncoding=="base64"))
//        if((charset=="utf-8")||(charset=="UTF-8"))
//        file.write(message);
//        else
            file.write(msg.toLocal8Bit());
        else file.write(msg.toUtf8());
        file.close();
        */
    }
}

void Message::clear()
{
    from.clear();
    to.clear();
    messagePartList.clear();
    transferEncodingPartList.clear();
    textEncodingPartList.clear();
    contentTypePartList.clear();
    contentSubtypePartList.clear();
    uidl.clear();
    number=0;

}
