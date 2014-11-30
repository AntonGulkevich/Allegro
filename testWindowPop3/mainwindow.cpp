#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pop3.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    protocol = new pop3("ivanovsergey764","qwerty123","pop.yandex.ru",995,30000);
    protocol->connectToHost();
    protocol->sendUser();
    protocol->sendPass();
    protocol->sendRetr(ui->spinBox->value());
    protocol->msg.print(ui->webView,ui->textEdit,ui->textEdit_2);


}

MainWindow::~MainWindow()
{
    protocol->sendQuit();
    delete ui;
}

void MainWindow::on_pushButtonUP_clicked()
{
    ui->spinBox->setValue(ui->spinBox->value()+1);
    protocol->sendRetr(ui->spinBox->value());
    protocol->msg.print(ui->webView,ui->textEdit,ui->textEdit_2);

}

void MainWindow::on_pushButtonDown_clicked()
{
    ui->spinBox->setValue(ui->spinBox->value()-1);
    protocol->sendRetr(ui->spinBox->value());
    protocol->msg.print(ui->webView,ui->textEdit,ui->textEdit_2);
}
