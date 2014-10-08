#include "subwindow.h"
#include <QDebug>

SubWindow::SubWindow(QWidget *parent , const QString &firstLabel, const QString &seclabel, const QString &thrdlabel,
                      int w, int h) :
    QFrame(parent)
{
    active=true;
    QPalette PW;
    PW.setColor(backgroundRole(), Qt::white);

    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setLineWidth(3);
    resize(w,h);
    setAutoFillBackground(true);
    setVisible(true);
    setPalette(PW);

    newDomainLabel = new ExLabel(firstLabel, this);
    newDomainLabel->setAlignment(Qt::AlignCenter);

    openDomainLabel = new ExLabel(seclabel,this);
    openDomainLabel->setAlignment(Qt::AlignCenter);

    manageDomainsLabel = new ExLabel(thrdlabel,this);
    manageDomainsLabel->setAlignment(Qt::AlignCenter);

    QPalette pal;
    pal.setColor(newDomainLabel->foregroundRole(), QColor(0, 90, 255));


    QFont unsel;
    unsel.setPixelSize(13);
    unsel.setBold(false);
    unsel.setUnderline(false);

    QFont sel;
    sel.setPixelSize(13);
    sel.setBold(true);
    sel.setUnderline(true);

    QFont act;
    act.setPixelSize(14);
    act.setBold(true);
    act.setUnderline(true);

    newDomainLabel->setPalette(pal);
    newDomainLabel->SetSelectedFont(sel);
    newDomainLabel->SetUnSelectedFont(unsel);
    newDomainLabel->SetActiveFont(act);


    openDomainLabel->setPalette(pal);
    openDomainLabel->SetSelectedFont(sel);
    openDomainLabel->SetUnSelectedFont(unsel);
    openDomainLabel->SetActiveFont(act);

    manageDomainsLabel->setPalette(pal);
    manageDomainsLabel->SetSelectedFont(sel);
    manageDomainsLabel->SetUnSelectedFont(unsel);
    manageDomainsLabel->SetActiveFont(act);

    QFrame *hor_line = new QFrame(this);
    hor_line->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line->setLineWidth(1);

    connect(newDomainLabel, SIGNAL(clicked()),SLOT(CreaLabelClick()));
    connect(openDomainLabel, SIGNAL(clicked()), SLOT(OpenLabelClick()));
    connect(manageDomainsLabel, SIGNAL(clicked()), SLOT(ManageLabelClick()));

    toplay = new QBoxLayout(QBoxLayout::TopToBottom);
    midlay = new QBoxLayout(QBoxLayout::TopToBottom);
    botlay = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout * headerlay=new QBoxLayout(QBoxLayout::LeftToRight);


    headerlay->setSpacing(10);
    headerlay->setMargin(10);


    headerlay->addWidget(newDomainLabel, 0);
    headerlay->addWidget(openDomainLabel, 0);
    headerlay->addWidget(manageDomainsLabel,0);

    toplay->addLayout(headerlay, 0);

    toplay->addWidget(hor_line, 1, Qt::AlignTop);

    QBoxLayout *biglay = new QBoxLayout(QBoxLayout::TopToBottom, this);
    biglay->addLayout(toplay, 1);
    biglay->addLayout(midlay, 5);
    biglay->addLayout(botlay, 1);

    grayZone= new QFrame(this);
    QPalette botGrayPal;
    botGrayPal.setColor(grayZone->backgroundRole(), QColor(238, 233, 233));
    grayZone->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    grayZone->setPalette(botGrayPal);
    grayZone->setAutoFillBackground(true);
    grayZone->setVisible(false);

}
void SubWindow::Close(){
    active=false;
    close();
}
SubWindow::~SubWindow(){

}
void SubWindow::CreaLabelClick(){

    emit OnCreateLabelClicked();
}
void SubWindow::OpenLabelClick(){

    emit OnOpenDomainLabelClicked();
}
void SubWindow::ManageLabelClick(){

    emit OnManageDomainsLabelClicked();
}
/*
void SubWindow::leaveEvent(QEvent *event){
    QWidget::leaveEvent(event);
}
void SubWindow::enterEvent(QEvent *event){
    QWidget::enterEvent(event);
}
*/
void SubWindow::AddBotLayout(QLayout *lay){
    botlay->addLayout(lay, 1);
}
void SubWindow::AddMidLayout(QLayout *lay){
    midlay->addLayout(lay, 1);

}
bool SubWindow::IsActive(){
    return active;
}
void SubWindow::SetActiveFirstLabel(bool state){
    newDomainLabel->setActive(state);
}
void SubWindow::SetActiveSecLabel(bool state){
    openDomainLabel->setActive(state);
}
void SubWindow::SetActiveThirdLabel(bool state){
    manageDomainsLabel->setActive(state);
}
void SubWindow::focusOutEvent(QFocusEvent *event){
    close();
    qDebug()<<"focus out";
    QWidget::focusOutEvent(event);
}
void SubWindow::closeEvent(QCloseEvent *event){
    emit OnClose();
    QWidget::closeEvent(event);

}
void SubWindow::setGrayZone(int w, int h, int top, int left){
    grayZone->resize(w, h);
    grayZone->move(top, left);
    grayZone->setVisible(true);

}
