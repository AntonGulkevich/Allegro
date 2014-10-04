#ifndef ALLERGOMAINWIN_H
#define ALLERGOMAINWIN_H

#include <QMainWindow>

#include "account.h"

namespace Ui {
class AllergoMainWin;
}

class AllergoMainWin : public QMainWindow
{
    Q_OBJECT

private Q_SLOTS:
    void DomenSetup();
    void On_Domain_Cursor_up();
public:
    explicit AllergoMainWin(QWidget *parent = 0);
    ~AllergoMainWin();
private:
    Ui::AllergoMainWin *ui;
};

#endif // ALLERGOMAINWIN_H
