#include "allergomainwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AllergoMainWin w;
    /*background*/

    QPalette main_back;
    main_back.setColor(w.backgroundRole(), Qt::white);
    w.setPalette(main_back);

    /*end background*/

    w.show();

    return a.exec();
}
