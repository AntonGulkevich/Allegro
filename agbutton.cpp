#include "agbutton.h"

AGButton::AGButton(QWidget * parent):
    QCommandLinkButton(parent)

{/*
    installEventFilter(this);
    setAttribute(Qt::WA_Hover);
*/
}
AGButton::~AGButton(){

}
void AGButton::mousePressEvent(QMouseEvent *pe){

}
void AGButton::mouseMoveEvent(QMouseEvent *pe){

}
void AGButton::mouseReleaseEvent(QMouseEvent *pe){
    clicked();
}
void AGButton::enterEvent(QEvent *event){
    setIcon(onEnterIcon);
    QWidget::enterEvent(event);
}
void AGButton::leaveEvent(QEvent *event){
    setIcon(onLeaveIcon);
    QWidget::leaveEvent(event);
}
void AGButton::setIconOnEnter(const QIcon &icon){
    onEnterIcon=icon;
}
void AGButton::setIconOnLeave(const QIcon &icon){
    onLeaveIcon=icon;
}



