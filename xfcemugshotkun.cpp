#include <filesystem>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
typedef std::string String;
template <class T>
using Vector=std::vector<T>;
namespace fs = std::filesystem;

void update_xfcemugshotkun(){
    fs::path homels("/home");
    Vector<String> rootdirvectkun;
    if(fs::exists(fs::path("/etc/skel"))){
        rootdirvectkun.push_back("/etc/skel");
    }
    if(fs::is_directory(homels)){
        auto it_home = fs::directory_iterator(homels);
        for(auto &entry:it_home){
            if(entry.is_directory()){
                rootdirvectkun.push_back(entry.path());
            }
        }
    }
    for(String entrykun:rootdirvectkun){
        std::cout << entrykun << std::endl;
        fs::path entrypath(entrykun + "/.config/xfce4/panel/whiskermenu-3.rc");
        if(fs::exists(entrypath)){
            pid_t pid=fork();
            if(pid < 0){
                perror("fork");
                exit(-10);
            }else
            if(pid == 0){
                execlp("sed","sed","-i","s|show-command-profile=true|show-command-profile=false|g",entrypath.c_str(),NULL);
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
    }
}
