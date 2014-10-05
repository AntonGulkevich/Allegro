#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    QFrame *mainframe = new QFrame();
    QPalette PW;
    PW.setColor(mainframe->backgroundRole(), Qt::white);
    mainframe->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    setCentralWidget(mainframe);

    setAutoFillBackground(true);
    setPalette(PW);
    resize(800,600);
    move(400, 100);
    setWindowFlags(Qt::FramelessWindowHint);

    MainBar = new QLabel;

    statusBar()->addWidget(MainBar);


    addNewDomain= new AGButton(centralWidget());
    addNewDomain->resize(110, 40);
    addNewDomain->move(30, 30);
    addNewDomain->setIconOnEnter(QIcon(":/data/down_sel.png"));
    addNewDomain->setIconOnLeave(QIcon(":/data/down_def.png"));
    addNewDomain->setText("Domains:");
    addNewDomain->setIconSize(QSize(20, 20));

    window_options=NULL;



    proxyButton= new AGButton(centralWidget());
    proxyButton->resize(110, 40);
    proxyButton->move(30, 80);
    proxyButton->setIconOnEnter(QIcon(":/data/down_sel.png"));
    proxyButton->setIconOnLeave(QIcon(":/data/down_def.png"));
    proxyButton->setText("Proxy:");
    proxyButton->setIconSize(QSize(20, 20));



    closeButton= new AGButton(centralWidget());
    closeButton->resize(35, 35);
    closeButton->setIconOnEnter(QIcon(":/data/close_sel.png"));
    closeButton->setIconOnLeave(QIcon(":/data/close_def.png"));
    closeButton->setText("");
    closeButton->setIconSize(QSize(20, 20));
    closeButton->setMaximumSize(35, 35);

    minimizeButton= new AGButton(centralWidget());
    minimizeButton->resize(35, 35);
    minimizeButton->setIconOnEnter(QIcon(":/data/min_sel.png"));
    minimizeButton->setIconOnLeave(QIcon(":/data/min_def.png"));
    minimizeButton->setText("");
    minimizeButton->setIconSize(QSize(20, 20));
    minimizeButton->setMaximumSize(35, 35);

    maximizeButton= new AGButton(centralWidget());
    maximizeButton->resize(35, 35);
    maximizeButton->setIconOnEnter(QIcon(":/data/max_sel.png"));
    maximizeButton->setIconOnLeave(QIcon(":/data/max_def.png"));
    maximizeButton->setText("");
    maximizeButton->setIconSize(QSize(20, 20));
    maximizeButton->setMaximumSize(35, 35);

    QFrame *v_line = new QFrame(window_options);
    v_line->setFrameStyle(QFrame::VLine| QFrame::Raised);
    v_line->setLineWidth(1);
    /*direction and positions*/

    QBoxLayout* cblay= new QBoxLayout(QBoxLayout::RightToLeft);
    cblay->setMargin(0);
    cblay->setSpacing(0);
    cblay->addWidget(closeButton, 0,Qt::AlignRight |Qt::AlignTop);
    cblay->addWidget(maximizeButton, 0,Qt::AlignRight |Qt::AlignTop);
    cblay->addWidget(minimizeButton, 0,Qt::AlignRight |Qt::AlignTop);
    cblay->addStretch(1);

    QBoxLayout* mainlay = new QBoxLayout(QBoxLayout::TopToBottom, mainframe);
    mainlay->setSpacing(10);
    mainlay->setMargin(0);

    QBoxLayout* buttonsLeftLay= new QBoxLayout(QBoxLayout::TopToBottom);
    buttonsLeftLay->setSpacing(10);
    buttonsLeftLay->setMargin(20);

    buttonsLeftLay->addWidget(addNewDomain, 0,Qt::AlignLeft |Qt::AlignTop);
    buttonsLeftLay->addWidget(proxyButton,  0,Qt::AlignLeft |Qt::AlignTop);
    buttonsLeftLay->addStretch(1);




    mainlay->addLayout(cblay);
    mainlay->addLayout(buttonsLeftLay, 1);

    connect(addNewDomain, SIGNAL(clicked()), SLOT(OnCreateLabelClicked()));
    connect(proxyButton, SIGNAL(clicked()), SLOT(OnManageProxyClicked()));
    connect(closeButton, SIGNAL(clicked()), SLOT(close()));
    connect(minimizeButton, SIGNAL(clicked()), SLOT(Mininize()));
    connect(maximizeButton, SIGNAL(clicked()), SLOT(Maximize()));
}
MainWindow::~MainWindow()
{

}
void MainWindow::On_Domain_Cursor_up(){

}
void MainWindow::OnCreateLabelClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }
    window_options = new SubWindow(this, "CREATE", "OPEN", "MANAGE");
    window_options->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    window_options->SetActiveFirstLabel(true);
    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnCreateLabelClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnOpenDomainLabelClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnManageDomainsLabelClicked()));

    MainBar->setText("Create a new domain");

    QGridLayout *midlay = new QGridLayout();
    QVBoxLayout *botlay= new QVBoxLayout();

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

    QFrame *hor_line2 = new QFrame(window_options);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);


    botlay->addWidget(hor_line2);
    botlay->addWidget(add_domain_CLB);

    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);

}
void MainWindow::OnOpenDomainLabelClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }

    MainBar->setText("Open file with domain list");
    window_options = new SubWindow(this, "CREATE", "OPEN", "MANAGE");
    window_options->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    window_options->resize(300, 150);
    window_options->SetActiveSecLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnCreateLabelClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnOpenDomainLabelClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnManageDomainsLabelClicked()));

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

    QFrame *hor_line2 = new QFrame(window_options);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);

    AGButton* openDomainCLB= new AGButton(window_options);
    openDomainCLB->setText("Open file with domains");
    openDomainCLB->setEnabled(true);
    openDomainCLB->setIconOnLeave(QIcon(":/data/open_def.png"));
    openDomainCLB->setIconOnEnter(QIcon(":/data/open_sel.png"));
    openDomainCLB->setIconSize(QSize(20, 20));

    connect(openDomainCLB, SIGNAL(clicked()), SLOT(OnOpenDomainFile()));

    midlay->addWidget(domainLabel, 0, 0);
    midlay->addWidget(domainFileName, 0, 1);

    botlay->addWidget(hor_line2);
    botlay->addWidget(openDomainCLB);

    window_options->AddMidLayout(midlay);
    window_options->AddBotLayout(botlay);
}
void MainWindow::OnManageDomainsLabelClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }

    MainBar->setText("Manage your domains");
    window_options = new SubWindow(this, "CREATE", "OPEN", "MANAGE");
    window_options->move(addNewDomain->pos().x(), addNewDomain->pos().y()+40);
    window_options->SetActiveThirdLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnCreateLabelClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnOpenDomainLabelClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnManageDomainsLabelClicked()));

    QBoxLayout *midlay = new QBoxLayout(QBoxLayout::TopToBottom);
    QVBoxLayout *botlay= new QVBoxLayout();

    botlay->setSpacing(5);
    botlay->setMargin(0);

    midlay->setSpacing(7);
    midlay->setMargin(10);

    /*midlay*/
    QTableWidget * DomainTable = new QTableWidget(window_options);
    DomainTable->setMaximumHeight(500);
    DomainTable->setMaximumWidth(290);

    midlay->addWidget(DomainTable, 1);
    /*end midlay*/

    /*botlay*/

    QBoxLayout * butlay= new QBoxLayout(QBoxLayout::LeftToRight);
    butlay->setSpacing(10);
    butlay->setMargin(0);

    QFrame *hor_line2 = new QFrame(window_options);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);

    AGButton* addNewDomain= new AGButton(window_options);
    addNewDomain->setText("Add");
    addNewDomain->setEnabled(true);
    addNewDomain->setIconOnLeave(QIcon(":/data/plus_def.png"));
    addNewDomain->setIconOnEnter(QIcon(":/data/plus_sel.png"));
    addNewDomain->setIconSize(QSize(20, 20));

    AGButton* delDomain= new AGButton(window_options);
    delDomain->setText("Delete");
    delDomain->setEnabled(true);
    delDomain->setIconOnLeave(QIcon(":/data/min_def.png"));
    delDomain->setIconOnEnter(QIcon(":/data/min_sel.png"));
    delDomain->setIconSize(QSize(20, 20));

    AGButton* saveDomain= new AGButton(window_options);
    saveDomain->setText("Save");
    saveDomain->setEnabled(true);
    saveDomain->setIconOnLeave(QIcon(":/data/save_def.png"));
    saveDomain->setIconOnEnter(QIcon(":/data/save_sel.png"));
    saveDomain->setIconSize(QSize(20, 20));


    butlay->addWidget(addNewDomain);
    butlay->addWidget(delDomain,2);
    butlay->addWidget(saveDomain);
    botlay->addWidget(hor_line2);
    botlay->addLayout(butlay);

    connect(addNewDomain, SIGNAL(clicked()), SLOT(OnCreateLabelClicked()));
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
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }

    MainBar->setText("Manage proxy");
    window_options = new SubWindow(this, "MANAGE", "URL", "OPEN");
    window_options->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    window_options->resize(300, 200);
    window_options->SetActiveFirstLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnOpenProxyClicked()));


}
void MainWindow::OnUrlProxyClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }

    MainBar->setText("Connect url with proxy");
    window_options = new SubWindow(this, "MANAGE", "URL", "OPEN");
    window_options->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    window_options->resize(300, 200);
    window_options->SetActiveSecLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnOpenProxyClicked()));

}
void MainWindow::OnOpenProxyClicked(){
    if(window_options){
        window_options->Close();
        window_options=NULL;
    }

    MainBar->setText("Open proxy list");
    window_options = new SubWindow(this, "MANAGE", "URL", "OPEN");
    window_options->move(proxyButton->pos().x(), proxyButton->pos().y()+40);
    window_options->resize(300, 200);
    window_options->SetActiveThirdLabel(true);

    connect(window_options, SIGNAL(OnCreateLabelClicked()), SLOT(OnManageProxyClicked()));
    connect(window_options, SIGNAL(OnOpenDomainLabelClicked()), SLOT(OnUrlProxyClicked()));
    connect(window_options, SIGNAL(OnManageDomainsLabelClicked()), SLOT(OnOpenProxyClicked()));

}
void MainWindow::Mininize(){
    showMinimized();
}
void MainWindow::Maximize(){
    showMaximized();
    connect(maximizeButton, SIGNAL(clicked()), SLOT(Normal()));
}
void MainWindow::Normal(){
    showNormal();
    connect(maximizeButton, SIGNAL(clicked()), SLOT(Maximize()));
}




