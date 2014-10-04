#include "exlabel.h"

ExLabel::ExLabel(const QString &text, QWidget *parent) :
    QLabel(text, parent)
{
}
ExLabel::~ExLabel(){

}
void ExLabel::leaveEvent(QEvent *event){
    setFont(unselectedFont);
    QWidget::leaveEvent(event);
}
void ExLabel::enterEvent(QEvent *event){
    setFont(selectedFont);
    QWidget::enterEvent(event);
}
void ExLabel::SetSelectedFont(const QFont &font){
    selectedFont=font;
}
void ExLabel::SetUnSelectedFont(const QFont &font){
    unselectedFont=font;
}
void ExLabel::mousePressEvent(QMouseEvent *pe){

    setFont(unselectedFont);
}
void ExLabel::mouseReleaseEvent(QMouseEvent *pe){
    clicked();
    setFont(selectedFont);
}

