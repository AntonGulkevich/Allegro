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

    QString imapHost;
    int imapPortEncr;

    QString smtpHost;
    int smtpPortEncr;

    bool selected;

    QCheckBox * checkBox;

    int count;

public:
    explicit Domain(QString _name="", QString _pop3host="", int _pop3PortEncr=0,
                                      QString _imaphost="", int _imapPortEncr=0,
                                      QString _smtphost="", int _smtpPortEncr=0, int _count=0);
    ~Domain();
    Domain(const Domain &_domain);
    bool isSelected();
    QString getName();
    void setSelected(bool state);

    QCheckBox *getChechBoxPtr();
    void UpdateSelection();

    void IncCount();
    int GetCount();
    void SetZeroCount();

    QString GetPop3Host();
    QString GetImapHost();
    QString GetSmtpHost();
    int GetPop3PortEncr();
    int GetImapPortEncr();
    int GetSmtpPortEncr();

    friend QDataStream & operator <<(QDataStream & out, const Domain& domain_);
    friend QDataStream & operator >>(QDataStream & in, Domain& domain_ );
};

#endif // DOMAIN_H
