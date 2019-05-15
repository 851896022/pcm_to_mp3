#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QProcess>
QString name;
int port;
QString baseDir;
void setDebugOutput(const QString &targetFilePath, const bool &argDateFlag = false);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QString log_dir;
    log_dir=qApp->applicationDirPath()+"/log_pcm_to_mp3/%1.log";
    setDebugOutput( log_dir, true );



    if(argc==4)
    {
        port=QString(argv[1]).toInt();
        name=QString(QByteArray::fromBase64(argv[2]));
        baseDir=argv[3];

    }
    else
    {
        port=50001;
        name="ch0";
        baseDir="E:/mp3";
    }
    baseDir+="/"+name;
   QDir *temp = new QDir;
   bool exist = temp->exists(baseDir);
   if(exist)
   {
       qDebug()<<"文件夹已经存在！";
   }

   else
   {
       bool ok = temp->mkdir(baseDir);
       if( ok )
       qDebug()<<"文件夹创建成功！";
   }
    dialog w;

    //w.show();

    int e = a.exec();

    if(e == 777)

    {
        QStringList list;
        QString a= QString(argv[1]);
        QString b= QString(argv[2]);
        QString c= QString(argv[3]);
        list<<a<<b<<c;
       QProcess::startDetached(qApp->applicationFilePath(), list);

       qDebug()<<"重启"<<list;
       return 0;

    }

    return e;
    //return a.exec();
}
//日志生成
void setDebugOutput(const QString &rawTargetFilePath_, const bool &argDateFlag_)
{
    static QString rawTargetFilePath;
    static bool argDateFlag;

    rawTargetFilePath = rawTargetFilePath_;
    argDateFlag = argDateFlag_;

    class HelperClass
    {
    public:
        static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message_)
        {
            QString message;
            QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
            switch ( type )
            {
                case QtDebugMsg:
                {
                    message = message_;
                    break;
                }
                case QtWarningMsg:
                {
                    message.append("Warning: ");
                    message.append(message_);
                    break;
                }
                case QtCriticalMsg:
                {
                    message.append("Critical: ");
                    message.append(message_);
                    break;
                }
                case QtFatalMsg:
                {
                    message.append("Fatal: ");
                    message.append(message_);
                    break;
                }
                default: { break; }
            }

            QString currentTargetFilePath;

            if ( argDateFlag )
            {
                currentTargetFilePath = rawTargetFilePath.arg( ( ( argDateFlag ) ? ( QDateTime::currentDateTime().toString("yyyy_MM_dd") ) : ( "" ) ) );
            }
            else
            {
                currentTargetFilePath = rawTargetFilePath;
            }

            if ( !QFileInfo::exists( currentTargetFilePath ) )
            {
                QDir().mkpath( QFileInfo( currentTargetFilePath ).path() );
            }

            QFile file( currentTargetFilePath );
            file.open( QIODevice::WriteOnly | QIODevice::Append );

            QTextStream textStream( &file );
            textStream << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ) << ": " <<context_info<<"->"<< message << "\r\n";

        }
    };

    qInstallMessageHandler( HelperClass::messageHandler );
}
