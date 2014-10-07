#include "agbutton.h"

AGButton::AGButton(QWidget * parent):
    QCommandLinkButton(parent)

{
    activePal= new QPalette;
    defPal= new QPalette;
    defPal->setColor(backgroundRole(),Qt::white);
    *activePal=*defPal;
    setAutoFillBackground(true);
    setPalette(*defPal);

}
AGButton::~AGButton(){
    if (activePal)
        delete activePal;
    if (defPal)
        delete defPal;
}

/*
void AGButton::paintEvent(QPaintEvent * event) {
    // draw//

    QPushButton::paintEvent(event);
}

void AGButton::mousePressEvent(QMouseEvent *pe){

}
void AGButton::mouseMoveEvent(QMouseEvent *pe){


}
void AGButton::mouseReleaseEvent(QMouseEvent *pe){

}
*/
void AGButton::enterEvent(QEvent *event){    
    setIcon(onEnterIcon);
    setPalette(*activePal);
    emit showHint(hint);
    QWidget::enterEvent(event);
}
void AGButton::leaveEvent(QEvent *event){
    setIcon(onLeaveIcon);
    setPalette(*defPal);
    QWidget::leaveEvent(event);
}
void AGButton::setIconOnEnter(const QIcon &icon){
    onEnterIcon=icon;
}
void AGButton::setIconOnLeave(const QIcon &icon){
    setIcon(icon);
    onLeaveIcon=icon;
}
void AGButton::setActivePalette(const QPalette &pal){
    *activePal=pal;
}
void AGButton::setDefaultPalette(const QPalette &pal){
    setPalette(pal);
    *defPal=pal;
}
void AGButton::setHint(const QString &hintText){
    hint=hintText;
}



