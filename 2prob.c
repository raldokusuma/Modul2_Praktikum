#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  pid_t child;
  int stat;

  child = fork();
  if(child < 0) exit(EXIT_FAILURE);
  else if (child == 0) {
    char *argv[] = {"unzip", "/home/raldo2/SISOP/modul2prak/2problem/access.log.2.zip", NULL};
    execv("/usr/bin/unzip", argv);
  }
    else while ((wait(&stat)) > 0);

FILE *fs;
FILE *fp;
char c[1000];
fp = fopen ("/home/raldo2/SISOP/modul2prak/2problem/access.log.2","r");
fs = fopen ("/home/raldo2/SISOP/modul2prak/2problem/output.txt", "w+");
while(fgets(c,1000,fp) != NULL){
	if(strstr(c,"Apache") != NULL){
		fprintf(fs,"%s",c);
	}
}
fclose(fs); fclose(fp);

    char  *arr[] = {"rm","/home/raldo2/SISOP/modul2prak/2problem/access.log.2",NULL};
    execv("/bin/rm", arr);


}
