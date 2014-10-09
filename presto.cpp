#include "presto.h"

presto::presto(QObject *parent, const QString & filename) :
    QObject(parent)
{
    fileName = new QString(filename);
}
presto::~presto(){

}
bool presto::openBase(QWidget * wdj){
    /*Open data base*/
    QString DefaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);;
    *fileName = QFileDialog::getOpenFileName(wdj, "Open Data Base", DefaultPath+"\\base","*.txt" );
    QFile DBFile(*fileName);
    if (DBFile.open(QFile::ReadOnly)==(-1)){
        return 0;
    }
    if(!DBFile.isOpen())
        return 0;

    QString ResultString;
    ResultString=QString::fromUtf8(DBFile.readAll());
    DBFile.close();

    return 1;

}
