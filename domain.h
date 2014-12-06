#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>
#include <QCheckBox>
#include <QWidget>
#include <QBoxLayout>

#include <QDataStream>

class Domain
{
private:
    QString name;

    QString pop3Host;
    int pop3PortEncr;
    int pop3PortNoEncr;

    QString imapHost;
    int imapPortEncr;
    int imapPortNoEncr;

    bool selected;

    QCheckBox * checkBox;

public:
    explicit Domain(QString _name="", QString _pop3host="", int _pop3PortEncr=0, int _pop3PortNoEncr=0,
                                      QString _imaphost="", int _imapPortEncr=0, int _imapPortNoEncr=0);
    ~Domain();
    Domain(const Domain &_domain);
    bool isSelected();
    QString getName();
    void setSelected(bool state);

    QCheckBox *getChechBoxPtr();
    void UpdateSelection();

    friend QDataStream & operator <<(QDataStream & out, const Domain& domain_);
    friend QDataStream & operator >>(QDataStream & in, Domain& domain_ );
};

#endif // DOMAIN_H
