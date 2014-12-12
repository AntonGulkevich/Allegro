#include "threadpop3.h"

ThreadPop3::ThreadPop3(QTableWidget *table, QWebView *view)
{
    tabl=table;
    vie=view;
    thread = new QThread();
    QString login="ivanovsergey764";
    QString password="qwerty123";
    QString host="pop.yandex.ru";
    int port=995;
    base = new BasePop3(login,password,host,port,QSsl::SslV3);
    connect(thread,SIGNAL(started()),base,SLOT(run()));
    connect(base,SIGNAL(stop()),thread,SLOT(quit()));
    connect(this,SIGNAL(get20MessageSignal()),base,SLOT(get20Message()));
    connect(base,SIGNAL(MessageTopOK(Message)),this,SLOT(getMessageTop(Message)));
    connect(this,SIGNAL(getMessageSignal(int)),base,SLOT(getMessage(int)));
    connect(base,SIGNAL(MessageOK(Message)),this,SLOT(getMessage(Message)));
    base->moveToThread(thread);
    thread->start();
}

void ThreadPop3::getMessageTop(Message top){
    tabl->setRowCount(tabl->rowCount()+1);
    tabl->setItem(tabl->rowCount()-1,0,new QTableWidgetItem(top.fromMes));
    tabl->setItem(tabl->rowCount()-1,1,new QTableWidgetItem(top.from));
    tabl->setItem(tabl->rowCount()-1,2,new QTableWidgetItem(top.to));
    tabl->setItem(tabl->rowCount()-1,3,new QTableWidgetItem(top.head));
    tabl->setItem(tabl->rowCount()-1,4,new QTableWidgetItem(top.uidl));
    tabl->setItem(tabl->rowCount()-1,5,new QTableWidgetItem(top.date));
}

void ThreadPop3::getMessage(Message msg){
    QString end("<html><body>Пусто</html></body>");
    while(!msg.messagePartList.isEmpty()){
        QString charset = msg.textEncodingPartList.takeFirst();
        QString transferEncoding = msg.transferEncodingPartList.takeFirst();
        QByteArray message = msg.messagePartList.takeFirst();
        if((transferEncoding=="quoted-printable")||(transferEncoding=="Quoted-Printable")) message =  QuotedPrintable::decode(message);
        if(transferEncoding=="base64") message =  QByteArray::fromBase64(message);
        QString tempType = msg.contentTypePartList.takeFirst();
        QString tempSubType = msg.contentSubtypePartList.takeFirst();
        QString msg;
        if((!charset.isEmpty())&&(charset!="utf-8")&&(charset!="UTF-8")&&(tempType=="text")) msg = QTextCodec::codecForName(charset.toUtf8())->toUnicode(message);
        else msg = QString::fromUtf8(message);
        if((tempType=="text")){
            if(tempSubType == "html")
            end =msg;
            else{
                msg = "<html><body>"+msg+"</body></html>";
                end = msg;
            }
        }
        vie->setHtml(end);
    }
}
