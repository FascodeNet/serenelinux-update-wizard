#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>

#define UPDATE_VER "33.0.1"
void update_xfcemugshotkun();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_installButton_clicked()
{

    std::fstream system_release_f;
    system_release_f.open("/etc/serenelinux-release",std::ios_base::out | std::ios_base::trunc);
    if(!system_release_f.is_open()){
        exit(-5);
    }
    system_release_f << UPDATE_VER << std::endl;
    system_release_f.close();

    update_xfcemugshotkun();
    QMessageBox msgBox(this);
    msgBox.setText(tr("Success Update!"));
    msgBox.setWindowTitle(tr("Success Update!"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

    close();
}

void MainWindow::on_cancelButton_clicked()
{
    close();
}
