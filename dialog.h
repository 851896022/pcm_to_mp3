#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QFile>
#include <QDir>
#include <QThread>
#include "lib/lame.h"
#include "lib/lameHelper.h"
#include "lib/wholeminute.h"
namespace Ui {
class dialog;
}

class dialog : public QObject
{
    Q_OBJECT

public:
    explicit dialog(QObject *parent = 0);
    ~dialog();
    QUdpSocket *udpSocket=NULL;
    lameHelper *mp3code;
    short int * input_pcm;
    QString filename;
    wholeMinute *whmin;
    QString nowDir;
    QUdpSocket *manageUdpSocket;
    bool state;
    int preState;
    QByteArray mp3buff;
    settings_t *mp3set;
    //=======================
    int saveDay=3650;
public slots:
    void onWholeMinute(int min);
    void onWholeSecond(int sec);//整分钟，修改文件名
    void OnReceive();
    void receiveOrder();
private:
    //Ui::dialog *ui;
};

#endif // DIALOG_H
