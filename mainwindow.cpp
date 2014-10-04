#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    wad_is_active=false;
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
    addNewDomain->setIcon(QIcon(":/data/down.PNG"));
    addNewDomain->setIconOnEnter(QIcon(":/data/down_pressed.PNG"));
    addNewDomain->setIconOnLeave(QIcon(":/data/down.PNG"));
    addNewDomain->setText("Domains:");
    addNewDomain->setIconSize(QSize(20, 20));


    connect(addNewDomain, SIGNAL(clicked()), SLOT(DomenSetup()));
}
MainWindow::~MainWindow()
{

}
void MainWindow::DomenSetup(){
    if (wad_is_active){
        Close();
        return;
    }
    wad_is_active=true;
    MainBar->setText("Domain setup");

    window_add_domain=new QFrame(this);
    window_add_domain->installEventFilter(this);

    window_add_domain->setAttribute(Qt::WA_Hover);
    QPalette PW;
    PW.setColor(window_add_domain->backgroundRole(), Qt::white);

    window_add_domain->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    window_add_domain->setLineWidth(3);
    window_add_domain->resize(300,400);
    window_add_domain->move(30, 72);
    window_add_domain->setAutoFillBackground(true);
    window_add_domain->setVisible(true);
    window_add_domain->setPalette(PW);

    ExLabel * wind_caption = new ExLabel("CREATE",window_add_domain);
    wind_caption->setAlignment(Qt::AlignCenter);

    ExLabel* openDomain = new ExLabel("OPEN",window_add_domain);
    openDomain->setAlignment(Qt::AlignCenter);

    ExLabel* manageDomains = new ExLabel("MANAGE",window_add_domain);
    manageDomains->setAlignment(Qt::AlignCenter);

    QPalette pal;
    pal.setColor(wind_caption->foregroundRole(), Qt::blue);


    QFont centr_label_font_unsel;
    centr_label_font_unsel.setPixelSize(15);
    centr_label_font_unsel.setBold(false);
    centr_label_font_unsel.setUnderline(true);

    QFont centr_label_font_sel;
    centr_label_font_sel.setPixelSize(15);
    centr_label_font_sel.setBold(true);
    centr_label_font_sel.setUnderline(true);

    wind_caption->setFont(centr_label_font_unsel);
    wind_caption->SetSelectedFont(centr_label_font_sel);
    wind_caption->SetUnSelectedFont(centr_label_font_unsel);
    wind_caption->setPalette(pal);

    openDomain->setFont(centr_label_font_unsel);
    openDomain->setPalette(pal);
    openDomain->SetSelectedFont(centr_label_font_sel);
    openDomain->SetUnSelectedFont(centr_label_font_unsel);

    manageDomains->setFont(centr_label_font_unsel);
    manageDomains->setPalette(pal);
    manageDomains->SetSelectedFont(centr_label_font_sel);
    manageDomains->SetUnSelectedFont(centr_label_font_unsel);

    QFrame *hor_line = new QFrame(window_add_domain);
    hor_line->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line->setLineWidth(1);


    QLabel *d_name_l = new QLabel("Domain name:",window_add_domain);

    QLabel *d_pop3_tsl_host_l =new QLabel("POP3 TSL host:", window_add_domain);
    QLabel *d_pop3_ssl_host_l =new QLabel ("POP3 SSL host:", window_add_domain);

    QLabel *d_imap_tsl_host_l =new QLabel ("IMAP TSL host:", window_add_domain);
    QLabel *d_imap_ssl_host_l =new QLabel ("IMAP SSL host:", window_add_domain);

    QLabel *d_pop3_tsl_port_l =new QLabel ("POP3 TSL port:", window_add_domain);
    QLabel *d_pop3_ssl_port_l =new QLabel ("POP3 SSL port:", window_add_domain);

    QLabel *d_imap_tsl_port_l =new QLabel ("IMAP TSL port:", window_add_domain);
    QLabel *d_imap_ssl_port_l =new QLabel ("IMAP SSL port:", window_add_domain);

    QLineEdit* d_name_le=new QLineEdit(window_add_domain);
    d_name_le->setPlaceholderText("ex: gmail.com");
    QLineEdit *d_pop3_tsl_host_le =new QLineEdit(window_add_domain);
    d_pop3_tsl_host_le->setPlaceholderText("ex: pop3.domainTSL.com");
    QLineEdit *d_pop3_ssl_host_le =new QLineEdit (window_add_domain);
    d_pop3_ssl_host_le->setPlaceholderText("ex: pop3.domainSSL.com");
    QLineEdit *d_imap_tsl_host_le =new QLineEdit (window_add_domain);
    d_imap_tsl_host_le->setPlaceholderText("ex: imap.domainTSL.com");
    QLineEdit *d_imap_ssl_host_le =new QLineEdit (window_add_domain);
    d_imap_ssl_host_le->setPlaceholderText("ex: imap.domainSSL.com");
    QLineEdit *d_pop3_tsl_port_le =new QLineEdit (window_add_domain);
    d_pop3_tsl_port_le->setInputMask("999");
    d_pop3_tsl_port_le->setPlaceholderText("000");
    QLineEdit *d_pop3_ssl_port_le =new QLineEdit (window_add_domain);
    d_pop3_ssl_port_le->setInputMask("999");
    d_pop3_ssl_port_le->setPlaceholderText("000");
    QLineEdit *d_imap_tsl_port_le =new QLineEdit (window_add_domain);
    d_imap_tsl_port_le->setInputMask("999");
    d_imap_tsl_port_le->setPlaceholderText("000");
    QLineEdit *d_imap_ssl_port_le =new QLineEdit (window_add_domain);
    d_imap_ssl_port_le->setInputMask("999");
    d_imap_ssl_port_le->setPlaceholderText("000");
    QGridLayout *grdlay= new QGridLayout();
    grdlay->setMargin(10);
    grdlay->setSpacing(5);

    grdlay->addWidget(d_name_l, 0, 0);
    grdlay->addWidget(d_name_le, 0, 1);
    grdlay->addWidget(d_pop3_tsl_host_l,1 ,0 );
    grdlay->addWidget(d_pop3_tsl_host_le,1 ,1 );
    grdlay->addWidget(d_pop3_ssl_host_l,2 ,0 );
    grdlay->addWidget(d_pop3_ssl_host_le,2 ,1 );
    grdlay->addWidget(d_imap_tsl_host_l,3 ,0 );
    grdlay->addWidget(d_imap_tsl_host_le,3 ,1 );
    grdlay->addWidget(d_imap_ssl_host_l,4 ,0 );
    grdlay->addWidget(d_imap_ssl_host_le,4 ,1 );
    grdlay->addWidget(d_pop3_tsl_port_l,5 ,0 );
    grdlay->addWidget(d_pop3_tsl_port_le,5 ,1 );
    grdlay->addWidget(d_pop3_ssl_port_l,6 ,0 );
    grdlay->addWidget(d_pop3_ssl_port_le,6 ,1 );
    grdlay->addWidget(d_imap_tsl_port_l,7 ,0 );
    grdlay->addWidget(d_imap_tsl_port_le,7 ,1 );
    grdlay->addWidget(d_imap_ssl_port_l,8 ,0 );
    grdlay->addWidget(d_imap_ssl_port_le,8 ,1 );

    QBoxLayout* headerlay = new QBoxLayout(QBoxLayout::LeftToRight);
    headerlay->setSpacing(10);
    headerlay->setMargin(0);
    headerlay->addWidget(wind_caption, 1);
    headerlay->addWidget(openDomain, 1);
    headerlay->addWidget(manageDomains,1);


    QVBoxLayout* toplay=new QVBoxLayout();
    toplay->setSpacing(10);
    toplay->setMargin(10);
    toplay->addLayout(headerlay);
    toplay->addWidget(hor_line);

    QVBoxLayout* botlay = new QVBoxLayout();
    botlay->setMargin(10);
    botlay->setSpacing(10);

    QFrame *hor_line2 = new QFrame(window_add_domain);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);

    QCommandLinkButton* add_domain_CLB= new QCommandLinkButton(window_add_domain);
    add_domain_CLB->setText("Add new domain");
    add_domain_CLB->setEnabled(true);
    add_domain_CLB->setIcon(QIcon(":/data/plus.png"));
    add_domain_CLB->setIconSize(QSize(20, 20));


    botlay->addWidget(hor_line2);
    botlay->addWidget(add_domain_CLB);

    QVBoxLayout*biglay = new QVBoxLayout();
    biglay->setMargin(10);
    biglay->setSpacing(10);
    biglay->addLayout(toplay);
    biglay->addLayout(grdlay);
    biglay->addLayout(botlay);



    window_add_domain->setLayout(biglay);
    connect(wind_caption, SIGNAL(clicked()),SLOT(OnCreateLabelClicked()));
    connect(openDomain, SIGNAL(clicked()), SLOT(OnOpenDomainLabelClicked()));
    connect(manageDomains, SIGNAL(clicked()), SLOT(OnManageDomainsLabelClicked()));
}
void MainWindow::On_Domain_Cursor_up(){

}
bool MainWindow::eventFilter(QObject * obj, QEvent * event)
{

    if(obj==window_add_domain){
        QEvent::Type type = event->type();
        if  (type == QEvent::HoverLeave) {
            Close();
        }
    }

    return QWidget::eventFilter(obj, event);
}
void MainWindow::Close(){
    window_add_domain->close();
    wad_is_active=false;
}
void MainWindow::OnCreateLabelClicked(){
    MainBar->setText("Create a new domain");

}
void MainWindow::OnOpenDomainLabelClicked(){
    MainBar->setText("Open file with domain list");

}
void MainWindow::OnManageDomainsLabelClicked(){
    MainBar->setText("Manage your domains");

}

