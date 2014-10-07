#include <QApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/data/clef.png"));
    MainWindow w;
    w.show();


    return app.exec();
}
