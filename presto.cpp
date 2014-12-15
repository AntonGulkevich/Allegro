#include "Presto.h"

Presto::Presto(QObject *parent, QString * filename) :
    QObject(parent)
{
    fileName = filename;
    warnings=0;
}
Presto::~Presto(){
    delete accoutVector;
}
bool Presto::openBase(){
    /*Open data base*/
    QFile DBFile(*fileName);
    if (DBFile.open(QFile::ReadOnly)==(-1)){
        return 0;
    }
    if(!DBFile.isOpen())
        return 0;
    QString ResultString;
    ResultString=QString::fromUtf8(DBFile.readAll());
    DBFile.close();

    fillVector(ResultString);
    return 1;
}
void Presto::setProgressBar(QProgressBar * bar){
    progressBar= bar;
}
void Presto::fillVector(const QString &str){
    QStringList list=str.split("\n");
    accoutVector = new QVector <Account>;
    int cur = 0;
    progressBar->setValue(cur);
    progressBar->setMaximum(list.count());

    QRegExp account ("[^"+ *delimiter +"]*["+ *delimiter +"]{1}.*");
    QString tmpStr;

    while( !list.isEmpty()){
        tmpStr= list.takeFirst();
        tmpStr=tmpStr.simplified();
        if (tmpStr=="")
            continue;
        if ((account.indexIn(tmpStr,0)==-1)&&(tmpStr!="")){
            progressBar->setValue(++cur);
            warnings++;
            continue;
        }
        Account tmpAccount(tmpStr.split(*delimiter)[0],
                tmpStr.split(*delimiter)[1]);
        tmpAccount.setDomain(findDomain(tmpAccount.getDomainName()));

        accoutVector->push_back(tmpAccount);
        progressBar->setValue(++cur);
    }
    progressBar->reset();
}
void Presto::setDelimiter(QString* del){
    delimiter= del;
}
void Presto::setDomains(QVector <Domain>* domainsVector){
    domains=domainsVector;
}
Domain* Presto::findDomain(const QString & domainName){
    for (QVector <Domain>::iterator it=domains->begin();it!=domains->end(); ++it){
        if (it->getName()== domainName){
            it->IncCount();
            return it;
            break;
        }
    }
    QVector <Domain>::iterator frst=domains->begin();
    frst->IncCount();
    return frst;
}

QString Presto::baseName(){
    return fileName->right(fileName->length()-fileName->lastIndexOf("/")-1);
}
int Presto::getWarnings(){
    return warnings;
}
void Presto::Check(){
    goodAccountsVector = new QVector <Account>;
    int cur=0;
    progressBar->setValue(cur);
    progressBar->setMaximum(accoutVector->count());

    for (QVector <Account>::iterator it=accoutVector->begin();it!=accoutVector->end(); ++it){
        if (it->GetImapHost()==""){
            continue;
            progressBar->setValue(cur++);
        }
        QString login = it->GetLogin();
        QString pas = it->GetPassword();\
        QString host = it->GetPop3Host();
        int port = it->GetPop3PortEncr();

        Pop3 *temp = new Pop3(login, pas, host,port , QSsl::SslV3);
        temp->connectToHost();

        if( temp->sendUser() ){
            qDebug()<<it->GetLogin()<<" login is correct";
            if (temp->sendPass()){
                goodAccountsVector->push_back(*it);
                qDebug()<<it->GetLogin()<<"pass is ok";
            }
            else{
                qDebug()<<it->GetLogin()<<"pass is not ok";
            }
        }
        else{
            qDebug()<<it->GetLogin()<<" login uncorect";
        }
        temp->sendQuit();

        delete temp;
        progressBar->setValue(cur++);
    }
    progressBar->reset();
}



