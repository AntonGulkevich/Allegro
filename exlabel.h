#ifndef EXLABEL_H
#define EXLABEL_H

#include <QLabel>
#include <QFont>
#include <QMouseEvent>

class ExLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ExLabel(const QString &text, QWidget *parent = 0);
    ~ExLabel();
    void SetSelectedFont(const QFont &font);
    void SetUnSelectedFont(const QFont &font);
    void SetActiveFont(const QFont &font);
    bool isActive();
    void setActive(bool status);

signals:
    void clicked();

public slots:
    void OnClick();

protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent *event);

private:
    QFont *selectedFont;
    QFont *unselectedFont;
    QFont *activeFont;
    bool active;
    QPoint pos;
};

#endif // EXLABEL_H
