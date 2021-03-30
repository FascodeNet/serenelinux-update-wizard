#include "update_manager.h"

#define UPDATE_VER "33.0.2"
update_manager::update_manager(QObject *parent) : QObject(parent)
{

}
void update_manager::enterOkButton(){
    std::cout << "entered" << std::endl;
    setprogbar(true);
    setMessage("0% Version File Writing...");
    std::fstream system_release_f;
    system_release_f.open("/etc/serenelinux-release",std::ios_base::out | std::ios_base::trunc);
    if(!system_release_f.is_open()){
        exit(-5);
    }
    system_release_f << UPDATE_VER << std::endl;
    system_release_f.close();
    setMessage("1% Updating Packages...");
    {
        pid_t pid=fork();
        if(pid < 0){
            perror("fork");
            exit(-10);
        }else
        if(pid == 0){
            execlp("dnf","dnf","-y","update",NULL);
            perror("exec");
            exit(-11);
        }
        int status;
        pid_t r=waitpid(pid,&status,0);
        if( r < 0){
            perror("waitpid");
            exit(-12);
        }
    }
    setMessage("5% Deleting Flast Gecko...");
    {
        pid_t pid=fork();
        if(pid < 0){
            perror("fork");
            exit(-10);
        }else
        if(pid == 0){
            execlp("dnf","dnf","-y","remove","flast-gecko-nightly",NULL);
            perror("exec");
            exit(-11);
        }
        int status;
        pid_t r=waitpid(pid,&status,0);
        if( r < 0){
            perror("waitpid");
            exit(-12);
        }
    }
    setMessage("10% Installing Firefox...");
    {
        pid_t pid=fork();
        if(pid < 0){
            perror("fork");
            exit(-10);
        }else
        if(pid == 0){
            execlp("dnf","dnf","-y","install","firefox",NULL);
            perror("exec");
            exit(-11);
        }
        int status;
        pid_t r=waitpid(pid,&status,0);
        if( r < 0){
            perror("waitpid");
            exit(-12);
        }
    }
    setMessage("17% Installing LightDM Qt Greeter...");
    {
        pid_t pid=fork();
        if(pid < 0){
            perror("fork");
            exit(-10);
        }else
        if(pid == 0){
            execlp("dnf","dnf","-y","install","lightdm-qtquick-greeter",NULL);
            perror("exec");
            exit(-11);
        }
        int status;
        pid_t r=waitpid(pid,&status,0);
        if( r < 0){
            perror("waitpid");
            exit(-12);
        }
    }
    setMessage("29% changing config lightdm qt...");
    {
         pid_t pid=fork();
         if(pid < 0){
             perror("fork");
             exit(-10);
         }else
         if(pid == 0){
             execlp("sed","sed","-i","s|file://hoge/fuga.png|file://usr/share/backgrounds/serene/serene-wallpaper-1.png|g","/etc/lightdm/lightdm-qtquick-greeter.json",NULL);
             perror("exec");
             exit(-11);
         }
         int status;
         pid_t r=waitpid(pid,&status,0);
         if( r < 0){
             perror("waitpid");
             exit(-12);
         }
    }
    setMessage("60% changing LightDM Config..");
    {
         pid_t pid=fork();
         if(pid < 0){
             perror("fork");
             exit(-10);
         }else
         if(pid == 0){
             execlp("sed","sed","-i","s|lightdm-webkit2-greeter|lightdm-qtquick-greeter|g","/etc/lightdm/lightdm.conf",NULL);
             perror("exec");
             exit(-11);
         }
         int status;
         pid_t r=waitpid(pid,&status,0);
         if( r < 0){
             perror("waitpid");
             exit(-12);
         }
    }
    setMessage("80% Deleting LightDM Webkit");
    {
        pid_t pid=fork();
        if(pid < 0){
            perror("fork");
            exit(-10);
        }else
        if(pid == 0){
            execlp("dnf","dnf","-y","remove","lightdm-webkit2-greeter","lightdm-webkit2-theme-serene",NULL);
            perror("exec");
            exit(-11);
        }
        int status;
        pid_t r=waitpid(pid,&status,0);
        if( r < 0){
            perror("waitpid");
            exit(-12);
        }
    }
    setMessage("100% Success!");
    setprogbar(false);
    show_Finished_Message();

}
