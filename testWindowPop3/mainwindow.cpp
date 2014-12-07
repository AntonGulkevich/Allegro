#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pop3.h"
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    protocol = new pop3("ivanovsergey764","qwerty123","pop.yandex.ru",995,30000);
    protocol->connectToHost();
    protocol->sendUser();
    protocol->sendPass();
    timer = new QTimer();
    countReal = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTCP()));
    timer->start(10000);

    ui->tableWidget->setColumnCount(6);
    QTableWidgetItem *fromName = new QTableWidgetItem("From(Name)");
    QTableWidgetItem *fromAdr = new QTableWidgetItem("From(Adr)");
    QTableWidgetItem *to = new QTableWidgetItem("To");
    QTableWidgetItem *head = new QTableWidgetItem("Head");
    QTableWidgetItem *uidl = new QTableWidgetItem("Uidl");
    QTableWidgetItem *data = new QTableWidgetItem("Data");
    ui->tableWidget->setHorizontalHeaderItem(0,fromName);
    ui->tableWidget->setHorizontalHeaderItem(1,fromAdr);
    ui->tableWidget->setHorizontalHeaderItem(2,to);
    ui->tableWidget->setHorizontalHeaderItem(3,head);
    ui->tableWidget->setHorizontalHeaderItem(4,uidl);
    ui->tableWidget->setHorizontalHeaderItem(5,data);
//    for(int j=0;j<10;j++){
//            protocol->sendRetr(j);
//
//    }
//    protocol->sendRetr(2);
//    protocol->msg.print(ui->webView);
    connect(ui->webView,SIGNAL(linkClicked(QUrl)),this,SLOT(newWindow(QUrl)));
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    protocol->sendList(ui->tableWidget,countReal);



}

MainWindow::~MainWindow()
{
    protocol->sendQuit();
    delete ui;
}

void MainWindow::on_pushButtonUP_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    countReal+=20;
    if(!protocol->sendList(ui->tableWidget,countReal))
            countReal-=20;
}

void MainWindow::on_pushButtonDown_clicked()
{
    countReal-=20;
    if(countReal==-20){
        countReal+=20;
        return;
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    protocol->sendList(ui->tableWidget,countReal);
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    int row = index.row() + 1 + countReal;
    protocol->sendRetr(row);
    protocol->msg.print(ui->webView);
}

void MainWindow::updateTCP(){
    protocol->sendNoop();
    timer->start(10000);
}

void MainWindow::newWindow(QUrl url){
    QDesktopServices::openUrl(url);
}

