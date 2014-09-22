#include "allergomainwin.h"
#include "ui_allergomainwin.h"

AllergoMainWin::AllergoMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllergoMainWin)
{
    ui->setupUi(this);
}

AllergoMainWin::~AllergoMainWin()
{
    delete ui;
}
