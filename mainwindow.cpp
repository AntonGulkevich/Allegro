#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    QFrame *mainframe = new QFrame();
    /*Default settings*/
    window_options=NULL;
    fullDataBase=NULL;
    delimiter= ":";
    domainVect=NULL;

    /*TEST*/
    domainVect= new QVector<Domain>;
    Domain *testDomain= new Domain("gmail", "popsslhost",995, "pop3tslhost", 555, "imaptslhost", 123, "imapsslhost", 125);
    domainVect->push_back(*testDomain);

    /*TEST*/

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
    progressBar->setMaximum(100);
    progressBar->setValue(38);

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


    addNewDomain= new AGButton(centralWidget());
    addNewDomain->setIconOnEnter(QIcon(":/data/down_sel.png"));
    addNewDomain->setIconOnLeave(QIcon(":/data/down_def.png"));
    addNewDomain->setText("Domains");
    addNewDomain->setIconSize(QSize(20, 20));
    addNewDomain->setMaximumSize(110, 40);
    addNewDomain->setHint("Manage list of domains...");

    proxyButton= new AGButton(centralWidget());
    proxyButton->setIconOnEnter(QIcon(":/data/down_sel.png"));
    proxyButton->setIconOnLeave(QIcon(":/data/down_def.png"));
    proxyButton->setText("Proxy");
    proxyButton->setIconSize(QSize(20, 20));
    proxyButton->setMaximumSize(110, 40);
    proxyButton->setHint("Manage list of proxy...");

    baseButton= new AGButton(centralWidget());
    baseButton->resize(110, 40);
    baseButton->setIconOnEnter(QIcon(":/data/down_sel.png"));
    baseButton->setIconOnLeave(QIcon(":/data/down_def.png"));
    baseButton->setText("Data Base");
    baseButton->setIconSize(QSize(20, 20));
    baseButton->setMaximumSize(110, 40);
    baseButton->setHint("Manage bases: open, close, save and etc...");

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

    /*
    domainsAccount= new QTableWidget;
    domainsAccount->setColumnCount(2);
    domainsAccount->setRowCount(0);
    domainsAccount->setColumnWidth(0, 112);
    domainsAccount->setColumnWidth(1, 60);
    domainsAccount->setHorizontalHeaderItem(0,new QTableWidgetItem("Domain") );
    domainsAccount->setHorizontalHeaderItem(1,new QTableWidgetItem("Count") );
    domainsAccount->setFrameStyle(0);
    domainsAccount->setMaximumSize(190, 200);
    domainsAccount->verticalHeader()->hide();
    domainsAccount->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    domainsAccount->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    domainsAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
    domainsAccount->setSelectionMode(QAbstractItemView::NoSelection);
    domainsAccount->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    domainsAccount->setVisible(true);
    */



    QFrame *v_line = new QFrame(window_options);
    v_line->setFrameStyle(QFrame::VLine| QFrame::Raised);
    v_line->setLineWidth(1);

    /*direction and positions*/

    QBoxLayout* mainlay = new QBoxLayout(QBoxLayout::TopToBottom, mainframe);
    QBoxLayout* cblay= new QBoxLayout(QBoxLayout::RightToLeft);
    QBoxLayout* buttonsLeftLay= new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* smainlay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* tablelay = new QBoxLayout(QBoxLayout::LeftToRight);

    QSplitter *tablespl= new QSplitter (Qt::Horizontal);
    tablespl->setHandleWidth(3);
    tablespl->setStyleSheet("QSplitter::handle{background:gray;}");
    tablespl->setContentsMargins(10, 10, 10, 10);

    QWidget *container= new QWidget;
    QVBoxLayout *container_layout = new QVBoxLayout;

    test1= new QTextEdit;
    QTextEdit* test2= new QTextEdit;


    tablespl->addWidget(test1);
    tablespl->addWidget(test2);

    container_layout->addWidget(tablespl);
    container->setLayout(container_layout);

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
    buttonsLeftLay->addStretch(4);

    tablelay->addWidget(v_line);
    tablelay->addWidget(container);

    smainlay->addLayout(buttonsLeftLay, 0);
    smainlay->addLayout(tablelay, 1);

    mainlay->addLayout(cblay);
    mainlay->addLayout(smainlay);

    connect(closeButton, SIGNAL(clicked()), SLOT(close()));
    connect(minimizeButton, SIGNAL(clicked()), SLOT(Mininize()));
    connect(maximizeButton, SIGNAL(clicked()), SLOT(Maximize()));

    connect(addNewDomain, SIGNAL(clicked()), SLOT(OnDomainButtonClicked()));
    connect(proxyButton, SIGNAL(clicked()), SLOT(OnProxyButtonClicked()));
    connect(baseButton, SIGNAL(clicked()), SLOT(OnBaseButtonClicked()));

    connect(addNewDomain, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(proxyButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(baseButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(closeButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(minimizeButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
    connect(maximizeButton, SIGNAL(showHint(QString)), MainBar, SLOT(setText(QString)));
}
MainWindow::~MainWindow()
{

}
void MainWindow::On_Domain_Cursor_up(){

}
void MainWindow::CreateLabelClicked(){
    closeWindowIfOpened();

    window_options = new SubWindow(this, "CREATE", "OPEN", "MANAGE", 300, 400);
    window_options->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    window_options->SetActiveFirstLabel(true);

    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OpenDomainLabelClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(ManageDomainsLabelClicked()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnCreateDomainClose()));

    MainBar->setText("Create a new domain");

    QGridLayout *midlay = new QGridLayout();
    QBoxLayout *botlay= new QBoxLayout(QBoxLayout::LeftToRight);

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);


    QLabel *d_name_l = new QLabel("Domain name:",window_options);

    QLabel *d_pop3_tsl_host_l =new QLabel("POP3 TSL host:", window_options);
    QLabel *d_pop3_ssl_host_l =new QLabel ("POP3 SSL host:", window_options);

    QLabel *d_imap_tsl_host_l =new QLabel ("IMAP TSL host:", window_options);
    QLabel *d_imap_ssl_host_l =new QLabel ("IMAP SSL host:", window_options);

    QLabel *d_pop3_tsl_port_l =new QLabel ("POP3 TSL port:", window_options);
    QLabel *d_pop3_ssl_port_l =new QLabel ("POP3 SSL port:", window_options);

    QLabel *d_imap_tsl_port_l =new QLabel ("IMAP TSL port:", window_options);
    QLabel *d_imap_ssl_port_l =new QLabel ("IMAP SSL port:", window_options);

    QLineEdit* d_name_le=new QLineEdit(window_options);
    d_name_le->setPlaceholderText("ex: gmail.com");
    QLineEdit *d_pop3_tsl_host_le =new QLineEdit(window_options);
    d_pop3_tsl_host_le->setPlaceholderText("ex: pop3.domainTSL.com");
    QLineEdit *d_pop3_ssl_host_le =new QLineEdit (window_options);
    d_pop3_ssl_host_le->setPlaceholderText("ex: pop3.domainSSL.com");
    QLineEdit *d_imap_tsl_host_le =new QLineEdit (window_options);
    d_imap_tsl_host_le->setPlaceholderText("ex: imap.domainTSL.com");
    QLineEdit *d_imap_ssl_host_le =new QLineEdit (window_options);
    d_imap_ssl_host_le->setPlaceholderText("ex: imap.domainSSL.com");
    QLineEdit *d_pop3_tsl_port_le =new QLineEdit (window_options);
    d_pop3_tsl_port_le->setInputMask("999");
    d_pop3_tsl_port_le->setPlaceholderText("000");
    QLineEdit *d_pop3_ssl_port_le =new QLineEdit (window_options);
    d_pop3_ssl_port_le->setInputMask("999");
    d_pop3_ssl_port_le->setPlaceholderText("000");
    QLineEdit *d_imap_tsl_port_le =new QLineEdit (window_options);
    d_imap_tsl_port_le->setInputMask("999");
    d_imap_tsl_port_le->setPlaceholderText("000");
    QLineEdit *d_imap_ssl_port_le =new QLineEdit (window_options);
    d_imap_ssl_port_le->setInputMask("999");
    d_imap_ssl_port_le->setPlaceholderText("000");


    midlay->addWidget(d_name_l, 0, 0);
    midlay->addWidget(d_name_le, 0, 1);
    midlay->addWidget(d_pop3_tsl_host_l,1 ,0 );
    midlay->addWidget(d_pop3_tsl_host_le,1 ,1 );
    midlay->addWidget(d_pop3_ssl_host_l,2 ,0 );
    midlay->addWidget(d_pop3_ssl_host_le,2 ,1 );
    midlay->addWidget(d_imap_tsl_host_l,3 ,0 );
    midlay->addWidget(d_imap_tsl_host_le,3 ,1 );
    midlay->addWidget(d_imap_ssl_host_l,4 ,0 );
    midlay->addWidget(d_imap_ssl_host_le,4 ,1 );
    midlay->addWidget(d_pop3_tsl_port_l,5 ,0 );
    midlay->addWidget(d_pop3_tsl_port_le,5 ,1 );
    midlay->addWidget(d_pop3_ssl_port_l,6 ,0 );
    midlay->addWidget(d_pop3_ssl_port_le,6 ,1 );
    midlay->addWidget(d_imap_tsl_port_l,7 ,0 );
    midlay->addWidget(d_imap_tsl_port_le,7 ,1 );
    midlay->addWidget(d_imap_ssl_port_l,8 ,0 );
    midlay->addWidget(d_imap_ssl_port_le,8 ,1 );


    AGButton* add_domain_CLB= new AGButton(window_options);
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
    botlay->addStretch(1);
    botlay->addWidget(add_domain_CLB);
    botlay->addStretch(1);

    window_options->setGrayZone(window_options->width()-2, add_domain_CLB->height()+29, add_domain_CLB->pos().x()+1, add_domain_CLB->pos().y()+340);

    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);

}
void MainWindow::OpenDomainLabelClicked(){
    closeWindowIfOpened();

    window_options = new SubWindow(this, "CREATE", "OPEN", "MANAGE", 300, 160);
    MainBar->setText("Open file with domain list");

    window_options->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    window_options->SetActiveSecLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(CreateLabelClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(ManageDomainsLabelClicked()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnOpenDomainFileClose()));
    /*bim and bot lay*/
    QGridLayout *midlay = new QGridLayout();
    QVBoxLayout *botlay= new QVBoxLayout();

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    QLabel* domainLabel = new QLabel("Domain list file:", window_options);
    QLabel* domainFileName = new QLabel("none", window_options);

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


    AGButton* openDomainCLB= new AGButton(window_options);
    openDomainCLB->setText("Open file with domains");
    openDomainCLB->setEnabled(true);
    openDomainCLB->setIconOnLeave(QIcon(":/data/open_def.png"));
    openDomainCLB->setIconOnEnter(QIcon(":/data/open_sel.png"));
    openDomainCLB->setIconSize(QSize(20, 20));

    connect(openDomainCLB, SIGNAL(clicked()), SLOT(OnOpenDomainFile()));

    midlay->addWidget(domainLabel, 0, 0);
    midlay->addWidget(domainFileName, 0, 1);

    QPalette def;
    def.setColor(openDomainCLB->backgroundRole(), QColor(238, 233, 233));
    openDomainCLB->setDefaultPalette(def);
    openDomainCLB->setActivePalette(def);

    window_options->setGrayZone(window_options->width()-2, openDomainCLB->height()+23, openDomainCLB->pos().x()+1, openDomainCLB->pos().y()+106);

    botlay->addWidget(openDomainCLB);

    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);
}
void MainWindow::ManageDomainsLabelClicked(){
    closeWindowIfOpened();

    MainBar->setText("Manage your domains");
    window_options = new SubWindow(this, "CREATE", "OPEN", "MANAGE", 300, 400);
    window_options->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    window_options->SetActiveThirdLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(CreateLabelClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OpenDomainLabelClicked()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnManageDomainClose()));

    QBoxLayout *midlay = new QBoxLayout(QBoxLayout::TopToBottom);
    QVBoxLayout *botlay= new QVBoxLayout();

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    /*midlay*/
    QTableWidget * DomainTable = new QTableWidget(window_options);

    DomainTable->setColumnCount(2);
    DomainTable->setRowCount(2);
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

    QWidget* t = new QWidget;
    QBoxLayout *box = new QBoxLayout(QBoxLayout::LeftToRight);
    box->setSpacing(0);
    box->setMargin(0);
    QCheckBox * Cbox= new QCheckBox(t);
    Cbox->setText("");
    Cbox->setChecked(false);
    box->addWidget(Cbox,1, Qt::AlignCenter);
    t->setLayout(box);
    DomainTable->setCellWidget(0, 1, t);
    DomainTable->setItem(0, 0, new QTableWidgetItem("gmail.com"));

    midlay->addWidget(DomainTable, 1);
    /*end midlay*/

    /*botlay*/

    QBoxLayout * butlay= new QBoxLayout(QBoxLayout::LeftToRight);
    butlay->setSpacing(10);
    butlay->setMargin(0);

    AGButton* addNewDomain= new AGButton(window_options);
    addNewDomain->setText("Add");
    addNewDomain->setEnabled(true);
    addNewDomain->setIconOnLeave(QIcon(":/data/plus_def.png"));
    addNewDomain->setIconOnEnter(QIcon(":/data/plus_sel.png"));
    addNewDomain->setIconSize(QSize(20, 20));
    addNewDomain->setMaximumHeight(40);

    AGButton* delDomain= new AGButton(window_options);
    delDomain->setText("Delete");
    delDomain->setEnabled(true);
    delDomain->setIconOnLeave(QIcon(":/data/min_def.png"));
    delDomain->setIconOnEnter(QIcon(":/data/min_sel.png"));
    delDomain->setIconSize(QSize(20, 20));
    delDomain->setMaximumHeight(40);
    delDomain->setEnabled(false);


    AGButton* saveDomain= new AGButton(window_options);
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

    window_options->setGrayZone(window_options->width()-2, addNewDomain->height()+29, addNewDomain->pos().x()+1, addNewDomain->pos().y()+340);

    butlay->addWidget(addNewDomain);
    butlay->addWidget(delDomain,2);
    butlay->addWidget(saveDomain);
    botlay->addLayout(butlay);

    connect(addNewDomain, SIGNAL(clicked()), SLOT(CreateLabelClicked()));
    connect(delDomain, SIGNAL(clicked()), SLOT(OnDelDomain()));
    connect(saveDomain, SIGNAL(clicked()), SLOT(OnSaveDomain()));
    /*end botlay*/


    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);
}
void MainWindow::OnOpenDomainFile(){
    MainBar->setText("Choose file with domains list");
}
void MainWindow::OnDelDomain(){
    MainBar->setText("Domain deleted");
}
void MainWindow::OnSaveDomain(){
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
void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if(window_options){
        int leftX, leftY, botX, botY;
        leftX=window_options->pos().x();
        leftY=window_options->pos().y();
        botX=leftX+window_options->width();
        botY=leftY+window_options->height();
        if(mpos.x()>botX||mpos.x()<leftX||mpos.y()>botY||mpos.y()<leftY){
            window_options->Close();
            window_options=NULL;
        }
    }
    mpos = QPoint(-1, -1);
}
void MainWindow::OnManageProxyClicked(){
    closeWindowIfOpened();

    MainBar->setText("Manage proxy");
    window_options = new SubWindow(this, "MANAGE", "URL", "OPEN");
    window_options->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    window_options->resize(300, 230);
    window_options->SetActiveFirstLabel(true);

    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnOpenProxyClicked()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnCloseManageProxy()));

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

    QCheckBox* useUrlCB = new QCheckBox;
    useUrlCB->setText("Use proxy list from url");
    useUrlCB->setChecked(false);
    useUrlCB->setFont(fnt1);

    QCheckBox* useFileCB= new QCheckBox;
    useFileCB->setText("Use proxy list form file");
    useFileCB->setChecked(false);
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

    QLabel* proxyLabel = new QLabel("Proxy list file:", window_options);
    QLabel* proxyFileName = new QLabel("none", window_options);

    proxyLabel->setFont(fnt1);
    proxyFileName->setFont(fnt2);
    proxyFileName->setAlignment(Qt::AlignLeft);
    proxyLabel->setAlignment(Qt::AlignRight);

    QLabel* proxyUrlLabel = new QLabel("Proxy url:", window_options);
    QLabel* proxyUrlName = new QLabel("none", window_options);

    proxyUrlLabel->setFont(fnt1);
    proxyUrlName->setFont(fnt2);
    proxyUrlName->setAlignment(Qt::AlignLeft);
    proxyUrlLabel->setAlignment(Qt::AlignRight);

    QFrame *hor_line2 = new QFrame(window_options);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);

    botlay->addWidget(hor_line2, 0, 0, 0, 2, Qt::AlignTop);
    botlay->addWidget(proxyLabel, 1, 0);
    botlay->addWidget(proxyFileName, 1, 1);
    botlay->addWidget(proxyUrlLabel, 2, 0);
    botlay->addWidget(proxyUrlName, 2, 1);

    /*end bot lay*/
    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);
    connect(setupProxyFile, SIGNAL(clicked()), SLOT(OnOpenProxyClicked()));
    connect(setupUrl, SIGNAL(clicked()), SLOT(OnUrlProxyClicked()));

}
void MainWindow::OnUrlProxyClicked(){
    closeWindowIfOpened();

    MainBar->setText("Connect url with proxy");
    window_options = new SubWindow(this, "MANAGE", "URL", "OPEN");
    window_options->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    window_options->resize(300, 200);
    window_options->SetActiveSecLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnOpenProxyClicked()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnCloseUrl()));

}
void MainWindow::OnOpenProxyClicked(){
    closeWindowIfOpened();

    MainBar->setText("Open proxy list");
    window_options = new SubWindow(this, "MANAGE", "URL", "OPEN", 300, 160);
    window_options->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    window_options->SetActiveThirdLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnCloseOpenProxy()));

    QGridLayout *midlay = new QGridLayout();
    QVBoxLayout *botlay= new QVBoxLayout();

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    QLabel* proxyLabel = new QLabel("Proxy list file:", window_options);
    QLabel* proxyFileName = new QLabel("none", window_options);

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

    AGButton* openProxyCLB= new AGButton(window_options);
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

    window_options->setGrayZone(window_options->width()-2, openProxyCLB->height()+26, openProxyCLB->pos().x()+1, openProxyCLB->pos().y()+103);

    botlay->addWidget(openProxyCLB);

    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);
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
    window_options = new SubWindow(this, "Full", "Good", "Searched");
    window_options->move(proxyButton->pos().x(), baseButton->pos().y()+40);
    window_options->resize(300, 350);
    window_options->SetActiveFirstLabel(true);

    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(GoodBase()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(SearchBase()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnFullBaseClose()));

    /*mid lay*/
    QGridLayout* midlay = new QGridLayout;
    midlay->setSpacing(10);
    midlay->setMargin(0);

    QBoxLayout * topMidlay= new QBoxLayout(QBoxLayout::LeftToRight);
    topMidlay->setMargin(0);
    topMidlay->setSpacing(10);

    QCheckBox* usePOP3TSL = new QCheckBox;
    QCheckBox* usePOP3SSL = new QCheckBox;
    QCheckBox* useIMAPTSL = new QCheckBox;
    QCheckBox* useIMAPSSL = new QCheckBox;
    QLabel* delLabel= new QLabel("Delimiter:");
    delLE=new QLineEdit;
    QLabel* fullBaseLabel = new QLabel("Current base:");
    QLabel* fullBaseFileName = new QLabel("none");

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

    if (fullDataBase!=NULL){
        fullBaseFileName->setText(fullDataBase->baseName());
    }

    usePOP3TSL->setFont(fnt1);
    usePOP3SSL->setFont(fnt1);
    useIMAPTSL->setFont(fnt1);
    useIMAPSSL->setFont(fnt1);
    delLabel->setFont(fnt1);
    delLE->setFont(fnt1);


    usePOP3TSL->setText("POP3 TSL");
    usePOP3SSL->setText("POP3 SSL");
    useIMAPTSL->setText("IMAP TSL");
    useIMAPSSL->setText("IMAP SSL");
    delLE->setText(delimiter);
    delLE->setMaxLength(1);
    delLE->setMaximumSize(17, 20);



    QFrame *hor_line2 = new QFrame(window_options);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);
    hor_line2->setMaximumHeight(5);

    QFrame *hor_line3 = new QFrame(window_options);
    hor_line3->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line3->setLineWidth(1);
    hor_line3->setMaximumHeight(5);


    topMidlay->addWidget(fullBaseLabel);
    topMidlay->addWidget(fullBaseFileName);

    midlay->addLayout(topMidlay,0, 0, 1, 2,Qt::AlignBottom );
    midlay->addWidget(hor_line2, 1, 0, 1, 2,Qt::AlignVCenter );
    midlay->addWidget(usePOP3TSL, 2, 0, Qt::AlignTop | Qt::AlignRight);
    midlay->addWidget(usePOP3SSL, 2, 1, Qt::AlignTop | Qt::AlignLeft );
    midlay->addWidget(useIMAPTSL, 3, 0, Qt::AlignTop | Qt::AlignRight);
    midlay->addWidget(useIMAPSSL, 3, 1, Qt::AlignTop | Qt::AlignLeft);
    midlay->addWidget(hor_line3, 4, 0, 1, 2,Qt::AlignVCenter );
    midlay->addWidget(delLabel, 5, 0, Qt::AlignTop  |Qt::AlignRight );
    midlay->addWidget(delLE, 5, 1, Qt::AlignTop| Qt::AlignLeft);


    /*end mid lay*/

    /*bot lay */
    QBoxLayout* botlay= new QBoxLayout(QBoxLayout::LeftToRight);

    AGButton* openDataFileCLB= new AGButton(window_options);
    openDataFileCLB->setText("Open");
    openDataFileCLB->setEnabled(true);
    openDataFileCLB->setIconOnLeave(QIcon(":/data/open_def.png"));
    openDataFileCLB->setIconOnEnter(QIcon(":/data/open_sel.png"));
    openDataFileCLB->setIconSize(QSize(20, 20));
    openDataFileCLB->setMaximumSize(100, 40);

    AGButton* checkDataFileCLB= new AGButton(window_options);
    checkDataFileCLB->setText("Check");
    checkDataFileCLB->setEnabled(true);
    checkDataFileCLB->setIconOnLeave(QIcon(":/data/check_def.png"));
    checkDataFileCLB->setIconOnEnter(QIcon(":/data/check_sel.png"));
    checkDataFileCLB->setIconSize(QSize(20, 20));
    checkDataFileCLB->setMaximumSize(100, 40);
    checkDataFileCLB->setEnabled(false);

    AGButton* closeDataFileCLB= new AGButton(window_options);
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

    window_options->setGrayZone(window_options->width()-2, checkDataFileCLB->height()+26,
                                checkDataFileCLB->pos().x()+1, checkDataFileCLB->pos().y()+293);

    botlay->addWidget(openDataFileCLB, 0);
    botlay->addWidget(checkDataFileCLB, 0);
    botlay->addWidget(closeDataFileCLB, 0);

    /*end bot lay*/
    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);
    delimiter=delLE->text();

}
void MainWindow::GoodBase(){
    closeWindowIfOpened();

    MainBar->setText("Manage base with doog account");
    window_options = new SubWindow(this, "Full", "Good", "Searched");
    window_options->move(proxyButton->pos().x(), baseButton->pos().y()+40);
    window_options->resize(300, 200);
    window_options->SetActiveSecLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(FullBase()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(SearchBase()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnGoodBaseClose()));

    /*midlay*/

    QBoxLayout* midlay= new QBoxLayout(QBoxLayout::RightToLeft);



}
void MainWindow::SearchBase(){
    closeWindowIfOpened();

    MainBar->setText("Manage current base");
    window_options = new SubWindow(this, "Full", "Good", "Searched");
    window_options->move(proxyButton->pos().x(), baseButton->pos().y()+40);
    window_options->resize(300, 200);
    window_options->SetActiveThirdLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(FullBase()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(GoodBase()));
    connect(window_options, SIGNAL(OnClose()), SLOT(OnSearchBaseClose()));

}
void MainWindow::OnCloseUrl(){
    qDebug()<<"OnCloseUrlSetup";
}
void MainWindow::OnCloseManageProxy(){
    qDebug()<<"OnCloseManageProxy";
}
void MainWindow::OnCloseOpenProxy(){
    qDebug()<<"OnCloseOpenProxy";
}
void MainWindow::OnFullBaseClose(){
    qDebug()<<"OnFullBaseClose";
    delimiter=delLE->text();
    delete delLE;
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
    if(window_options){
        window_options->Close();
        window_options=NULL;
        return;
    }
    CreateLabelClicked();

}
void MainWindow::OnBaseButtonClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
        return;
    }
    FullBase();

}
void MainWindow::OnProxyButtonClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
        return;
    }
    OnManageProxyClicked();

}
void MainWindow::closeWindowIfOpened(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }
}
void MainWindow::OnOpenProxyFile(){

}
QString MainWindow::OnOpenDataFileCLB(){
    closeWindowIfOpened();
    /*Open data base*/
    if (fullDataBase!=NULL){
        delete fullDataBase;
        fullDataBase=NULL;
    }

    QString DefaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);;
    QString *fileName = new QString(QFileDialog::getOpenFileName(this, "Open Data Base", DefaultPath+"\\base","*.txt" ));

    fullDataBase= new Presto(this, fileName);

    fullDataBase->setProgressBar(progressBar);
    fullDataBase->setDelimiter(delimiter);
    fullDataBase->setDomains(domainVect);

    if(!fullDataBase->openBase()){
        delete fullDataBase;
        fullDataBase=NULL;
    }
    MainBar->setText("Base opened, warnings: " +QString::number(fullDataBase->getWarnings()));
}
void MainWindow::OnCloseDataFileCLB(){



}
void MainWindow::OnCheckDataFileCLB(){

}



