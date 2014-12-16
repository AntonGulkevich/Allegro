#include "threadpop3.h"

ThreadPop3::ThreadPop3(QList<QByteArray> *filelist,QTableWidget *table, QWebView *view,QTextEdit * status,QTableWidget *fileTable,QString& login,QString& password,QString& host,int port,QSsl::SslProtocol ssl)
{
    filelis = filelist;
    tabl=table;
    vie=view;
    statu=status;
    filetabl=fileTable;
    thread = new QThread();
    base = new BasePop3(login,password,host,port,ssl);
    connect(thread,SIGNAL(started()),base,SLOT(run()));
    connect(this,SIGNAL(get20MessageSignal()),base,SLOT(get20Message()));
    connect(base,SIGNAL(MessageTopOK(Message)),this,SLOT(getMessageTop(Message)));
    connect(this,SIGNAL(getMessageSignal(int)),base,SLOT(getMessage(int)));
    connect(base,SIGNAL(MessageOK(Message)),this,SLOT(getMessage(Message)));
    connect(this,SIGNAL(update()),base,SLOT(update()));
    connect(this,SIGNAL(deleteMessage(int)),base,SLOT(deleteMessage(int)));
    connect(base,SIGNAL(Error(QString)),this,SLOT(getError(QString)));
    base->moveToThread(thread);
    thread->start();
}

void ThreadPop3::getMessageTop(Message top){
    tabl->setRowCount(tabl->rowCount()+1);
    tabl->setItem(tabl->rowCount()-1,0,new QTableWidgetItem(top.fromMes));
    tabl->setItem(tabl->rowCount()-1,1,new QTableWidgetItem(top.from));
    tabl->setItem(tabl->rowCount()-1,2,new QTableWidgetItem(top.to));
    tabl->setItem(tabl->rowCount()-1,3,new QTableWidgetItem(top.date));
    tabl->setItem(tabl->rowCount()-1,4,new QTableWidgetItem(top.head));

}

void ThreadPop3::getMessage(Message msg){
    QString end("<html><body>Пусто</html></body>");
    vie->setHtml(end);
    filelis->clear();
    filetabl->clearContents();
    filetabl->setRowCount(0);
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
            vie->setHtml(end);
        } else {
            filetabl->setRowCount(filetabl->rowCount()+1);
            filetabl->setItem(filetabl->rowCount()-1,0,new QTableWidgetItem(charset));
            filelis->append(message);
        }
    }
}

void ThreadPop3::getError(QString messsage)
{
    statu->append(messsage);
}
