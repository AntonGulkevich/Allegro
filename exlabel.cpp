#include "exlabel.h"

ExLabel::ExLabel(const QString &text, QWidget *parent) :
    QLabel(text, parent)
{
    active=false;
}
ExLabel::~ExLabel(){

}
void ExLabel::leaveEvent(QEvent *event){
    if (active){
        setFont(activeFont);
    }
    else{
        setFont(unselectedFont);
    }
    QWidget::leaveEvent(event);
}
void ExLabel::enterEvent(QEvent *event){
    if (active){
        setFont(activeFont);
    }
    else{
        setFont(selectedFont);
    }
    QWidget::enterEvent(event);
}
void ExLabel::SetSelectedFont(const QFont &font){
    selectedFont=font;
}
void ExLabel::SetActiveFont(const QFont &font){
    activeFont=font;
}
void ExLabel::SetUnSelectedFont(const QFont &font){
    unselectedFont=font;
}
void ExLabel::mousePressEvent(QMouseEvent *pe){
    if (active){
        setFont(activeFont);
    }
    else{
        setFont(selectedFont);
    }
}
void ExLabel::mouseReleaseEvent(QMouseEvent *pe){
    if (active){
        setFont(activeFont);
    }
    else{
        setFont(selectedFont);
    }
    clicked();
}
void ExLabel::setActive(bool status){
    setFont(activeFont);
    active=status;
}
bool ExLabel::isActive(){
    return active;
}

