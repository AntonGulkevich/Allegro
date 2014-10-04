#ifndef AGBUTTON_H
#define AGBUTTON_H

#include <QCommandLinkButton>
#include <QString>
#include <QtGui>
#include <QObject>
#include <QIcon>

class AGButton : public QCommandLinkButton
{
    Q_OBJECT
public:
    explicit AGButton(QWidget * parent= 0);
    void setIconOnEnter(const QIcon &icon);
    void setIconOnLeave(const QIcon &icon);
    ~AGButton();

signals:


public slots:


protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent *event   );

private:
    QIcon onEnterIcon;
    QIcon onLeaveIcon;

};

#endif // AGBUTTON_H
