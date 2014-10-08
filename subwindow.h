#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QFrame>
#include <QPalette>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLayout>

#include "exlabel.h"

class SubWindow : public QFrame
{
    Q_OBJECT
public:
    explicit SubWindow(QWidget *parent = 0, const QString &firstLabel="", const QString &seclabel="", const QString &thrdlabel="",
                       int w=100, int h=200);
    ~SubWindow();
    void Close();
    void AddMidLayout(QLayout* lay);
    void AddBotLayout(QLayout* lay);
    bool IsActive();
    void SetActiveFirstLabel(bool state);
    void SetActiveSecLabel(bool state);
    void SetActiveThirdLabel(bool state);
    void setGrayZone(int width, int heigth, int top, int left);

signals:
    void OnCreateLabelClicked();
    void OnOpenDomainLabelClicked();
    void OnManageDomainsLabelClicked();
    void OnClose();

public slots:
    void CreaLabelClick();
    void OpenLabelClick();
    void ManageLabelClick();

private:
    bool active;
    ExLabel* newDomainLabel;
    ExLabel* openDomainLabel;
    ExLabel* manageDomainsLabel;
    QBoxLayout* toplay;
    QBoxLayout* midlay;
    QBoxLayout* botlay;

    QFrame * grayZone;
protected:
    //virtual void leaveEvent(QEvent * event);
   // virtual void enterEvent(QEvent *event);
    //void QWidget::focusOutEvent ( QFocusEvent * event )   [virtual protected]
    void focusOutEvent(QFocusEvent * event);
    void closeEvent(QCloseEvent * event);
};

#endif // SUBWINDOW_H
