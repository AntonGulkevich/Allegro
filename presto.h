#ifndef Presto_H
#define Presto_H
/* Class implementing data base*/
/*Works as a container and manipulating with data*/

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QProgressBar>
#include <QStringList>
#include <QRegExp>


#include "domain.h"
#include "account.h"
#include "pop3.h"


class Presto : public QObject
{
    Q_OBJECT
public:
    explicit Presto(QObject *parent = 0, QString * filename=NULL);
    bool openBase();
    ~Presto();
    void setProgressBar(QProgressBar * bar);
    void setDelimiter(QString* del);
    void setDomains(QVector<Domain> * domainsVector);
    QString  baseName();
    int getWarnings();
    void Check();

    QVector <Account> * goodAccountsVector;

signals:

public slots:

private:
    QString* fileName;
    QVector <Account> * accoutVector;
    QProgressBar * progressBar;
    QString* delimiter;
    QVector <Domain> * domains;


    int good;
    int bad;
    int error;
    int total;
    int warnings;

    void fillVector(const  QString& str);
    Domain* findDomain(const QString& domainName);


};

#endif // Presto_H
