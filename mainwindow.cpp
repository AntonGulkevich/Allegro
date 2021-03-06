#include "mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    QFrame *mainframe = new QFrame();
    /*Default settings*/
    fullDataBase=NULL;
    delimiter= ":";
    domainVect=NULL;
    domainVect= new QVector<Domain>;

    Domain unknownDomain("Unknown");
    domainVect->push_back(unknownDomain);

    useImap=true;
    usePop3=true;
    useTSLSSL=true;
    useEncrNone=false;

    useURLproxy=false;
    useFILEproxy=false;


    /*end of deault settings*/

    QPalette PW/*main*/,
            EB/*active*/ ,
            DP/*default*/,
            SB/*statusbar palette*/;
    PW.setColor(backgroundRole(), Qt::white);
    mainframe->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setCentralWidget(mainframe);
    setAutoFillBackground(true);
    setPalette(PW);
    resize(800,600);
    move(400, 100);
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(500, 550);

    /*setup status bar*/
    progressBar = new QProgressBar;
    MainBar = new QLabel;
    QFrame* statusBarFrame= new QFrame;
    statusBarFrame->setAutoFillBackground(true);
    SB.setColor(backgroundRole(), Qt::gray);
    SB.setColor(foregroundRole(), Qt::black);
    statusBarFrame->setPalette(SB);
    QBoxLayout* statusBarLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    statusBarLayout->setSpacing(10);
    statusBarLayout->setMargin(0);
    MainBar->setMaximumWidth(250);
    MainBar->setMinimumWidth(250);

    statusBarLayout->addWidget(MainBar, 1);
    statusBarLayout->addWidget(progressBar,2);
    statusBar()->setContentsMargins(0, 0, 0, 0);
    statusBar()->setPalette(SB);
    statusBar()->setAutoFillBackground(true);
    statusBarFrame->setLayout(statusBarLayout);
    progressBar->setPalette(SB);
    progressBar->reset();

    statusBar()->addWidget(statusBarFrame, 1);

    progressBar->setStyleSheet("QProgressBar {"
                               "border: 2px solid grey;"
                               "border-radius: 5px;"
                               "text-align: center;}"

                               "QProgressBar::chunk {"
                               "background-color: #CD96CD;"
                               "}"  );
    MainBar->setAutoFillBackground(true);
    MainBar->setPalette(SB);
    MainBar->setText("Setup domains, proxy and open the base...");
    /*end of setup status bar*/

    /*setup left buttons*/
    addNewDomain= new AGButton(centralWidget());
    addNewDomain->setIconOnEnter(QIcon(":/data/down_sel.png"));
    addNewDomain->setIconOnLeave(QIcon(":/data/down_def.png"));
    addNewDomain->setText("Domains");
    addNewDomain->setIconSize(QSize(25, 25));
    addNewDomain->setMaximumSize(110, 40);
    addNewDomain->setHint("Manage list of domains...");

    proxyButton= new AGButton(centralWidget());
    proxyButton->setIconOnEnter(QIcon(":/data/down_sel.png"));
    proxyButton->setIconOnLeave(QIcon(":/data/down_def.png"));
    proxyButton->setText("Proxy");
    proxyButton->setIconSize(QSize(25, 25));
    proxyButton->setMaximumSize(110, 40);
    proxyButton->setHint("Manage list of proxy...");

    baseButton= new AGButton(centralWidget());
    baseButton->resize(110, 40);
    baseButton->setIconOnEnter(QIcon(":/data/down_sel.png"));
    baseButton->setIconOnLeave(QIcon(":/data/down_def.png"));
    baseButton->setText("Accounts");
    baseButton->setIconSize(QSize(25, 25));
    baseButton->setMaximumSize(110, 40);
    baseButton->setHint("Manage bases: open, close, save and etc...");

    /*setup control top buttons*/

    closeButton= new AGButton(centralWidget());
    closeButton->setIconOnEnter(QIcon(":/data/close_sel.png"));
    closeButton->setIconOnLeave(QIcon(":/data/close_def.png"));
    closeButton->setText("");
    closeButton->setIconSize(QSize(20, 20));
    closeButton->setMaximumSize(35, 35);
    closeButton->setMinimumSize(35, 35);
    closeButton->setHint("Close the application.");
    EB.setColor(closeButton->backgroundRole(), Qt::red);
    DP.setColor(closeButton->backgroundRole(), Qt::white);
    closeButton->setActivePalette(EB);
    closeButton->setDefaultPalette(DP);


    minimizeButton= new AGButton(centralWidget());
    minimizeButton->setIconOnEnter(QIcon(":/data/min_sel.png"));
    minimizeButton->setIconOnLeave(QIcon(":/data/min_def.png"));
    minimizeButton->setText("");
    minimizeButton->setIconSize(QSize(20, 20));
    minimizeButton->setMaximumSize(35, 35);
    minimizeButton->setMinimumSize(35, 35);
    minimizeButton->setHint("Minimize the application.");

    maximizeButton= new AGButton(centralWidget());
    maximizeButton->setIconOnEnter(QIcon(":/data/max_sel.png"));
    maximizeButton->setIconOnLeave(QIcon(":/data/max_def.png"));
    maximizeButton->setText("");
    maximizeButton->setIconSize(QSize(20, 20));
    maximizeButton->setMaximumSize(35, 35);
    maximizeButton->setMinimumSize(35, 35);
    maximizeButton->setHint("Maximize the application.");

    QFrame *v_line = new QFrame();
    v_line->setFrameStyle(QFrame::VLine| QFrame::Raised);
    v_line->setLineWidth(1);

    /*direction and positions*/

    QBoxLayout* mainlay = new QBoxLayout(QBoxLayout::TopToBottom, mainframe);
    QBoxLayout* cblay= new QBoxLayout(QBoxLayout::RightToLeft);
    QBoxLayout* buttonsLeftLay= new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* smainlay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* tablelay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* contrButtonsLay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* contrButtonsListLay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* contrButtonsMessageLay = new QBoxLayout(QBoxLayout::LeftToRight);

    /*setup controll buttons for mail*/

    AGButton *backToList = new AGButton(centralWidget());
    backToList->setIconOnEnter(QIcon(":/data/home_sel.png"));
    backToList->setIconOnLeave(QIcon(":/data/home_def.png"));
    backToList->setText("");
    backToList->setIconSize(QSize(25, 25));
    backToList->setMaximumSize(40, 40);
    backToList->setHint("Back to e-mails list");

    AGButton *searchInEmail = new AGButton(centralWidget());
    searchInEmail->setIconOnEnter(QIcon(":/data/search_sel.png"));
    searchInEmail->setIconOnLeave(QIcon(":/data/search_def.png"));
    searchInEmail->setText("");
    searchInEmail->setIconSize(QSize(25, 25));
    searchInEmail->setMaximumSize(40, 40);
    searchInEmail->setHint("Search in e-mails");

    AGButton *previousMessage = new AGButton(centralWidget());
    previousMessage->setIconOnEnter(QIcon(":/data/right_sel.png"));
    previousMessage->setIconOnLeave(QIcon(":/data/right_def.png"));
    previousMessage->setText("");
    previousMessage->setIconSize(QSize(25, 25));
    previousMessage->setMaximumSize(40, 40);
    previousMessage->setHint("Previous message");

    AGButton *nextMessage = new AGButton(centralWidget());
    nextMessage->setIconOnEnter(QIcon(":/data/left_sel.png"));
    nextMessage->setIconOnLeave(QIcon(":/data/left_def.png"));
    nextMessage->setText("");
    nextMessage->setIconSize(QSize(25, 25));
    nextMessage->setMaximumSize(40, 40);
    nextMessage->setHint("Next message");

    contrButtonsLay->addWidget(previousMessage, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsLay->addWidget(nextMessage, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsLay->addWidget(searchInEmail, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsLay->addWidget(backToList, 0,Qt::AlignLeft |Qt::AlignTop);

    contrButtonsLay->addStretch(1);


    /*end of setup controll buttons for mail*/

    /*setup controll buttons for list of emails*/

    AGButton *writeEmail = new AGButton(centralWidget());
    writeEmail->setIconOnEnter(QIcon(":/data/write_sel.png"));
    writeEmail->setIconOnLeave(QIcon(":/data/write_def.png"));
    writeEmail->setText("");
    writeEmail->setIconSize(QSize(25, 25));
    writeEmail->setMaximumSize(40, 40);
    writeEmail->setHint("Write an e-mail");

    AGButton *refresh = new AGButton(centralWidget());
    refresh->setIconOnEnter(QIcon(":/data/refresh_sel.png"));
    refresh->setIconOnLeave(QIcon(":/data/refresh_def.png"));
    refresh->setText("");
    refresh->setIconSize(QSize(25, 25));
    refresh->setMaximumSize(40, 40);
    refresh->setHint("Refresh list of email from the beggining");

    AGButton *searchInList = new AGButton(centralWidget());
    searchInList->setIconOnEnter(QIcon(":/data/search_sel.png"));
    searchInList->setIconOnLeave(QIcon(":/data/search_def.png"));
    searchInList->setText("");
    searchInList->setIconSize(QSize(25, 25));
    searchInList->setMaximumSize(40, 40);
    searchInList->setHint("Search in list");

    AGButton *loadNextMessages = new AGButton(centralWidget());
    loadNextMessages->setIconOnEnter(QIcon(":/data/next_sel.png"));
    loadNextMessages->setIconOnLeave(QIcon(":/data/next_def.png"));
    loadNextMessages->setText("");
    loadNextMessages->setIconSize(QSize(25, 25));
    loadNextMessages->setMaximumSize(40, 40);
    loadNextMessages->setHint("Load next messages");

    AGButton *deleteMessageButton = new AGButton(centralWidget());
    deleteMessageButton->setIconOnEnter(QIcon(":/data/close_sel.png"));
    deleteMessageButton->setIconOnLeave(QIcon(":/data/close_def.png"));
    deleteMessageButton->setText("");
    deleteMessageButton->setIconSize(QSize(25, 25));
    deleteMessageButton->setMaximumSize(40, 40);
    deleteMessageButton->setHint("Delete message");

    contrButtonsListLay->addWidget(writeEmail, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsListLay->addWidget(refresh, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsListLay->addWidget(searchInList, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsListLay->addWidget(loadNextMessages, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsListLay->addWidget(deleteMessageButton, 0,Qt::AlignLeft |Qt::AlignTop);

    contrButtonsListLay->addStretch(1);


    /*end of setup controll buttons for list of emails*/

    /*setup controll buttons for new message*/

    AGButton *sendEmail = new AGButton(centralWidget());
    sendEmail->setIconOnEnter(QIcon(":/data/send_sel.png"));
    sendEmail->setIconOnLeave(QIcon(":/data/send_def.png"));
    sendEmail->setText("");
    sendEmail->setIconSize(QSize(25, 25));
    sendEmail->setMaximumSize(40, 40);
    sendEmail->setHint("Send an e-mail");

    AGButton *attachment = new AGButton(centralWidget());
    attachment->setIconOnEnter(QIcon(":/data/attachment_sel.png"));
    attachment->setIconOnLeave(QIcon(":/data/attachment_def.png"));
    attachment->setText("");
    attachment->setIconSize(QSize(25, 25));
    attachment->setMaximumSize(40, 40);
    attachment->setHint("Add an attachment");

    AGButton *backToList2 = new AGButton(centralWidget());
    backToList2->setIconOnEnter(QIcon(":/data/home_sel.png"));
    backToList2->setIconOnLeave(QIcon(":/data/home_def.png"));
    backToList2->setText("");
    backToList2->setIconSize(QSize(25, 25));
    backToList2->setMaximumSize(40, 40);
    backToList2->setHint("Back to e-mails list");


    contrButtonsMessageLay->addWidget(sendEmail, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsMessageLay->addWidget(attachment, 0,Qt::AlignLeft |Qt::AlignTop);
    contrButtonsMessageLay->addWidget(backToList2, 0,Qt::AlignLeft |Qt::AlignTop);

    contrButtonsMessageLay->addStretch(1);


    /*end of setup controll buttons for new message*/


    /*search in emil setup*/
    searchBox = new QLineEdit();
    word = new QString;
    searchEmailWidget = new QWidget;
    QBoxLayout * searchLay = new QBoxLayout(QBoxLayout::LeftToRight);

    searchLay->addWidget(searchBox, 1);

    searchEmailWidget->setLayout(searchLay);
    searchEmailWidget->hide();

    connect(searchBox,SIGNAL(returnPressed()),this, SLOT(scanPageForWord()));
    /* end of search in emil setup*/


    /*setup of qwebwie*/

    tabsForWork = new QTabWidget(centralWidget());

    QBoxLayout * tabsLay = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout * tabEmailLay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout * tabListLay = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout * emailLay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout * listLay = new QBoxLayout(QBoxLayout::TopToBottom);

    QWidget * emailTab = new QWidget;
    QWidget * listTab = new QWidget;
    /*setup email table*/
    emailsTable= new QTableWidget();
    fileTable = new QTableWidget();

    connect(emailsTable, SIGNAL(cellDoubleClicked(int,int)), SLOT(OnEmailCliked(int,int)));
    connect(fileTable, SIGNAL(cellDoubleClicked(int,int)), SLOT(OnAttachmentSave(int,int)));

    /*end of setup email table*/

    ViewFrame =new QWebView(centralWidget());

    /*setup tabs layouts*/


    tabEmailLay->addLayout(contrButtonsLay, 0);
    tabEmailLay->addLayout(emailLay, 1);
    emailLay->addWidget(searchEmailWidget, 0);
    emailLay->addWidget(ViewFrame, 6);
    emailLay->addWidget(fileTable, 1);
    emailTab->setLayout(tabEmailLay);

    tabListLay->addLayout(contrButtonsListLay, 0);
    tabListLay->addLayout(listLay, 1);
    listLay->addWidget(emailsTable, 1);
    listTab->setLayout(tabListLay);


    QWidget *tabWrite = new QWidget;
    QBoxLayout * tabWriteLay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout * writeLay = new QBoxLayout(QBoxLayout::TopToBottom);

    /*setup write widget*/

    recipientsEdit = new QLineEdit;
    recipientsEdit->setPlaceholderText("Recipients");
    recipientsEdit->setStyleSheet("QLineEdit { border: none }");
    themeEdit = new QLineEdit;
    themeEdit->setPlaceholderText("Theme");
    themeEdit->setStyleSheet("QLineEdit { border: none }");
    textEdit = new QTextEdit;
    textEdit->setStyleSheet("QTextEdit { border: none}");
    attachmentsLabel = new QLabel("Attachments: ");

    loginEdit = new QLineEdit;
    loginEdit->setPlaceholderText("Login");
    loginEdit->setStyleSheet("QLineEdit { border: none }");

    passEdit = new QLineEdit;
    passEdit->setPlaceholderText("Password");
    passEdit->setStyleSheet("QLineEdit { border: none }");


    QFrame *hor_line4 = new QFrame;
    hor_line4->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line4->setLineWidth(1);
    hor_line4->setMaximumHeight(5);

    QFrame *hor_line5 = new QFrame;
    hor_line5->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line5->setLineWidth(1);
    hor_line5->setMaximumHeight(5);

    QFrame *hor_line6 = new QFrame;
    hor_line6->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line6->setLineWidth(1);
    hor_line6->setMaximumHeight(5);

    QFrame *hor_line7 = new QFrame;
    hor_line7->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line7->setLineWidth(1);
    hor_line7->setMaximumHeight(5);

    QBoxLayout * authLay = new QBoxLayout(QBoxLayout::LeftToRight);

    authLay->addWidget(loginEdit, 1);
    authLay->addWidget(passEdit, 1);

    writeLay->addLayout(authLay,0);

    writeLay->addWidget(hor_line7, 0);

    writeLay->addWidget(recipientsEdit, 0);
    writeLay->addWidget(hor_line4, 0);
    writeLay->addWidget(themeEdit, 0);
    writeLay->addWidget(hor_line5, 0);

    writeLay->addWidget(textEdit, 1);
    writeLay->addWidget(hor_line6, 0);
    writeLay->addWidget(attachmentsLabel, 0);


    /*end of setup write widget*/


    tabWriteLay->addLayout(contrButtonsMessageLay, 0);
    tabWriteLay->addLayout(writeLay, 1);
    tabWrite->setLayout(tabWriteLay);


    tabsForWork->addTab(emailTab,"Email"); //tab for email view
    tabsForWork->addTab(listTab, "Test"); // tab for list of emails
    tabsForWork->addTab(tabWrite, "New Message"); // tab for new message
    tabsForWork->tabBar()->setVisible(false);
    tabsForWork->setStyleSheet("QTabWidget { border: none }");

    tabsForWork->tabBar()->setCurrentIndex(1);
    /*
    list of indexes
    0-email
    1-list of email
    2-send email
    */


    tabsLay->addWidget(tabsForWork, 1);
    /*end of setup of qwebwie*/

    mainlay->setSpacing(10);
    mainlay->setMargin(0);
    smainlay->setSpacing(0);
    smainlay->setMargin(0);
    cblay->setSpacing(0);
    cblay->setMargin(0);
    buttonsLeftLay->setSpacing(10);
    buttonsLeftLay->setMargin(20);
    tablelay->setSpacing(10);
    tablelay->setMargin(10);

    cblay->addWidget(closeButton, 0,Qt::AlignRight |Qt::AlignTop);
    cblay->addWidget(maximizeButton, 0,Qt::AlignRight |Qt::AlignTop);
    cblay->addWidget(minimizeButton, 0,Qt::AlignRight |Qt::AlignTop);
    cblay->addStretch(1);

    buttonsLeftLay->addWidget(addNewDomain, 0,Qt::AlignLeft |Qt::AlignTop);
    buttonsLeftLay->addWidget(proxyButton,  0,Qt::AlignLeft |Qt::AlignTop);
    buttonsLeftLay->addWidget(baseButton, 0,Qt::AlignLeft |Qt::AlignTop);
    buttonsLeftLay->addStretch(1);

    tablelay->addWidget(v_line);
    tablelay->addLayout(tabsLay);

    QWidget * leftButtonsWidget = new QWidget;
    leftButtonsWidget->setLayout(buttonsLeftLay);

    smainlay->addWidget(leftButtonsWidget, 0);
    smainlay->addLayout(tablelay, 1);

    mainlay->addLayout(cblay);
    mainlay->addLayout(smainlay);

    connect(closeButton, SIGNAL(clicked()), SLOT(close()));
    connect(minimizeButton, SIGNAL(clicked()), SLOT(Mininize()));
    connect(maximizeButton, SIGNAL(clicked()), SLOT(Maximize()));

    connect(addNewDomain, SIGNAL(clicked()), SLOT(OnDomainButtonClicked()));
    connect(proxyButton, SIGNAL(clicked()), SLOT(OnProxyButtonClicked()));
    connect(baseButton, SIGNAL(clicked()), SLOT(OnBaseButtonClicked()));

    connect(backToList, SIGNAL(clicked()), SLOT(OnHomeButtonClicked()));
    connect(backToList2, SIGNAL(clicked()), SLOT(OnHomeButtonClicked()));
    connect(searchInEmail, SIGNAL(clicked()), SLOT(OnSearchButtonClicked()));
    connect(previousMessage, SIGNAL(clicked()), SLOT(OnPreviousButtonClicked()));
    connect(nextMessage, SIGNAL(clicked()), SLOT(OnNextButtonClicked()));
    connect(loadNextMessages, SIGNAL(clicked()), SLOT(OnLoadNextMessages()));
    connect(writeEmail, SIGNAL(clicked()), SLOT(OnWriteButtonClicked()));
    connect(sendEmail, SIGNAL(clicked()), SLOT(OnSendMessageClicked()));
    connect(attachment, SIGNAL(clicked()), SLOT(OnAddAttachmentsClicked()));
    connect(refresh, SIGNAL(clicked()), SLOT(OnRefreshClicked()));
    connect(deleteMessageButton, SIGNAL(clicked()), SLOT(onDelMessage()));


    connect(addNewDomain, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(proxyButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(baseButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(closeButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(minimizeButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(maximizeButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(backToList, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(searchInEmail, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(previousMessage, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(nextMessage, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(writeEmail, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(refresh, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(searchInList, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(loadNextMessages, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(sendEmail, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(attachment, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(backToList2, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(deleteMessageButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));


    /*Setup subwindows*/
    activeWindow=NULL;

    windowDomainManage=NULL;
    windowDomainOpen=NULL;
    windowDomainCreate=NULL;

    windowProxyUrl= NULL;
    windowProxyFile= NULL;
    windowProxyManage= NULL;

    windowBaseFull= NULL;
    windowBaseGood= NULL;
    windowBaseSearch= NULL;

    /*end of setup subwindows*/
    messageEdit = new QTextEdit();

    fileTable->setColumnCount(1);
    fileTable->verticalHeader()->hide();
    fileTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    fileTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    fileTable->horizontalHeader()->hide();
    fileTable->setVisible(true);


    emailsTable->setColumnCount(5);
    emailsTable->setHorizontalHeaderItem(0,new QTableWidgetItem("From(Name)") );
    emailsTable->setHorizontalHeaderItem(1,new QTableWidgetItem("From(Adr)") );
    emailsTable->setHorizontalHeaderItem(2,new QTableWidgetItem("To") );
    emailsTable->setHorizontalHeaderItem(3,new QTableWidgetItem("Data") );
    emailsTable->setHorizontalHeaderItem(4,new QTableWidgetItem("Head") );
    emailsTable->setFrameStyle(0);
    emailsTable->verticalHeader()->hide();
    emailsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    emailsTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    emailsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //emailsTable->setSelectionMode(QAbstractItemView::NoSelection);
    emailsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    emailsTable->horizontalHeader()->setStretchLastSection(true);
    emailsTable->setVisible(true);

    connect(ViewFrame,SIGNAL(linkClicked(QUrl)),this,SLOT(newWindow(QUrl)));
    ViewFrame->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

}
MainWindow::~MainWindow()
{
}
void MainWindow::On_Domain_Cursor_up(){


}
void MainWindow::OnSendMessageClicked(){

    QString login=loginEdit->text();
    QString password=passEdit->text();

    QString hostsmtp="smtp."+login.right(login.length()-login.indexOf("@")-1);
    int port=465;

    Smtp* smtp = new Smtp(login, password, hostsmtp, port);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(login, recipientsEdit->text() , themeEdit->text(),textEdit->toPlainText(), files );
    else
        smtp->sendMail(login, recipientsEdit->text() , themeEdit->text(),textEdit->toPlainText());


}
void MainWindow::mailSent(QString text){

}
void MainWindow::OnAddAttachmentsClicked(){
    files.clear();
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    attachmentsLabel->setText( fileListString );
}
void MainWindow::CreateLabelClicked(){
    closeWindowIfOpened();
    MainBar->setText("Create a new domain");
    activeWindow=windowDomainCreate;
    windowDomainCreate->show();

}
void MainWindow::OpenDomainLabelClicked(){
    closeWindowIfOpened();
    MainBar->setText("Open file with domain list");
    activeWindow=windowDomainOpen;
    windowDomainOpen->show();

}
void MainWindow::ManageDomainsLabelClicked(){
    closeWindowIfOpened();
    updateDomainTable();

    if (domainVect->isEmpty()){
        saveDomain->setEnabled(false);
    }
    else
        saveDomain->setEnabled(true);
    MainBar->setText("Manage your domains");
    activeWindow=windowDomainManage;
    windowDomainManage->show();

}
void MainWindow::OnOpenDomainFile(){
    closeWindowIfOpened();
    MainBar->setText("Choose file with domains list");

    QString fileName =QFileDialog::getOpenFileName(this,
                                                   tr("Open domains"), "domains.mdf",
                                                   tr("Domains (*.mdf);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            MainBar->setText("Unable to open file");
            file.close();
            return;
        }
        QDataStream in(&file);

        int count;
        in>>count;

        domainVect->clear();
        /*
        Domain unknownDomain("Unknown");
        domainVect->push_back(unknownDomain);
        */
        while (count--){
            Domain temp;
            in>>temp;
            domainVect->push_back(temp);
        }


        file.close();
    }
    domainFileName->setText(fileName.right(fileName.length()-fileName.lastIndexOf("/")-1));

}
void MainWindow::OnDelDomain(){    
    domainVect->remove(selectedRow);
    updateDomainTable();
    delDomain->setEnabled(false);
    MainBar->setText("Domain deleted");
}
void MainWindow::OnSaveDomain(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save domains"), "domains.mdf",
                                                    tr("Domains (*.mdf);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            MainBar->setText("Unable to open file");
            file.close();
            return;
        }
        QDataStream out(&file);
        out<<int(domainVect->count());
        for (QVector<Domain>::iterator it = domainVect->begin(); it!=domainVect->end(); ++it){
            out<<*it;
        }

        file.close();

    }
    MainBar->setText("Domains saved to file");
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    mpos=event->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent * )
{
    qDebug()<<mpos.x();
    qDebug()<<mpos.y();


    if(activeWindow){
        int leftX, leftY, botX, botY;

        leftX=activeWindow->pos().x();
        leftY=activeWindow->pos().y();
        botX=leftX+activeWindow->width();
        botY=leftY+activeWindow->height();

        if(mpos.x()>botX||mpos.x()<leftX||mpos.y()>botY||mpos.y()<leftY){
            closeWindowIfOpened();
        }

    }
    mpos = QPoint(-1, -1);
}
void MainWindow::OnManageProxyClicked(){
    closeWindowIfOpened();
    MainBar->setText("Manage proxy");
    activeWindow=windowProxyManage;
    windowProxyManage->show();

}
void MainWindow::OnUrlProxyClicked(){
    closeWindowIfOpened();
    MainBar->setText("Connect url with proxy");
    activeWindow=windowProxyUrl;
    windowProxyUrl->show();

}
void MainWindow::OnOpenProxyClicked(){
    closeWindowIfOpened();
    MainBar->setText("Open proxy list");
    activeWindow=windowProxyFile;
    windowProxyFile->show();

}
void MainWindow::Mininize(){
    showMinimized();
}
void MainWindow::Maximize(){
    showMaximized();
    maximizeButton->setIconOnEnter(QIcon(":/data/minimize_sel.png"));
    maximizeButton->setIconOnLeave(QIcon(":/data/minimize_def.png"));

    connect(maximizeButton, SIGNAL(clicked()), SLOT(Normal()));
}
void MainWindow::Normal(){
    showNormal();
    maximizeButton->setIconOnEnter(QIcon(":/data/max_sel.png"));
    maximizeButton->setIconOnLeave(QIcon(":/data/max_def.png"));
    connect(maximizeButton, SIGNAL(clicked()), SLOT(Maximize()));
}
void MainWindow::setupVectorDomains(){


}
void MainWindow::FullBase(){
    closeWindowIfOpened();
    MainBar->setText("Manage current base");
    activeWindow=windowBaseFull;
    windowBaseFull->show();


}
void MainWindow::GoodBase(){
    closeWindowIfOpened();
    MainBar->setText("Manage base with doog account");
    activeWindow=windowBaseGood;
    windowBaseGood->show();
}
void MainWindow::SearchBase(){
    closeWindowIfOpened();
    MainBar->setText("Manage search results");
    activeWindow=windowBaseSearch;
    windowBaseSearch->show();

}
void MainWindow::OnCloseUrl(){
    qDebug()<<"OnCloseUrlSetup";
}
void MainWindow::OnCloseManageProxy(){
    qDebug()<<"OnCloseManageProxy";

    useURLproxy=useUrlCB->checkState();
    useFILEproxy=useFileCB->checkState();
}
void MainWindow::OnCloseOpenProxy(){
    qDebug()<<"OnCloseOpenProxy";
}
void MainWindow::OnFullBaseClose(){
    qDebug()<<"OnFullBaseClose";
    delimiter=delLE->text();

    usePop3=usePOP3CB->checkState();
    useImap=useIMAPCB->checkState();
    useEncrNone=useNoneCB->checkState();
    useTSLSSL=useTSLSSLCB->checkState();
}
void MainWindow::OnGoodBaseClose(){
    qDebug()<<"OnGoodBaseClose";
}
void MainWindow::OnSearchBaseClose(){
    qDebug()<<"OnSearchBaseClose";
}
void MainWindow::OnOpenDomainFileClose(){
    qDebug()<<"OnOpenDomainFileClose";
}
void MainWindow::OnManageDomainClose(){
    qDebug()<<"OnManageDomainClose";
}
void MainWindow::OnCreateDomainClose(){
    qDebug()<<"OnCreateDomainClose";
}
void MainWindow::OnDomainButtonClicked(){
    if (windowDomainManage==NULL){
        setupWindowDomainManage(this);
        setupWindowDomainOpen(this);
        setupWindowDomainCreate(this);
    }

    if (windowDomainCreate->isHidden()) {
        CreateLabelClicked();
    }
    else{
        windowDomainCreate->hide();
    }
}
void MainWindow::OnBaseButtonClicked(){
    if (windowBaseFull==NULL){
        setupWindowBaseFull(this);
        setupWindowBaseGood(this);
        setupWindowBaseSearch(this);
    }

    if (windowBaseFull->isHidden()) {
        FullBase();
    }
    else{
        windowBaseFull->hide();
    }

}
void MainWindow::OnProxyButtonClicked(){
    if (windowProxyManage==NULL){
        setupWindowProxyFile(this);
        setupWindowProxyManage(this);
        setupWindowProxyUrl(this);
    }

    if (windowProxyManage->isHidden()) {
        OnManageProxyClicked();
    }
    else{
        windowProxyManage->hide();
    }

}
void MainWindow::closeWindowIfOpened(){
    if (activeWindow){
        activeWindow->hide();
    }
}
void MainWindow::OnOpenProxyFile(){


}
void MainWindow::OnOpenDataFileCLB(){
    closeWindowIfOpened();
    /*Open data base*/
    if (fullDataBase!=NULL){
        OnCloseDataFileCLB();
    }

    QString DefaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);;
    QString *fileName = new QString(QFileDialog::getOpenFileName(this, "Open Data Base", DefaultPath+"\\base","*.txt" ));

    if(*fileName==""){
        delete fullDataBase;
        fullDataBase=NULL;
        return;
    }

    fullDataBase= new Presto(this, fileName);

    fullDataBase->setProgressBar(progressBar);
    fullDataBase->setDelimiter(&delimiter);
    fullDataBase->setDomains(domainVect);
    fullDataBase->openBase();

    fullBaseFileName->setText(fullDataBase->baseName());
    checkDataFileCLB->setEnabled(true);
    closeDataFileCLB->setEnabled(true);

    MainBar->setText("Base opened, warnings: " +QString::number(fullDataBase->getWarnings()));
}
void MainWindow::OnCloseDataFileCLB(){
    closeWindowIfOpened();

    fullBaseFileName->setText("none");
    checkDataFileCLB->setEnabled(false);
    closeDataFileCLB->setEnabled(false);

    MainBar->setText(fullDataBase->baseName()+" closed.");
    delete fullDataBase;
    fullDataBase=NULL;
    for(QVector<Domain>::iterator it = domainVect->begin(); it!=domainVect->end(); ++it){
        it->SetZeroCount();
    }

}
void MainWindow::OnCheckDataFileCLB(){
    closeWindowIfOpened();

    for(QVector<Domain>::iterator it = domainVect->begin(); it!=domainVect->end(); ++it){
        qDebug()<<it->getName()<<it->GetCount();
    }
    fullDataBase->Check();
    for(QVector<Account>::iterator it=fullDataBase->goodAccountsVector->begin(); it!=fullDataBase->goodAccountsVector->end(); ++it){
        QString login=it->GetLogin();
        QString pas=it->GetPassword();
        QString host=it->GetPop3Host();
        int port=it->GetPop3PortEncr();
        protocol = new ThreadPop3(&fileList,emailsTable,ViewFrame,messageEdit,fileTable,login,pas,host,port,QSsl::SslV3);
        emit protocol->get20MessageSignal();
    }

}
void MainWindow::setupWindowDomainCreate(QWidget *prnt){

    windowDomainCreate = new SubWindow(prnt, "CREATE", "OPEN", "MANAGE", 300, 300);
    windowDomainCreate->move(addNewDomain->pos().x(), addNewDomain->pos().y()+100);
    windowDomainCreate->SetActiveFirstLabel(true);

    connect(windowDomainCreate, SIGNAL(OnSecondLabelClicked()), SLOT(OpenDomainLabelClicked()));
    connect(windowDomainCreate, SIGNAL(OnThirdLabelClicked()), SLOT(ManageDomainsLabelClicked()));
    connect(windowDomainCreate, SIGNAL(OnClose()), SLOT(OnCreateDomainClose()));

    QGridLayout *midlay = new QGridLayout();
    QBoxLayout *botlay= new QBoxLayout(QBoxLayout::LeftToRight);

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(5);
    midlay->setMargin(10);


    QLabel *d_name_l = new QLabel("Domain name:",windowDomainCreate);

    QLabel *d_pop3_host_l =new QLabel("POP3 host:", windowDomainCreate);
    QLabel *d_pop3_port_l =new QLabel ("POP3 port:", windowDomainCreate);

    QLabel *d_imap_host_l =new QLabel("IMAP host:", windowDomainCreate);
    QLabel *d_imap_port_l =new QLabel ("IMAP port:", windowDomainCreate);

    QLabel *d_smtp_host_l =new QLabel ("SMTP host:", windowDomainCreate);
    QLabel *d_smtp_port_l =new QLabel ("SMTP port:", windowDomainCreate);


    d_name_le=new QLineEdit(windowDomainCreate);
    d_name_le->setPlaceholderText("ex: domain.com");

    d_pop3_host_le =new QLineEdit(windowDomainCreate);
    d_pop3_host_le->setPlaceholderText("ex: pop.domain.com");
    d_pop3_port_le =new QLineEdit (windowDomainCreate);
    d_pop3_port_le->setInputMask("999");
    d_pop3_port_le->setPlaceholderText("000");
    d_smtp_host_le =new QLineEdit (windowDomainCreate);
    d_smtp_host_le->setPlaceholderText("ex: smtp.domain.com");

    d_imap_host_le =new QLineEdit(windowDomainCreate);
    d_imap_host_le->setPlaceholderText("ex: imap.domain.com");
    d_imap_port_le =new QLineEdit (windowDomainCreate);
    d_imap_port_le->setInputMask("999");
    d_imap_port_le->setPlaceholderText("000");
    d_smtp_port_le =new QLineEdit (windowDomainCreate);
    d_smtp_port_le->setInputMask("999");
    d_smtp_port_le->setPlaceholderText("000");



    midlay->addWidget(d_name_l, 0, 0);

    midlay->addWidget(d_name_le, 0, 1);
    midlay->addWidget(d_pop3_host_l,1 ,0 );
    midlay->addWidget(d_pop3_host_le,1 ,1 );
    midlay->addWidget(d_pop3_port_l,2 ,0 );
    midlay->addWidget(d_pop3_port_le,2 ,1 );

    midlay->addWidget(d_imap_host_l,3 ,0 );
    midlay->addWidget(d_imap_host_le,3 ,1 );
    midlay->addWidget(d_imap_port_l,4 ,0 );
    midlay->addWidget(d_imap_port_le,4 ,1 );

    midlay->addWidget(d_smtp_host_l,5 ,0 );
    midlay->addWidget(d_smtp_host_le,5 ,1 );
    midlay->addWidget(d_smtp_port_l,6 ,0 );
    midlay->addWidget(d_smtp_port_le,6 ,1 );



    AGButton* add_domain_CLB= new AGButton(windowDomainCreate);
    add_domain_CLB->setText("Add new domain");
    add_domain_CLB->setEnabled(true);
    add_domain_CLB->setIconOnLeave(QIcon(":/data/plus_def.png"));
    add_domain_CLB->setIconOnEnter(QIcon(":/data/plus_sel.png"));
    add_domain_CLB->setIconSize(QSize(20, 20));
    add_domain_CLB->setMaximumSize(160, 40);
    QPalette def;
    def.setColor(add_domain_CLB->backgroundRole(), QColor(238, 233, 233));
    add_domain_CLB->setDefaultPalette(def);
    add_domain_CLB->setActivePalette(def);
    botlay->addWidget(add_domain_CLB);

    windowDomainCreate->setGrayZone(windowDomainCreate->width()-2, add_domain_CLB->height()+29, add_domain_CLB->pos().x()+1, add_domain_CLB->pos().y()+240);

    windowDomainCreate->AddMidLayout(midlay);
    windowDomainCreate->AddBotLayout(botlay);

    connect(add_domain_CLB, SIGNAL(clicked()), SLOT(OnAddDomainClicked()));
}
void MainWindow::setupWindowDomainOpen (QWidget *prnt){

    windowDomainOpen = new SubWindow(prnt, "CREATE", "OPEN", "MANAGE", 300, 160);

    windowDomainOpen->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    windowDomainOpen->SetActiveSecLabel(true);

    connect(windowDomainOpen, SIGNAL(OnFirstLabelClicked()), SLOT(CreateLabelClicked()));
    connect(windowDomainOpen, SIGNAL(OnThirdLabelClicked()), SLOT(ManageDomainsLabelClicked()));
    connect(windowDomainOpen, SIGNAL(OnClose()), SLOT(OnOpenDomainFileClose()));
    /*bim and bot lay*/
    QGridLayout *midlay = new QGridLayout();
    QBoxLayout *botlay= new QBoxLayout(QBoxLayout::LeftToRight);

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    QLabel* domainLabel = new QLabel("Domain list file:", windowDomainOpen);
    domainFileName = new QLabel("none", windowDomainOpen);

    QFont fnt1;
    fnt1.setPixelSize(15);
    fnt1.setItalic(false);
    QFont fnt2;
    fnt2.setPixelSize(15);
    fnt2.setItalic(true);
    fnt2.setUnderline(true);

    domainLabel->setFont(fnt1);
    domainFileName->setFont(fnt2);
    domainFileName->setAlignment(Qt::AlignLeft);
    domainLabel->setAlignment(Qt::AlignRight);


    AGButton* openDomainCLB= new AGButton(windowDomainOpen);
    openDomainCLB->setText("Open file with domains");
    openDomainCLB->setEnabled(true);
    openDomainCLB->setIconOnLeave(QIcon(":/data/open_def.png"));
    openDomainCLB->setIconOnEnter(QIcon(":/data/open_sel.png"));
    openDomainCLB->setIconSize(QSize(20, 20));
    openDomainCLB->setMaximumSize(200, 40);

    connect(openDomainCLB, SIGNAL(clicked()), SLOT(OnOpenDomainFile()));

    midlay->addWidget(domainLabel, 0, 0);
    midlay->addWidget(domainFileName, 0, 1);

    QPalette def;
    def.setColor(openDomainCLB->backgroundRole(), QColor(238, 233, 233));
    openDomainCLB->setDefaultPalette(def);
    openDomainCLB->setActivePalette(def);

    windowDomainOpen->setGrayZone(windowDomainOpen->width()-2, openDomainCLB->height()+23, openDomainCLB->pos().x()+1, openDomainCLB->pos().y()+106);

    botlay->addWidget(openDomainCLB,0);

    windowDomainOpen->AddMidLayout(midlay);
    windowDomainOpen->AddBotLayout(botlay);

}
void MainWindow::setupWindowDomainManage (QWidget *prnt){

    windowDomainManage = new SubWindow(prnt, "CREATE", "OPEN", "MANAGE", 300, 400);
    windowDomainManage->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);

    windowDomainManage->SetActiveThirdLabel(true);

    connect(windowDomainManage, SIGNAL(OnFirstLabelClicked()), SLOT(CreateLabelClicked()));
    connect(windowDomainManage, SIGNAL(OnSecondLabelClicked()), SLOT(OpenDomainLabelClicked()));
    connect(windowDomainManage, SIGNAL(OnClose()), SLOT(OnManageDomainClose()));

    QBoxLayout *midlay = new QBoxLayout(QBoxLayout::TopToBottom);
    QVBoxLayout *botlay= new QVBoxLayout();

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    /*midlay*/
    DomainTable = new QTableWidget(windowDomainManage);

    DomainTable->setColumnCount(2);
    DomainTable->setRowCount(10);
    DomainTable->setColumnWidth(0, 190);
    DomainTable->setColumnWidth(1, 55);
    DomainTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Domain") );
    DomainTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Enabled") );
    DomainTable->setFrameStyle(0);
    DomainTable->verticalHeader()->hide();
    DomainTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    DomainTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    DomainTable->setEditTriggers(QAbstractItemView::EditKeyPressed);
    DomainTable->setSelectionMode(QAbstractItemView::SingleSelection);
    DomainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(DomainTable, SIGNAL(cellClicked(int,int)), SLOT(OnCellClicked(int,int)));

    midlay->addWidget(DomainTable, 1);
    /*end midlay*/

    /*botlay*/

    QBoxLayout * butlay= new QBoxLayout(QBoxLayout::LeftToRight);
    butlay->setSpacing(10);
    butlay->setMargin(0);

    AGButton* addNewDomain= new AGButton(windowDomainManage);
    addNewDomain->setText("Add");
    addNewDomain->setEnabled(true);
    addNewDomain->setIconOnLeave(QIcon(":/data/plus_def.png"));
    addNewDomain->setIconOnEnter(QIcon(":/data/plus_sel.png"));
    addNewDomain->setIconSize(QSize(20, 20));
    addNewDomain->setMaximumHeight(40);

    delDomain= new AGButton(windowDomainManage);
    delDomain->setText("Delete");
    delDomain->setEnabled(true);
    delDomain->setIconOnLeave(QIcon(":/data/min_def.png"));
    delDomain->setIconOnEnter(QIcon(":/data/min_sel.png"));
    delDomain->setIconSize(QSize(20, 20));
    delDomain->setMaximumHeight(40);
    delDomain->setEnabled(false);


    saveDomain= new AGButton(windowDomainManage);
    saveDomain->setText("Save");
    saveDomain->setEnabled(true);
    saveDomain->setIconOnLeave(QIcon(":/data/save_def.png"));
    saveDomain->setIconOnEnter(QIcon(":/data/save_sel.png"));
    saveDomain->setIconSize(QSize(20, 20));
    saveDomain->setMaximumHeight(40);
    saveDomain->setEnabled(false);


    QPalette def;
    def.setColor(addNewDomain->backgroundRole(), QColor(238, 233, 233));
    addNewDomain->setDefaultPalette(def);
    addNewDomain->setActivePalette(def);
    delDomain->setDefaultPalette(def);
    delDomain->setActivePalette(def);
    saveDomain->setDefaultPalette(def);
    saveDomain->setActivePalette(def);

    windowDomainManage->setGrayZone(windowDomainManage->width()-2, addNewDomain->height()+29, addNewDomain->pos().x()+1, addNewDomain->pos().y()+340);

    butlay->addWidget(addNewDomain);
    butlay->addWidget(delDomain,2);
    butlay->addWidget(saveDomain);
    botlay->addLayout(butlay);

    connect(addNewDomain, SIGNAL(clicked()), SLOT(CreateLabelClicked()));
    connect(delDomain, SIGNAL(clicked()), SLOT(OnDelDomain()));
    connect(saveDomain, SIGNAL(clicked()), SLOT(OnSaveDomain()));
    /*end botlay*/


    windowDomainManage->AddMidLayout(midlay);
    windowDomainManage->AddBotLayout(botlay);

}
void MainWindow::OnEmailCliked(int row, int col){
    lastRow=row+1;
    emit protocol->getMessageSignal(row+1);
    tabsForWork->tabBar()->setCurrentIndex(0);
}
void MainWindow::OnCellClicked(int a/*row*/, int b/*col*/){
    MainBar->setText(QString::number(a)+" "+ QString::number(b));
    int count=domainVect->count();
    selectedRow=a;//counts from zero (0)
    if (a<=--count){
        delDomain->setEnabled(true);
    }
    else{
        delDomain->setEnabled(false);
    }

}
void MainWindow::setupWindowProxyUrl (QWidget *prnt){

    windowProxyUrl = new SubWindow(prnt, "MANAGE", "URL", "OPEN");
    windowProxyUrl->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    windowProxyUrl->resize(300, 200);
    windowProxyUrl->SetActiveSecLabel(true);

    connect(windowProxyUrl, SIGNAL(OnFirstLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(windowProxyUrl, SIGNAL(OnThirdLabelClicked()), SLOT(OnOpenProxyClicked()));
    connect(windowProxyUrl, SIGNAL(OnClose()), SLOT(OnCloseUrl()));

}
void MainWindow::setupWindowProxyFile (QWidget *prnt){

    windowProxyFile = new SubWindow(prnt, "MANAGE", "URL", "OPEN", 300, 160);
    windowProxyFile->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    windowProxyFile->SetActiveThirdLabel(true);

    connect(windowProxyFile, SIGNAL(OnFirstLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(windowProxyFile, SIGNAL(OnSecondLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(windowProxyFile, SIGNAL(OnClose()), SLOT(OnCloseOpenProxy()));

    QGridLayout *midlay = new QGridLayout();
    QVBoxLayout *botlay= new QVBoxLayout();

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    QLabel* proxyLabel = new QLabel("Proxy list file:", windowProxyFile);
    QLabel* proxyFileName = new QLabel("none", windowProxyFile);

    QFont fnt1;
    fnt1.setPixelSize(15);
    fnt1.setItalic(false);
    QFont fnt2;
    fnt2.setPixelSize(15);
    fnt2.setItalic(true);
    fnt2.setUnderline(true);

    proxyLabel->setFont(fnt1);
    proxyFileName->setFont(fnt2);
    proxyFileName->setAlignment(Qt::AlignLeft);
    proxyLabel->setAlignment(Qt::AlignRight);

    AGButton* openProxyCLB= new AGButton(windowProxyFile);
    openProxyCLB->setText("Open file with proxy list");
    openProxyCLB->setEnabled(true);
    openProxyCLB->setIconOnLeave(QIcon(":/data/open_def.png"));
    openProxyCLB->setIconOnEnter(QIcon(":/data/open_sel.png"));
    openProxyCLB->setIconSize(QSize(20, 20));

    connect(openProxyCLB, SIGNAL(clicked()), SLOT(OnOpenProxyFile()));

    midlay->addWidget(proxyLabel, 0, 0);
    midlay->addWidget(proxyFileName, 0, 1);

    QPalette def;
    def.setColor(openProxyCLB->backgroundRole(), QColor(238, 233, 233));
    openProxyCLB->setDefaultPalette(def);
    openProxyCLB->setActivePalette(def);

    windowProxyFile->setGrayZone(windowProxyFile->width()-2, openProxyCLB->height()+26, openProxyCLB->pos().x()+1, openProxyCLB->pos().y()+103);

    botlay->addWidget(openProxyCLB);

    windowProxyFile->AddMidLayout(midlay);
    windowProxyFile->AddBotLayout(botlay);

}
void MainWindow::setupWindowProxyManage (QWidget *prnt){
    windowProxyManage = new SubWindow(prnt, "MANAGE", "URL", "OPEN");
    windowProxyManage->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    windowProxyManage->resize(300, 230);
    windowProxyManage->SetActiveFirstLabel(true);

    connect(windowProxyManage, SIGNAL(OnSecondLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(windowProxyManage, SIGNAL(OnThirdLabelClicked()), SLOT(OnOpenProxyClicked()));
    connect(windowProxyManage, SIGNAL(OnClose()), SLOT(OnCloseManageProxy()));

    /*midlay*/

    QFont fnt1;
    fnt1.setPixelSize(15);
    fnt1.setItalic(false);
    QFont fnt2;
    fnt2.setPixelSize(15);
    fnt2.setItalic(true);
    fnt2.setUnderline(true);

    QGridLayout* midlay = new QGridLayout;
    QFont chBoxFont;
    chBoxFont.setPixelSize(20);

    useUrlCB = new QCheckBox;
    useUrlCB->setText("Use proxy list from url");
    useUrlCB->setChecked(useURLproxy);
    useUrlCB->setFont(fnt1);

    useFileCB= new QCheckBox;
    useFileCB->setText("Use proxy list form file");
    useFileCB->setChecked(useFILEproxy);
    useFileCB->setFont(fnt1);

    AGButton* setupUrl= new AGButton(centralWidget());
    setupUrl->setIconOnEnter(QIcon(":/data/left_sel.png"));
    setupUrl->setIconOnLeave(QIcon(":/data/left_def.png"));
    setupUrl->setText("");
    setupUrl->setIconSize(QSize(20, 20));
    setupUrl->setMaximumSize(35, 35);

    AGButton* setupProxyFile= new AGButton(centralWidget());
    setupProxyFile->setIconOnEnter(QIcon(":/data/left_sel.png"));
    setupProxyFile->setIconOnLeave(QIcon(":/data/left_def.png"));
    setupProxyFile->setText("");
    setupProxyFile->setIconSize(QSize(20, 20));
    setupProxyFile->setMaximumSize(35, 35);

    midlay->addWidget(useUrlCB, 0, 0);
    midlay->addWidget(setupUrl, 0, 1, Qt::AlignLeft);
    midlay->addWidget(useFileCB,1, 0);
    midlay->addWidget(setupProxyFile, 1, 1, Qt::AlignLeft);

    midlay->setMargin(10);
    midlay->setSpacing(0);
    /*end mid lay*/
    /*botlay*/
    QGridLayout * botlay = new QGridLayout;

    QLabel* proxyLabel = new QLabel("Proxy list file:", windowProxyManage);
    QLabel* proxyFileName = new QLabel("none", windowProxyManage);

    proxyLabel->setFont(fnt1);
    proxyFileName->setFont(fnt2);
    proxyFileName->setAlignment(Qt::AlignLeft);
    proxyLabel->setAlignment(Qt::AlignRight);

    QLabel* proxyUrlLabel = new QLabel("Proxy url:", windowProxyManage);
    QLabel* proxyUrlName = new QLabel("none", windowProxyManage);

    proxyUrlLabel->setFont(fnt1);
    proxyUrlName->setFont(fnt2);
    proxyUrlName->setAlignment(Qt::AlignLeft);
    proxyUrlLabel->setAlignment(Qt::AlignRight);

    QFrame *hor_line2 = new QFrame(windowProxyManage);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);

    botlay->addWidget(hor_line2, 0, 0, 0, 2, Qt::AlignTop);
    botlay->addWidget(proxyLabel, 1, 0);
    botlay->addWidget(proxyFileName, 1, 1);
    botlay->addWidget(proxyUrlLabel, 2, 0);
    botlay->addWidget(proxyUrlName, 2, 1);

    /*end bot lay*/
    windowProxyManage->AddMidLayout(midlay);
    windowProxyManage->AddBotLayout(botlay);
    connect(setupProxyFile, SIGNAL(clicked()), SLOT(OnOpenProxyClicked()));
    connect(setupUrl, SIGNAL(clicked()), SLOT(OnUrlProxyClicked()));


}
void MainWindow::setupWindowBaseFull(QWidget *prnt){
    windowBaseFull = new SubWindow(prnt, "All", "Only good", "Search");
    windowBaseFull->move(proxyButton->pos().x(), baseButton->pos().y()+40);
    windowBaseFull->resize(300, 350);
    windowBaseFull->SetActiveFirstLabel(true);

    connect(windowBaseFull, SIGNAL(OnSecondLabelClicked()), SLOT(GoodBase()));
    connect(windowBaseFull, SIGNAL(OnThirdLabelClicked()), SLOT(SearchBase()));
    connect(windowBaseFull, SIGNAL(OnClose()), SLOT(OnFullBaseClose()));

    /*mid lay*/
    QGridLayout* midlay = new QGridLayout;
    midlay->setSpacing(10);
    midlay->setMargin(0);

    QBoxLayout * topMidlay= new QBoxLayout(QBoxLayout::LeftToRight);
    topMidlay->setMargin(0);
    topMidlay->setSpacing(10);

    useIMAPCB = new QCheckBox;
    usePOP3CB = new QCheckBox;
    useTSLSSLCB = new QCheckBox;
    useNoneCB = new QCheckBox;
    QLabel* delLabel= new QLabel("Delimiter:");
    delLE=new QLineEdit;
    QLabel* fullBaseLabel = new QLabel("Current base:");
    fullBaseFileName = new QLabel("none");

    QFont fnt1;
    fnt1.setPixelSize(15);
    fnt1.setItalic(false);

    QFont fnt2;
    fnt2.setPixelSize(15);
    fnt2.setItalic(true);
    fnt2.setUnderline(true);

    fullBaseLabel->setFont(fnt1);
    fullBaseFileName->setFont(fnt2);
    fullBaseLabel->setAlignment(Qt::AlignRight);
    fullBaseFileName->setAlignment(Qt::AlignLeft);

    useIMAPCB->setFont(fnt1);
    usePOP3CB->setFont(fnt1);
    useTSLSSLCB->setFont(fnt1);
    useNoneCB->setFont(fnt1);

    delLabel->setFont(fnt1);
    delLE->setFont(fnt1);

    useIMAPCB->setText("IMAP");
    usePOP3CB->setText("POP3");
    useTSLSSLCB->setText("SSL/TLS");
    useNoneCB->setText  ("No encryption");
    useTSLSSLCB->setMinimumWidth(120);
    useNoneCB->setMinimumWidth(120);

    usePOP3CB->setChecked(usePop3);
    useIMAPCB->setChecked(useImap);
    useTSLSSLCB->setChecked(useTSLSSL);
    useNoneCB->setChecked(useEncrNone);

    delLE->setText(delimiter);
    delLE->setMaxLength(1);
    delLE->setMaximumSize(17, 20);

    QFrame *hor_line2 = new QFrame(windowBaseFull);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);
    hor_line2->setMaximumHeight(5);

    QFrame *hor_line3 = new QFrame(windowBaseFull);
    hor_line3->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line3->setLineWidth(1);
    hor_line3->setMaximumHeight(5);

    QFrame *vLine = new QFrame(windowBaseFull);
    vLine->setFrameStyle(QFrame::VLine| QFrame::Raised);
    vLine->setLineWidth(1);
    vLine->setMaximumHeight(90);


    topMidlay->addWidget(fullBaseLabel);
    topMidlay->addWidget(fullBaseFileName);
    midlay->addLayout(topMidlay,    0, 0, 1, 3, Qt::AlignBottom );
    midlay->addWidget(hor_line2,    1, 0, 1, 3, Qt::AlignVCenter );
    midlay->addWidget(usePOP3CB,    2, 0,       Qt::AlignTop | Qt::AlignHCenter);
    midlay->addWidget(useTSLSSLCB,  2, 2,       Qt::AlignTop | Qt::AlignHCenter );
    midlay->addWidget(useIMAPCB,    3, 0,       Qt::AlignTop | Qt::AlignHCenter);
    midlay->addWidget(useNoneCB,    3, 2,       Qt::AlignTop | Qt::AlignHCenter);
    midlay->addWidget(hor_line3,    4, 0, 1, 3, Qt::AlignVCenter );
    midlay->addWidget(delLabel,     5, 0,       Qt::AlignTop  |Qt::AlignRight );
    midlay->addWidget(delLE,        5, 1,       Qt::AlignTop| Qt::AlignLeft);
    midlay->addWidget(vLine,        1, 1, 4, 1 );

    /*end mid lay*/

    /*bot lay */
    QBoxLayout* botlay= new QBoxLayout(QBoxLayout::LeftToRight);

    AGButton* openDataFileCLB= new AGButton(windowBaseFull);
    openDataFileCLB->setText("Open");
    openDataFileCLB->setEnabled(true);
    openDataFileCLB->setIconOnLeave(QIcon(":/data/open_def.png"));
    openDataFileCLB->setIconOnEnter(QIcon(":/data/open_sel.png"));
    openDataFileCLB->setIconSize(QSize(20, 20));
    openDataFileCLB->setMaximumSize(100, 40);

    checkDataFileCLB = new AGButton(windowBaseFull);
    checkDataFileCLB->setText("Check");
    checkDataFileCLB->setEnabled(true);
    checkDataFileCLB->setIconOnLeave(QIcon(":/data/check_def.png"));
    checkDataFileCLB->setIconOnEnter(QIcon(":/data/check_sel.png"));
    checkDataFileCLB->setIconSize(QSize(20, 20));
    checkDataFileCLB->setMaximumSize(100, 40);
    checkDataFileCLB->setEnabled(false);

    closeDataFileCLB = new AGButton(windowBaseFull);
    closeDataFileCLB->setText("Close");
    closeDataFileCLB->setEnabled(true);
    closeDataFileCLB->setIconOnLeave(QIcon(":/data/close_def.png"));
    closeDataFileCLB->setIconOnEnter(QIcon(":/data/close_sel.png"));
    closeDataFileCLB->setIconSize(QSize(20, 20));
    closeDataFileCLB->setMaximumSize(100, 40);
    closeDataFileCLB->setEnabled(false);


    connect(openDataFileCLB, SIGNAL(clicked()), SLOT(OnOpenDataFileCLB()));
    connect(checkDataFileCLB, SIGNAL(clicked()), SLOT(OnCheckDataFileCLB()));
    connect(closeDataFileCLB, SIGNAL(clicked()), SLOT(OnCloseDataFileCLB()));


    /* Gray Zone */

    QPalette def;
    def.setColor(openDataFileCLB->backgroundRole(), QColor(238, 233, 233));
    openDataFileCLB->setDefaultPalette(def);
    openDataFileCLB->setActivePalette(def);
    checkDataFileCLB->setDefaultPalette(def);
    checkDataFileCLB->setActivePalette(def);
    closeDataFileCLB->setDefaultPalette(def);
    closeDataFileCLB->setActivePalette(def);

    windowBaseFull->setGrayZone(windowBaseFull->width()-2, checkDataFileCLB->height()+26,
                                checkDataFileCLB->pos().x()+1, checkDataFileCLB->pos().y()+293);

    botlay->addWidget(openDataFileCLB, 0);
    botlay->addWidget(checkDataFileCLB, 0);
    botlay->addWidget(closeDataFileCLB, 0);

    /*end of bot lay*/
    windowBaseFull->AddMidLayout(midlay);
    windowBaseFull->AddBotLayout(botlay);
    delimiter=delLE->text();
}
void MainWindow::setupWindowBaseGood (QWidget *prnt){

    windowBaseGood = new SubWindow(prnt, "All", "Only good", "Search");
    windowBaseGood->move(proxyButton->pos().x(), baseButton->pos().y()+40);
    windowBaseGood->resize(300, 200);
    windowBaseGood->SetActiveSecLabel(true);

    connect(windowBaseGood, SIGNAL(OnFirstLabelClicked()), SLOT(FullBase()));
    connect(windowBaseGood, SIGNAL(OnThirdLabelClicked()), SLOT(SearchBase()));
    connect(windowBaseGood, SIGNAL(OnClose()), SLOT(OnGoodBaseClose()));

    /*midlay*/

    QBoxLayout* midlay= new QBoxLayout(QBoxLayout::RightToLeft);

}
void MainWindow::setupWindowBaseSearch (QWidget *prnt){
    windowBaseSearch = new SubWindow(prnt, "Full", "Good", "Searched");
    windowBaseSearch->move(proxyButton->pos().x(), baseButton->pos().y()+40);
    windowBaseSearch->resize(300, 200);
    windowBaseSearch->SetActiveThirdLabel(true);

    connect(windowBaseSearch, SIGNAL(OnFirstLabelClicked()), SLOT(FullBase()));
    connect(windowBaseSearch, SIGNAL(OnSecondLabelClicked()), SLOT(GoodBase()));
    connect(windowBaseSearch, SIGNAL(OnClose()), SLOT(OnSearchBaseClose()));

}
void MainWindow::OnAddDomainClicked(){
    bool fieldsComplete=true;
    if (checkLineEdit(d_name_le))
        fieldsComplete = false;
    if (checkLineEdit(d_pop3_host_le))
        fieldsComplete = false;
    if (checkLineEdit(d_pop3_port_le))
        fieldsComplete = false;
    if (checkLineEdit(d_imap_host_le))
        fieldsComplete = false;
    if (checkLineEdit(d_imap_port_le))
        fieldsComplete = false;
    if (checkLineEdit(d_smtp_host_le))
        fieldsComplete = false;
    if (checkLineEdit(d_smtp_port_le))
        fieldsComplete = false;

    if (fieldsComplete){
        Domain tmpDomain(d_name_le->text(),
                         d_pop3_host_le->text(),
                         d_pop3_port_le->text().toInt(),
                         d_imap_host_le->text(),
                         d_imap_port_le->text().toInt(),
                         d_smtp_host_le->text(),
                         d_smtp_port_le->text().toInt());
        tmpDomain.setSelected(true);
        domainVect->push_back(tmpDomain);
        ManageDomainsLabelClicked();
    }

}
void MainWindow::updateDomainTable(){
    int row=0;
    DomainTable->clearContents();
    for(QVector<Domain>::iterator it = domainVect->begin(); it!=domainVect->end(); ++it){

        QWidget* t = new QWidget;
        QBoxLayout *box = new QBoxLayout(QBoxLayout::LeftToRight);
        box->setSpacing(0);
        box->setMargin(0);

        box->addWidget(it->getChechBoxPtr(),1, Qt::AlignCenter);
        t->setLayout(box);
        connect (it->getChechBoxPtr(), SIGNAL(stateChanged(int)), SLOT(UpdateSelection()));
        DomainTable->setItem(row, 0, new QTableWidgetItem(it->getName()));
        DomainTable->setCellWidget(row++, 1, t);
    }
}
void MainWindow::UpdateSelection(){
    /*
Qt::Unchecked	0	The item is unchecked.
Qt::PartiallyChecked	1	The item is partially checked.
Items in hierarchical models may be partially checked if some, but not all, of their children are checked.
Qt::Checked	2	The item is checked.
    */

    /*Sory for crutch :) */
    int count=0;
    for(QVector<Domain>::iterator it = domainVect->begin(); it!=domainVect->end(); ++it){
        it->UpdateSelection();
    }
}
bool MainWindow::checkLineEdit(QLineEdit *lineEdit){
    if (lineEdit->text().isEmpty()){
        lineEdit->setStyleSheet("QLineEdit { border: 1px solid red}");
        return 1;
    }
    else{
        lineEdit->setStyleSheet("");
        return 0;
    }
}
void MainWindow::OnNextButtonClicked(){
    emit protocol->getMessageSignal(++lastRow);

}
void MainWindow::OnPreviousButtonClicked(){
    emit protocol->getMessageSignal(--lastRow);

}
void MainWindow::OnSearchButtonClicked(){
    if (searchEmailWidget->isHidden()){
        searchEmailWidget->show();
    }
    else{
        ViewFrame->findText("", QWebPage::HighlightAllOccurrences);
        searchEmailWidget->hide();
    }
}

void MainWindow::OnHomeButtonClicked(){
    tabsForWork->tabBar()->setCurrentIndex(1);
}
void MainWindow::OnWriteButtonClicked(){
    tabsForWork->tabBar()->setCurrentIndex(2);
}
void MainWindow::newWindow(QUrl url){
    QDesktopServices::openUrl(url);
}
void MainWindow::OnRefreshClicked(){
    emailsTable->clearContents();
    emailsTable->setRowCount(0);
    emit protocol->update();
}
void MainWindow::onDelMessage(){

    if(emailsTable->selectionModel()->selectedRows().count()==0){
        qDebug()<<"Zero selection";
        return;
    }
    while(!emailsTable->selectionModel()->selectedRows().isEmpty()){
        emit protocol->deleteMessage(emailsTable->selectionModel()->selectedRows().takeFirst().row()+1);
        emailsTable->removeRow(emailsTable->selectionModel()->selectedRows().takeFirst().row());
        qDebug()<<"Message deleted";
    }
    ViewFrame->setHtml("<html><body>Пустая страница</html></body>");

}

void MainWindow::OnAttachmentSave(int row, int col){
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save Document"),
                "C:\\Program Files\\Oracle\\VirtualBox\\",
                tr("Documents (*.*)") );
    if(!filename.isEmpty()){
        QFile file(filename);
        file.open(QFile::WriteOnly);
        file.write(fileList.at(row));
        file.close();
    }
}

void MainWindow::OnLoadNextMessages(){
    qDebug()<<"next 20 emails";
    emit protocol->get20MessageSignal();
}
void MainWindow::scanPageForWord(){
    qDebug()<<"scaning"<<*word;
    *word=searchBox->text();
    qDebug()<<ViewFrame->findText(*word,QWebPage::HighlightAllOccurrences);
}


