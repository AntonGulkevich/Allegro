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
#include <QErrorMessage>
#include <QWebView>

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
    void OnAddDomainClicked();
    void OnCellClicked(int a, int b);

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

    void UpdateSelection();




public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupVectorDomains();
    void closeWindowIfOpened();
    void updateDomainTable();
    void updateDomainVector(int pos, bool state);
    bool checkLineEdit(QLineEdit* lineEdit);

    void setupWindowDomainManage(QWidget *prnt);
    void setupWindowDomainOpen (QWidget *prnt);
    void setupWindowDomainCreate (QWidget *prnt);

    void setupWindowProxyUrl (QWidget *prnt);
    void setupWindowProxyFile (QWidget *prnt);
    void setupWindowProxyManage (QWidget *prnt);

    void setupWindowBaseFull(QWidget *prnt);
    void setupWindowBaseGood (QWidget *prnt);
    void setupWindowBaseSearch (QWidget *prnt);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
   /*GUI*/
   QLabel *MainBar;

   SubWindow* activeWindow;

   SubWindow* windowDomainManage;
   SubWindow* windowDomainOpen;
   SubWindow* windowDomainCreate;

   SubWindow* windowProxyUrl;
   SubWindow* windowProxyFile;
   SubWindow* windowProxyManage;

   SubWindow* windowBaseFull;
   SubWindow* windowBaseGood;
   SubWindow* windowBaseSearch;

   AGButton* addNewDomain;
   AGButton* baseButton;
   AGButton* proxyButton;

   AGButton* closeButton;
   AGButton* minimizeButton;
   AGButton* maximizeButton;

   QTableWidget* domainsAccount;
   QProgressBar* progressBar;

   QPoint mpos;

   QLineEdit* delLE;

   AGButton* saveDomain;
   AGButton* delDomain;
   /*END of GUI*/


   /*LOGIC*/

   QVector <Domain>* domainVect;
   QTableWidget* DomainTable;
   QLabel* fullBaseFileName;
   AGButton* checkDataFileCLB;
   AGButton* closeDataFileCLB;

   QLineEdit* d_name_le;
   QLineEdit *d_pop3_host_le;
   QLineEdit *d_pop3_port_le;
   QLineEdit *d_imap_host_le;
   QLineEdit *d_imap_port_le;
   QLineEdit *d_noEncr_pop3_port_le;
   QLineEdit *d_noEncr_imap_port_le;


   Presto* fullDataBase;
   QString  delimiter;

   bool pop3;
   bool imap;
   bool TSLSSL;
   bool encrNone;

   bool useURLproxy;
   bool useFILEproxy;

   QCheckBox* useIMAP;
   QCheckBox* usePOP3;
   QCheckBox* useTSLSSL;
   QCheckBox* useNone;

   QCheckBox* useUrlCB;
   QCheckBox* useFileCB;

   int selectedRow;//returns selected row from "Domain Table"
   QLabel* domainFileName;

   /*END of LOGIC*/

   /*TEST*/

   /*END of TEST*/

 };

#endif // MAINWINDOW_H
