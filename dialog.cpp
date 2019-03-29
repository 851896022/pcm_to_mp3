#include "dialog.h"
#include "ui_dialog.h"
#include "QDebug"
#include <QTime>
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QApplication>
extern int port;
extern QString name;
QString info;
extern QString baseDir;
void clearFiles(const QString &folderFullPath);
void clearFolder(const QString &folderFullPath);
dialog::dialog(QObject *parent) : QObject(parent)
{
    //ui->setupUi(this);
    udpSocket=new QUdpSocket;
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(OnReceive()));
    //===================================
    mp3set=new settings_t;
    mp3set->channels=EC_MONO;
    mp3set->abr_bitrate=BR_32kbps;
    mp3set->cbr_bitrate=BR_32kbps;
    mp3set->quality=9;
    mp3set->enc_mode=EM_ABR;
    mp3set->resample_frequency=SR_48khz;
    mp3set->in_samplerate=SR_48khz;
    //-----------------------------------

    mp3code=new lameHelper(*mp3set);
    input_pcm=(short int*)malloc(2304);
    //--------------------------------
    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();//当前的小时
    int minute = current_time.minute();//当前的分
    onWholeMinute(hour*60+minute);
    //-------------------------------------

        whmin=new wholeMinute;
        connect(whmin, SIGNAL(wholeMinuteSignal(int)),this,SLOT(onWholeMinute(int)));
        connect(whmin, SIGNAL(wholeSecondSignal(int)),this,SLOT(onWholeSecond(int)));
        QThread *thread = new QThread;
        whmin->moveToThread(thread);
        thread->start();
        state=true;


    //===============================================================
    udpSocket->bind(port);

    qDebug()<<"init ok"<<baseDir;
    //==================================
    info=QString::number(port)+" "+name;
    //this->setWindowTitle(info);
    //==================================
    manageUdpSocket= new QUdpSocket;
    connect(manageUdpSocket,SIGNAL(readyRead()),this,SLOT(receiveOrder()));
    //manageUdpSocket->bind(port+100);
    //========读取文件保存时间=================
    QString saveDayDir=qApp->applicationDirPath()+"/sav/saveday.sav";
    QFile *file = new QFile(saveDayDir);
    if(file->open(QIODevice::ReadOnly))
    {
        QString ba=file->readLine();
        if(ba.toInt()>9);
        {
            saveDay=ba.toInt();
        }
        qDebug()<<"saveDay"<<saveDay;

        file->close();
    }
    delete(file);
}
void dialog::onWholeMinute(int min)//整分钟，修改文件名
{

    QString hh,mm;
    hh=QString::number(min/60);
    mm=QString::number(min%60);
    //新建文件夹
    QDateTime currentTime = QDateTime::currentDateTime();
    {
        QString tmpDir=baseDir+"/"+currentTime.toString("yyyy-MM-dd");
        QDir *temp = new QDir;
        if(!(temp->exists(tmpDir)))
        {
            temp->mkdir(tmpDir);
        }
        delete temp;
    }
    nowDir=baseDir+"/"+currentTime.toString("yyyy-MM-dd/hh时");
    QDir *temp = new QDir;
    if(!(temp->exists(nowDir)))
    {
        temp->mkdir(nowDir);
    }
    delete temp;

    filename=nowDir;
    filename+="/";
    filename+=(name+currentTime.toString("-yyyy年MM月dd日hh时mm分"));
    //filename+=hh+"时"+mm+"分";
    filename+=".mp3";
    QString tmp;
    if(state) tmp+="working ";
            else tmp+="stop ";
    tmp+=info+" "+filename;
    //this->setWindowTitle(tmp);
    if(preState==1)
    {
        preState=0;
        state=false;
    }
    //删除文件夹
    {
        for(int i=0;i<365;i++)
        {
            QString day=currentTime.addDays(0-i-saveDay).toString("yyyy-MM-dd");
            QString dayDir=baseDir+"/"+day;

            QDir dir;
            if(dir.exists(dayDir))
            {

                {
                    clearFolder(dayDir);
                    qDebug()<<"删除"<<dayDir;

                }
                //dir.rmpath(dayDir);
            }

        }
    }
}
void dialog::onWholeSecond(int sec)//整秒钟
{
    //qDebug()<<preState<<state;
    if(preState==2&&false)
    {

        QString hh,mm,ss;
        hh=QString::number(sec/3600);
        mm=QString::number((sec%3600)/60);
        ss=QString::number((sec%3600)%60);
        filename=baseDir;
        filename+="/";
        filename+=hh+"-"+mm+"-"+ss;
        filename+=".mp3";

        state=true;
        preState=0;


        QString tmp;
        if(state) tmp+="working ";
        else tmp+="stop ";
        tmp+=info+" "+filename;
        //this->setWindowTitle(tmp);



    }
    //ui->lineEdit->setText("no data");
    if(state&&((sec%10)==0))
    {
        QFile *file = new QFile(filename);
        if(file->open(QIODevice:: Append))
        {
            int writeSize=file->write(mp3buff.data(),mp3buff.count());
            if(writeSize<5)
            {

                if(udpSocket)
                {
                    delete mp3code;
                    mp3code=new lameHelper(*mp3set);
                    disconnect(udpSocket,SIGNAL(readyRead()),this,SLOT(OnReceive()));
                    udpSocket->deleteLater();
                    udpSocket=new QUdpSocket;
                    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(OnReceive()));

                }
                qDebug()<<name<<"reboot socket and mp3code";
            }
            file->flush();
            file->close();
        }
        delete(file);
        mp3buff.clear();
    }
    QString data;
    data+=("1|"+QString::number((port-50000)/10)+"|"+QString(QByteArray(filename.toStdString().data()).toBase64()));
    data+=";";
    manageUdpSocket->writeDatagram(data.toLatin1(),QHostAddress("127.0.0.1"),2500);

}
void dialog::OnReceive()
{

    unsigned char ch[65536]={0};
    int realsize=0;
    unsigned char mp3code_output[1153]={0};
    size_t mp3code_done=0;

    while(udpSocket->bytesAvailable())
    {


        realsize=udpSocket->readDatagram((char*)ch, 65536);
        mp3code->encode((short int *)ch,realsize/2,mp3code_output,1153,&mp3code_done);
        mp3buff.append((char*)mp3code_output,mp3code_done);


    }
}


dialog::~dialog()
{
    //delete ui;
}
void dialog::receiveOrder()
{
    unsigned char ch[65536]={0};
    int realsize=0;

    if(manageUdpSocket->pendingDatagramSize()>0)
    {

        realsize=manageUdpSocket->readDatagram((char*)ch, 65536);
        QString tmp;
        //ui->lineEdit->setText(tmp);
        tmp=QString(QLatin1String((char*)ch));
        //ui->lineEdit->setText(tmp);
        QStringList order=tmp.split("|");
        qDebug()<<order;
        //端口|命令|其他
        if(!(order.count()==3)) return;
        if(!(order.first().toInt()==port)) return;
        switch (order.at(1).toInt())
        {
        case 1:
        {
            preState=1;
            break;
        }
        case 2:
        {
            preState=2;
            break;
        }

        default:
        {

        }
        }


    }
    realsize=realsize;//去除烦人的警告
}
/********************************************************************************
说明：删除文件及文件夹涉及到的类包括QDir、QFile、QFileInfo、QFileInfoList，
      清空文件夹的方法很多，此处仅给出我常用的两种方法
*********************************************************************************/

/********************************************************************************
clearFiles():仅清空文件夹内的文件(不包括子文件夹内的文件)
folderFullPath:文件夹全路径
*********************************************************************************/
void clearFiles(const QString &folderFullPath)
{
    QDir dir(folderFullPath);
    dir.setFilter(QDir::Files);
    int fileCount = dir.count();
    for (int i = 0; i < fileCount; i++)
        dir.remove(dir[i]);
}

/********************************************************************************
clearFolder():删除非空文件夹
folderFullPath:文件夹全路径
*********************************************************************************/
void clearFolder(const QString &folderFullPath)
{

    QDir             dir(folderFullPath);
    QFileInfoList    fileList;
    QFileInfo        curFile;
    QFileInfoList    fileListTemp;
    int              infoNum;
    int              i;
    int              j;
    /* 首先获取目标文件夹内所有文件及文件夹信息 */
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                                |QDir::Readable|QDir::Writable
                                |QDir::Hidden|QDir::NoDotAndDotDot
                                ,QDir::Name);

    while(fileList.size() > 0)
    {
        infoNum = fileList.size();

        for(i = infoNum - 1; i >= 0; i--)
        {
            curFile = fileList[i];
            if(curFile.isFile()) /* 如果是文件，删除文件 */
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }

            if(curFile.isDir()) /* 如果是文件夹 */
            {
                QDir dirTemp(curFile.filePath());
                fileListTemp = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
                                                    | QDir::Readable | QDir::Writable
                                                    | QDir::Hidden | QDir::NoDotAndDotDot
                                                    , QDir::Name);
                if(fileListTemp.size() == 0) /* 下层没有文件或文件夹 则直接删除*/
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else /* 下层有文件夹或文件 则将信息添加到列表*/
                {
                    for(j = 0; j < fileListTemp.size(); j++)
                    {
                        if(!(fileList.contains(fileListTemp[j])))
                        {
                            fileList.append(fileListTemp[j]);
                        }
                    }
                }
            }
        }
    }
    dir.rmdir(".");/*删除目标文件夹,如果只是清空文件夹folderFullPath的内容而不删除folderFullPath本身,则删掉本行即可*/
}
