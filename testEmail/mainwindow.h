#ifndef MAINWINDOW_H
#define MAINWINDOW_H


/*#include <QFile>
#include <qnetwork.h>
#include <QtNetwork/QTcpSocket>
#include <QStandardPaths>
#include <QTime>
#include <QDesktopServices>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>
#include <QVector>
#include <QStringList>
#include <QRegExp>
#include <QMessageBox>
#include <qfiledialog.h>
*/

#include <QMainWindow>
#include <QSslSocket>
#include <QAbstractSocket>
#include <QDebug>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void read();
private:
    Ui::MainWindow *ui;
    QSslSocket * socket;
    bool ok;
    QByteArray temp;
};

#endif // MAINWINDOW_H
