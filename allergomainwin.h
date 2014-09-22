#ifndef ALLERGOMAINWIN_H
#define ALLERGOMAINWIN_H

#include <QMainWindow>

namespace Ui {
class AllergoMainWin;
}

class AllergoMainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AllergoMainWin(QWidget *parent = 0);
    ~AllergoMainWin();

private:
    Ui::AllergoMainWin *ui;
};

#endif // ALLERGOMAINWIN_H
