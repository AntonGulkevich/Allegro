#include "allergomainwin.h"
#include "ui_allergomainwin.h"

AllergoMainWin::AllergoMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllergoMainWin)
{
    ui->setupUi(this);
    connect(ui->CLB, SIGNAL(clicked()),SLOT(DomenSetup()));

    QPalette pal;
//    pal.setColor(ui->DomainLabel->foregroundRole(), Qt::black);
//    ui->DomainLabel->setPalette(pal);
}

AllergoMainWin::~AllergoMainWin()
{
    delete ui;
}
void AllergoMainWin::DomenSetup(){
    ui->statusBar->showMessage("Creating a new domen");

    QWidget * WindowSetup = new QWidget(this);
    QPalette PW;
    PW.setColor(WindowSetup->backgroundRole(), Qt::black);
    WindowSetup->resize(300, 100);
    WindowSetup->move(75, 75);

    //delete WindowSetup;

}
