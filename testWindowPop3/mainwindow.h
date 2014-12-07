#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pop3.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTimer>
#include <QUrl>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT
    pop3* protocol;
    int countReal;
    QTimer *timer;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_pushButtonUP_clicked();

    void on_pushButtonDown_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void updateTCP();
    void newWindow(QUrl url);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
