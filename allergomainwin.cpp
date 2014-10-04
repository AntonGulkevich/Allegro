#include "allergomainwin.h"
#include <QFrame>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "agbutton.h"

AllergoMainWin::AllergoMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllergoMainWin)
{
    ui->setupUi(this);


    AGButton * addNewDomain= new AGButton(0, ui->centralWidget);
    addNewDomain->resize(100, 40);
    addNewDomain->move(30, 30);
    addNewDomain->SetIcon(QIcon(":/data/down.PNG"));
    addNewDomain->SetCaption("Domains:");
    addNewDomain->button->setIconSize(QSize(20, 20));


    connect(addNewDomain, SIGNAL(OnCaptionChanged(QString)),ui->statusBar, SLOT(showMessage(QString)));
    connect(addNewDomain->button, SIGNAL(clicked()), SLOT(DomenSetup()));

}

AllergoMainWin::~AllergoMainWin()
{
    delete ui;
}
void AllergoMainWin::DomenSetup(){
    ui->statusBar->showMessage("Domain setup");

    QFrame *frame=new QFrame(ui->centralWidget);
    QPalette PW;
    PW.setColor(frame->backgroundRole(), Qt::white);

    frame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    frame->setLineWidth(3);
    frame->resize(300,400);
    frame->move(20, 52);
    frame->setAutoFillBackground(true);
    frame->setVisible(true);
    frame->setPalette(PW);

    QLabel * wind_caption = new QLabel("Creating a new domain",frame);
    wind_caption->setAlignment(Qt::AlignCenter);

    QPalette pal;
    pal.setColor(wind_caption->foregroundRole(), Qt::black);

    wind_caption->setPalette(pal);
    QFont centr_label_font;
    centr_label_font.setPixelSize(15);
    centr_label_font.setBold(true);
    wind_caption->setFont(centr_label_font);
    wind_caption->resize(200, 20);
    int x;
    x=frame->width()/2-wind_caption->width()/2;
    wind_caption->move(x, 10);

    QFrame *hor_line = new QFrame(frame);
    hor_line->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line->setLineWidth(1);


    QLabel *d_name_l = new QLabel("Domain name:",frame);

    QLabel *d_pop3_tsl_host_l =new QLabel("POP3 TSL host:", frame);
    QLabel *d_pop3_ssl_host_l =new QLabel ("POP3 SSL host:", frame);

    QLabel *d_imap_tsl_host_l =new QLabel ("IMAP TSL host:", frame);
    QLabel *d_imap_ssl_host_l =new QLabel ("IMAP SSL host:", frame);

    QLabel *d_pop3_tsl_port_l =new QLabel ("POP3 TSL port:", frame);
    QLabel *d_pop3_ssl_port_l =new QLabel ("POP3 SSL port:", frame);

    QLabel *d_imap_tsl_port_l =new QLabel ("IMAP TSL port:", frame);
    QLabel *d_imap_ssl_port_l =new QLabel ("IMAP SSL port:", frame);

    QLineEdit* d_name_le=new QLineEdit(frame);

    QLineEdit *d_pop3_tsl_host_le =new QLineEdit(frame);
    QLineEdit *d_pop3_ssl_host_le =new QLineEdit (frame);

    QLineEdit *d_imap_tsl_host_le =new QLineEdit (frame);
    QLineEdit *d_imap_ssl_host_le =new QLineEdit (frame);

    QLineEdit *d_pop3_tsl_port_le =new QLineEdit (frame);
    d_pop3_tsl_port_le->setInputMask("9999");
    QLineEdit *d_pop3_ssl_port_le =new QLineEdit (frame);
    d_pop3_ssl_port_le->setInputMask("9999");


    QLineEdit *d_imap_tsl_port_le =new QLineEdit (frame);
    d_imap_tsl_port_le->setInputMask("9999");
    QLineEdit *d_imap_ssl_port_le =new QLineEdit (frame);
    d_imap_ssl_port_le->setInputMask("9999");

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

    QVBoxLayout* toplay=new QVBoxLayout();
    toplay->setSpacing(10);
    toplay->setMargin(10);
    toplay->addWidget(wind_caption);
    toplay->addWidget(hor_line);

    QVBoxLayout* botlay = new QVBoxLayout();
    botlay->setMargin(10);
    botlay->setSpacing(10);

    QFrame *hor_line2 = new QFrame(frame);
    hor_line2->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line2->setLineWidth(1);

    QCommandLinkButton* add_domain_CLB= new QCommandLinkButton(frame);
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



    frame->setLayout(biglay);

}
void AllergoMainWin::On_Domain_Cursor_up(){

}
