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
#include <QSplitter>
#include <QTextEdit>
#include <QHeaderView>
#include <QCheckBox>
#include <QVector>
#include <QProgressBar>
#include <QFileDialog>


#include "agbutton.h"
#include "exlabel.h"
#include "subwindow.h"
#include "domain.h"
#include "presto.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private Q_SLOTS:
    void On_Domain_Cursor_up();
    void CreateLabelClicked();
    void OpenDomainLabelClicked();
    void ManageDomainsLabelClicked();
    void OnOpenDomainFile();
    void OnDelDomain();
    void OnSaveDomain();
    void OnOpenDomainFileClose();
    void OnCreateDomainClose();
    void OnManageDomainClose();

    void OnManageProxyClicked();    
    void OnUrlProxyClicked();    
    void OnOpenProxyClicked();
    void OnCloseUrl();
    void OnCloseManageProxy();
    void OnCloseOpenProxy();
    void OnOpenProxyFile();

    void FullBase();
    void GoodBase();
    void SearchBase();
    void OnFullBaseClose();
    void OnGoodBaseClose();
    void OnSearchBaseClose();
    void OnOpenDataFileCLB();
    void OnCloseDataFileCLB();
    void OnCheckDataFileCLB();

    void OnDomainButtonClicked();
    void OnProxyButtonClicked();
    void OnBaseButtonClicked();

    void Mininize();
    void Maximize();
    void Normal();




public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupVectorDomains();
    void closeWindowIfOpened();

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
   /*GUI*/
   QLabel *MainBar;
   SubWindow* window_options;

   AGButton* addNewDomain;
   AGButton* baseButton;
   AGButton* proxyButton;

   AGButton* closeButton;
   AGButton* minimizeButton;
   AGButton* maximizeButton;

   QTableWidget* domainsAccount;
   QProgressBar * progressBar;

   QPoint mpos;

   QLineEdit* delLE;
   /*END of GUI*/


   /*LOGIC*/

   QVector <Domain> *domainVect;

   Presto * fullDataBase;
   QString  delimiter;

   bool pop3TSL;
   bool pop3SSL;
   bool imapTSL;
   bool imapSSL;

   QCheckBox* usePOP3TSL;
   QCheckBox* usePOP3SSL;
   QCheckBox* useIMAPTSL;
   QCheckBox* useIMAPSSL;

   /*END of LOGIC*/

   /*TEST*/

   QTextEdit* test1;

   /*END of TEST*/

 };

#endif // MAINWINDOW_H
