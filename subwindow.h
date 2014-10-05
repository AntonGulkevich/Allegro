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
    explicit SubWindow(QWidget *parent = 0, const QString &firstLabel="", const QString &seclabel="", const QString &thrdlabel="");
    ~SubWindow();
    void Close();
    void AddMidLayout(QLayout* lay);
    void AddBotLayout(QLayout* lay);
    bool IsActive();
    void SetActiveFirstLabel(bool state);
    void SetActiveSecLabel(bool state);
    void SetActiveThirdLabel(bool state);

signals:
    void OnCreateLabelClicked();
    void OnOpenDomainLabelClicked();
    void OnManageDomainsLabelClicked();

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
protected:
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent *event);

};

#endif // SUBWINDOW_H
