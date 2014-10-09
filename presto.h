#ifndef PRESTO_H
#define PRESTO_H
/* Class implementing pseudo data base*/
/*Works as a container and manipulating with data*/

#include <QObject>
#include <QString>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

#include "domain.h"
#include "account.h"


class presto : public QObject
{
    Q_OBJECT
public:
    explicit presto(QObject *parent = 0, const QString & filename="");
    bool openBase(QWidget * wdj);
    ~presto();

signals:

public slots:

private:
    QString* fileName;
    QVector <Account> * accoutVector;
    int goodCount;
    int badCount;
    int errorCount;
    int totalCount;

};

#endif // PRESTO_H
