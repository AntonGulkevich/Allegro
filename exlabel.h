#ifndef EXLABEL_H
#define EXLABEL_H

#include <QLabel>
#include <QFont>

class ExLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ExLabel(const QString &text, QWidget *parent = 0);
    ~ExLabel();
    void SetSelectedFont(const QFont &font);
    void SetUnSelectedFont(const QFont &font);
signals:
    void clicked();

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent *event);
private:
    QFont selectedFont;
    QFont unselectedFont;
};

#endif // EXLABEL_H
