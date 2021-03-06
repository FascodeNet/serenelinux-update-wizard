#include <QApplication>
#include <mainwindow.h>
#include <QCommandLineParser>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <QTranslator>
#include <QDir>
void update_sys();
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QString lang_path = "serenelinux-update-wizard_" + QLocale::system().name();

    QTranslator qtTranslator;
    if(QFile::exists(lang_path + ".qm")){
        std::cout << lang_path.toStdString() << std::endl;
        qtTranslator.load(lang_path);
        app.installTranslator(&qtTranslator);
    }
    QCommandLineParser parser;
    parser.addHelpOption();
    QCommandLineOption nochildkun({"n","nochild"},"no child process");
    parser.addOption(nochildkun);
    parser.process(app.arguments());
    if(parser.isSet(nochildkun)){
        pid_t pidkun=0;
        if((pidkun =fork()) == -1){
            return -1;

        }else if(pidkun != 0){
            _exit(0);
        }
        //setsid();
        signal(SIGHUP, SIG_IGN);
        /*if((pidkun = fork()) == 0){
            _exit(0);
        }*/
        execl(argv[0],argv[0]);

    }
    MainWindow mainwin;
    mainwin.show();
    return app.exec();
}

void update_sys(){
}
