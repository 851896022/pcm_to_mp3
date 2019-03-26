#ifndef WHOLEMINUTE_H
#define WHOLEMINUTE_H

#include <QObject>
#include <QTime>
#include <QTimer>
class wholeMinute : public QObject
{
    Q_OBJECT
public:
    explicit wholeMinute(QObject *parent = nullptr);
    QTimer *timer;
signals:
    void wholeMinuteSignal(int min);
    void wholeSecondSignal(int sec);
public slots:
    void sendSignal();
};

#endif // WHOLEMINUTE_H
