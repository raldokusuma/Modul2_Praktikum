#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
  FILE *fp, *fs;
  int i=0;
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
  

  while(1) {
    fp = fopen("/home/usersisop/modul2/induk.txt","r"); 
      if (fp == NULL){
       while(fp == NULL){
          i++;
          char path[100];
          sprintf(path,"/home/usersisop/modul2/virus%d.txt",i);
          fs = fopen(path,"w+");
          fp = fopen("/home/usersisop/modul2/induk.txt","r");
          if(fp!=NULL) exit(EXIT_SUCCESS);
          sleep(10);
       }              
      }
   
      fclose(fp);
   }
  
  exit(EXIT_SUCCESS);
}
