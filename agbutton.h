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
    void setActivePalette(const QPalette &pal);
    void setDefaultPalette(const QPalette &pal);
    void setHint(const QString &hintText);

signals:
    void showHint(QString textInfo);

public slots:


protected:

    //virtual void paintEvent(QPaintEvent *);
   // virtual void mousePressEvent(QMouseEvent* pe);
   // virtual void mouseReleaseEvent(QMouseEvent* pe);
   // virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent *event   );



private:
    QIcon onEnterIcon;
    QIcon onLeaveIcon;
    QPalette* activePal;
    QPalette* defPal;
    QString hint;

};

#endif // AGBUTTON_H
