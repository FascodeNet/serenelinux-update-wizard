#include <QCommandLineParser>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
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
#include <QQuickStyle>
#include "update_manager.h"
void update_sys();
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");
    QGuiApplication app(argc, argv);
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
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    QObject *root = engine.rootObjects().first();
    update_manager managerkun;
    QObject::connect(root,SIGNAL(enterOkButton()),&managerkun,SLOT(enterOkButton()));
    QObject::connect(&managerkun,&update_manager::setMessage,[&](QString msg){
    });
    QObject::connect(&managerkun,&update_manager::setprogbar,[&](bool bartype){
    });
    QObject::connect(&managerkun,&update_manager::show_Finished_Message,[&](){
        QObject* dialogkun=engine.rootObjects().first()->findChild<QObject*>("success_dialog");
        dialogkun->setProperty("visible",true);
    });
    return app.exec();
}

void update_sys(){
}
