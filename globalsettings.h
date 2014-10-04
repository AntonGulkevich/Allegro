#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>
#include <QColor>

class GlobalSettings : public QObject
{
    Q_OBJECT
public:
    explicit GlobalSettings(QObject *parent = 0);
    ~GlobalSettings();
private:
    /*Pallette and colours*/
    QColor title_text;
    QColor sub_title_text;
    QColor common_text;
    QColor main_background;

    /*End all about pallette and colours*/

signals:

public slots:

};

#endif // GLOBALSETTINGS_H
