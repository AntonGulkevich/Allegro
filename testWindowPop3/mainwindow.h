#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pop3.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    pop3* protocol;
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_pushButtonUP_clicked();

    void on_pushButtonDown_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
