#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
int stat;
FILE *f;
char *l= "/bin";
char *simpan="/home/raldo2/SISOP/modul2prak/1problem";
DIR *d;
struct dirent *dir;

f = fopen("/home/raldo2/SISOP/modul2prak/1problem/output.txt","w+");
d = opendir(l);
if(d){
	dir =readdir(d);
	while(dir){
		fprintf(f,"%s\t", dir->d_name);
		dir = readdir(d);
	}
}
fclose(f);

pid_t child_id;
child_id = fork();

  if (child_id > 0) {
    char *argv[4] = {"zip", "/home/raldo2/SISOP/modul2prak/1problem/output.zip", "output.txt", NULL};
    execv("/usr/bin/zip", argv);
  } else if(child_id == 0) {
    while ((wait(&stat)) > 0);
    char *argv[3] = {"rm", "/home/raldo2/SISOP/modul2prak/1problem/output.txt", NULL};
    execv("/bin/rm", argv);
  }
}


