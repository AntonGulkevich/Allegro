#include <QApplication>
#include <QFrame>
#include <QBoxLayout>
#include <QPalette>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
