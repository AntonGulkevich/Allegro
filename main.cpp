#include <QApplication>
#include <QIcon>
#include "mainwindow.h"
#include <QSplashScreen>

void loadModules(QSplashScreen* psplash)
{

    QTime time;
    time.start();

    for (int i = 0; i < 100; ) {
        if (time.elapsed() > 40) {
            time.start();
            ++i;
        }
       psplash->showMessage("Loading ... "
                             + QString::number(i) + "%",
                             Qt::AlignHCenter | Qt::AlignBottom,
                             Qt::white
                             );
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/data/clef.png"));
    /*set splash screen*/
    QSplashScreen * psplash = new QSplashScreen (QPixmap(":/data/black.png"));
    psplash->resize(800,600);
    psplash->move(400, 100);
    psplash->show();

    loadModules(psplash);
    /*set splash screen*/

    MainWindow w;
    psplash->finish(&w);


    w.show();


    return app.exec();
}
