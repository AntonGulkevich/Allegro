#include "Presto.h"

Presto::Presto(QObject *parent, QString * filename) :
    QObject(parent)
{
    fileName = filename;
    warnings=0;
}
Presto::~Presto(){

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
    fillVector(ResultString);
    DBFile.close();
    return 1;
}
bool Presto::validation(){

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
void Presto::setDelimiter(const QString &del){
    delimiter= new QString(del);
}
void Presto::setDomains(QVector<Domain> * domainsVector){
    domains=domainsVector;
}
Domain* Presto::findDomain(const QString & domainName){
    return &(domains->last());

}
QString Presto::baseName(){
    return fileName->right(fileName->length()-fileName->lastIndexOf("/")-1);
}
int Presto::getWarnings(){
    return warnings;
}
