#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QStatusBar>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
 #include <QTableWidget>

#include "agbutton.h"
#include "exlabel.h"
#include "subwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private Q_SLOTS:
    void On_Domain_Cursor_up();
    void OnCreateLabelClicked();
    void OnOpenDomainLabelClicked();
    void OnManageDomainsLabelClicked();
    void OnOpenDomainFile();
    void OnDelDomain();
    void OnSaveDomain();
    void OnManageProxyClicked();
    void OnUrlProxyClicked();
    void OnOpenProxyClicked();
    void Mininize();
    void Maximize();
    void Normal();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
   QLabel *MainBar;
   AGButton * addNewDomain;
   SubWindow* window_options;

   AGButton* closeButton;
   AGButton* minimizeButton;
   AGButton* maximizeButton;

   AGButton* proxyButton;
   QPoint mpos;

 };

#endif // MAINWINDOW_H
