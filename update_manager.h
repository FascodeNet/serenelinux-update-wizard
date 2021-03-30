#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

#include <QObject>
#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <unistd.h>

class update_manager : public QObject
{
    Q_OBJECT
public:
    explicit update_manager(QObject *parent = nullptr);
public slots:
    void enterOkButton();
signals:
    void setMessage(QString);
    void setprogbar(bool);
    void show_Finished_Message();

};

#endif // UPDATE_MANAGER_H
