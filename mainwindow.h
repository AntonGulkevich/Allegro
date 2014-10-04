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

#include "agbutton.h"
#include "exlabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private Q_SLOTS:
    void DomenSetup();
    void On_Domain_Cursor_up();
    void Close();
    void OnCreateLabelClicked();
    void OnOpenDomainLabelClicked();
    void OnManageDomainsLabelClicked();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

public slots:

protected:
  bool eventFilter(QObject *, QEvent *);

private:
   bool wad_is_active;
   QLabel *MainBar;
   AGButton * addNewDomain;
   QFrame *window_add_domain;

};

#endif // MAINWINDOW_H
