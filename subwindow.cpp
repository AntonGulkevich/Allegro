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
    setPalette(PW);

    first_label = new ExLabel(firstLabel, this);
    first_label->setAlignment(Qt::AlignCenter);

    second_label = new ExLabel(seclabel,this);
    second_label->setAlignment(Qt::AlignCenter);

    third_label = new ExLabel(thrdlabel,this);
    third_label->setAlignment(Qt::AlignCenter);

    QPalette pal;
    pal.setColor(first_label->foregroundRole(), QColor(0, 90, 255));


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

    first_label->setPalette(pal);
    first_label->SetSelectedFont(sel);
    first_label->SetUnSelectedFont(unsel);
    first_label->SetActiveFont(act);


    second_label->setPalette(pal);
    second_label->SetSelectedFont(sel);
    second_label->SetUnSelectedFont(unsel);
    second_label->SetActiveFont(act);

    third_label->setPalette(pal);
    third_label->SetSelectedFont(sel);
    third_label->SetUnSelectedFont(unsel);
    third_label->SetActiveFont(act);

    QFrame *hor_line = new QFrame(this);
    hor_line->setFrameStyle(QFrame::HLine| QFrame::Raised);
    hor_line->setLineWidth(1);
    hor_line->setMaximumHeight(5);

    connect(first_label, SIGNAL(clicked()),SLOT(firstLabelClick()));
    connect(second_label, SIGNAL(clicked()), SLOT(secondLabelClick()));
    connect(third_label, SIGNAL(clicked()), SLOT(thirdLabelClick()));

    toplay = new QBoxLayout(QBoxLayout::TopToBottom);
    midlay = new QBoxLayout(QBoxLayout::TopToBottom);
    botlay = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout * headerlay=new QBoxLayout(QBoxLayout::LeftToRight);


    headerlay->setSpacing(10);
    headerlay->setMargin(10);


    headerlay->addWidget(first_label, 1);
    headerlay->addWidget(second_label, 1);
    headerlay->addWidget(third_label,1);

    toplay->addLayout(headerlay, 0);
    toplay->addWidget(hor_line, 0, Qt::AlignTop);

    QBoxLayout *biglay = new QBoxLayout(QBoxLayout::TopToBottom, this);
    biglay->addLayout(toplay, 0);
    biglay->addLayout(midlay, 0);
    biglay->addLayout(botlay, 0);

    grayZone= new QFrame(this);
    QPalette botGrayPal;
    botGrayPal.setColor(grayZone->backgroundRole(), QColor(238, 233, 233));
    grayZone->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    grayZone->setPalette(botGrayPal);
    grayZone->setAutoFillBackground(true);
    grayZone->setVisible(false);

    hide();

}
void SubWindow::Close(){
    active=false;
    close();
}
SubWindow::~SubWindow(){
    delete first_label;
    delete second_label;
    delete third_label;
    delete toplay;
    delete midlay;
    delete botlay;
    delete grayZone;
}
void SubWindow::firstLabelClick(){

    emit OnFirstLabelClicked();
}
void SubWindow::secondLabelClick(){

    emit OnSecondLabelClicked();
}
void SubWindow::thirdLabelClick(){

    emit OnThirdLabelClicked();
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
    midlay->addLayout(lay, 5);

}
bool SubWindow::IsActive(){
    return active;
}
void SubWindow::SetActiveFirstLabel(bool state){
    first_label->setActive(state);
}
void SubWindow::SetActiveSecLabel(bool state){
    second_label->setActive(state);
}
void SubWindow::SetActiveThirdLabel(bool state){
    third_label->setActive(state);
}
void SubWindow::focusOutEvent(QFocusEvent *event){
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

}/*
void SubWindow::mousePressEvent(QMouseEvent *event){

}*/
