#ifndef MUMBLEPLUGIN_H
#define MUMBLEPLUGIN_H

#include <QObject>

class MumblePlugin: public QObject
{
    Q_OBJECT

public slots:
    void setPositionalAudio(double x, double y);
};


#endif // MUMBLEPLUGIN_H
