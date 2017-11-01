#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
int file_is_modified(const char *path) {
    struct stat file_stat;
    int err = stat(path, &file_stat);
    if (err != 0) {
        perror(" [file_is_modified] stat");
        exit(errno);
    }
    return file_stat.st_mtime;
}

int getChmod(const char *path){
    struct stat ret;

    if (stat(path, &ret) == -1) {
        return -1;
    }

    return (ret.st_mode & S_IRUSR)|(ret.st_mode & S_IWUSR)|(ret.st_mode & S_IXUSR)|/*owner*/
        (ret.st_mode & S_IRGRP)|(ret.st_mode & S_IWGRP)|(ret.st_mode & S_IXGRP)|/*group*/
        (ret.st_mode & S_IROTH)|(ret.st_mode & S_IWOTH)|(ret.st_mode & S_IXOTH);/*other*/
}

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  pid_t child;
  int aa;
  int cc, status;
  cc=getChmod("/home/raldo2/git/syukron.txt");
  aa=file_is_modified("/home/raldo2/git/syukron.txt");
  while(1) {
  child=fork();  
    if(child < 0) exit(EXIT_FAILURE);
    else if(child == 0){
        if (file_is_modified("/home/raldo2/git/syukron.txt") != aa || getChmod("/home/raldo2/git/syukron.txt") != cc){
        char *argv[] = {"cp", "/home/raldo2/git/syukron.txt","/home/raldo2/repo", NULL};
        execv("/bin/cp", argv);
      }
        else kill(getpid(),SIGTERM);
    }
    else {
      while((wait(&status)) > 0);  
      cc = getChmod("/home/raldo2/git/syukron.txt");
      aa = file_is_modified("/home/raldo2/git/syukron.txt");
      
    }  
  }
  
  exit(EXIT_SUCCESS);
}