#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
QString name;
int port;
QString baseDir;
void setDebugOutput(const QString &targetFilePath, const bool &argDateFlag = false);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QString log_dir;
    log_dir=qApp->applicationDirPath()+"/log1/%1.log";
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
    return a.exec();
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
        static void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &message_)
        {
            QString message;

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
            textStream << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ) << ": " << message << "\r\n";
        }
    };

    qInstallMessageHandler( HelperClass::messageHandler );
}
