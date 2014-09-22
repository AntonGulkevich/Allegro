#include "allergomainwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AllergoMainWin w;
    w.show();

    return a.exec();
}
