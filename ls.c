#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
i gave up on implementing flags since it didt seem worth it so for now how this program functions will be hardcoded
idk how i would implement this, i could be lazy and use a long struct with all of the fields but that feels like a waste,
i will need to learn binary operators to properly implement this
const char* const flag_list="aAbBcdlLgrRTp";
-a all
-A almost all
-b binary
-B bytes
-c color
-d only dirs
-g group id
-l list
-L level of depth
-r recurse
-R reverse
-T Tree
-p permissions
*/

int with_flags(void){
struct dirent* dirent;
struct stat fi;
DIR* dir;
char buff[4096];
char* cwd=getcwd(buff, sizeof(buff));
struct passwd* passwd;
dir=opendir(cwd);
while((dirent=readdir(dir))!=NULL){
  if(strcmp(dirent->d_name, ".")!=0 && strcmp(dirent->d_name, "..")!=0){
  int color=0;
  lstat(dirent->d_name, &fi);
  struct tm* tm;
  tm=localtime(&fi.st_mtime);
  char time[200];
  memset(time, '\0', strlen(time));
  strftime(time, 200, "%a %H:%M:%S", tm);
  printf("%s", (fi.st_mode & S_IRUSR) ? "r" : "-");
  printf("%s", (fi.st_mode & S_IWUSR) ? "w" : "-");
  printf("%s", (fi.st_mode & S_IXUSR) ? "x" : "-");
  printf("%s", (fi.st_mode & S_IRGRP) ? "r" : "-");
  printf("%s", (fi.st_mode & S_IWGRP) ? "w" : "-");
  printf("%s", (fi.st_mode & S_IXGRP) ? "x" : "-");
  printf("%s", (fi.st_mode & S_IROTH) ? "r" : "-");
  printf("%s", (fi.st_mode & S_IWOTH) ? "w" : "-");
  printf("%s ", (fi.st_mode & S_IXOTH) ? "x" : "-");
  passwd=getpwuid(fi.st_uid);
  if(passwd==NULL) return 0;
  if(S_ISDIR(fi.st_mode)){
  if(color==0) color=34;
  printf("\e[0;32m%u\e[0m ", fi.st_size);
  printf("%s ", passwd->pw_name);
  printf("\e[0;34m%s\e[0m %s ", dirent->d_name, time);
  }
  if(S_ISREG(fi.st_mode) && !(fi.st_mode & S_IXUSR) && !(fi.st_mode & S_IXGRP) && !(fi.st_mode & S_IXOTH) && !(S_ISDIR(fi.st_mode) && (S_ISREG(fi.st_mode)))){
  if(dirent->d_name[strlen(dirent->d_name)-2]=='.' && dirent->d_name[strlen(dirent->d_name)-1]=='c'){
  if(color==0) color=126; 
  printf("\e[0;32m%u\e[0m ", fi.st_size);
  printf("%s ", passwd->pw_name);
  printf("\033[38:5:208m%s\033[m ", dirent->d_name);
  } else{ 
    if(color==0) color=37;
  printf("\e[0;32m%u\e[0m ", fi.st_size);
  printf("%s ", passwd->pw_name);
  printf("\033[38:5:255m%s\033[m %s ", dirent->d_name, time);
  }
  }
  if(S_ISLNK(fi.st_mode)){
  if(color==0) color=31;
  printf("\033[38:5:239m%s\e[0m ", "-");
  printf("%s ", passwd->pw_name);
  printf("\033[38:5:4m%s\033[m \033[38:5:73m%s\033[m ", time, dirent->d_name);
  }
  if(fi.st_mode & S_IXUSR || !(fi.st_mode & S_IXUSR) && fi.st_mode & S_IXGRP || fi.st_mode & S_IXOTH && !(S_ISDIR(fi.st_mode) && (S_ISREG(fi.st_mode)))){
  if(color==0){ 
  color=32;
  printf("\e[0;32m%u\e[0m ", fi.st_size);
  printf("%s ", passwd->pw_name);
  printf("\e[0;32m%s\e[0m %s ", dirent->d_name, time);
  }
  }
  printf("\n");
}
}
return 0;
}

int main(int argc, char* argv[]){
  /*
  for(int i=0; i<=120; i++){
  printf("\033[38:5:%dm%s\033[m %d\n", i, "hello world", i);
  }
  printf("\033[38:5:73m%s\033[m\n", "hello world");
  */
  with_flags();
  // TODO: come with a way to parse flags like -abcd and have it impact the program
return 0;
} 
