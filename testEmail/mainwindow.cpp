#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkProxy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(NULL),
    ok(false)
{
    ui->setupUi(this);
//    on_pushButton_clicked();
//     QNetworkProxy::setApplicationProxy(proxy);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::on_pushButton_clicked()
{
    temp.clear();
    if (socket) delete socket;
    socket = new QSslSocket(this);
    socket->setProtocol(QSsl::SslV3);

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("177.234.14.150");
    proxy.setPort(80);
    proxy.setUser("username");
    proxy.setPassword("password");
    socket->setProxy(proxy);







    socket->connectToHostEncrypted("pop.yandex.com",995);
    socket->waitForConnected();

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
//    socket->waitForConnected();

//    QString request ="USER ivanovsergey764123\r\n";
    QString request ="USER ivanovsergey764\r\n";
    socket->write(request.toUtf8());
    socket->waitForBytesWritten();

//    request ="PASS qwerty12312\r\n";
    request ="PASS qwerty123\r\n";
    socket->write(request.toUtf8());
    socket->waitForBytesWritten();

    request ="RETR "+QString::number(ui->spinBox->value())+"\r\n";

    qDebug() << request;

    socket->write(request.toUtf8());
    socket->waitForBytesWritten();

    request ="QUIT\r\n";
    socket->write(request.toUtf8());
    socket->waitForBytesWritten();

}

void MainWindow::stateChanged(QAbstractSocket::SocketState socketState) {
    qDebug() << "stateChanged " << socketState;
}

// private slot

void MainWindow::errorReceived(QAbstractSocket::SocketError socketError) {
    qDebug() << "error " << socketError;
}

// private slot

void MainWindow::disconnected() {
    qDebug() << "disconneted";
    qDebug() << "error " << socket->errorString();
}
// private slot

void MainWindow::connected() {
    qDebug() << "Connected ";
}

void MainWindow::read(){
//    socket->waitForEncrypted();
    QByteArray msg = socket->readAll();
    qDebug() << msg;
        if(msg=="+OK shutting down.\r\n") {
            ok = false;
            ui->webView->setHtml(QString(temp));
           // ui->webView->setHtml(QByteArray::fromBase64(temp));
           // ui->webView->setHtml(temp);

        }

        if(ok) temp.append(msg);
        if(msg=="    <html>\r\n") {ok=true;
        qDebug()<<"\n\n\nhui\n\n\n";}

//        ui->textEdit->append(QString(msg));}
//        ui->textEdit->setHtml(ui->textEdit->toPlainText());
//    }
}
