#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int with_flags(int count){
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
  printf("\e[0;32m%u\e[0m ", fi.st_size);
  passwd=getpwuid(fi.st_uid);
  if(passwd==NULL) return 0;
  printf("%s ", passwd->pw_name);
  if(S_ISDIR(fi.st_mode)){
  if(color==0) color=34;
  }
  if(S_ISREG(fi.st_mode) && !(fi.st_mode & S_IXUSR) && !(fi.st_mode & S_IXGRP) && !(fi.st_mode & S_IXOTH) && !(S_ISDIR(fi.st_mode) && (S_ISREG(fi.st_mode)))){
  if(color==0) color=37;
  }
  if(S_ISLNK(fi.st_mode)){
  if(color==0) color=33;
  }
  if(fi.st_mode & S_IXUSR || !(fi.st_mode & S_IXUSR) && fi.st_mode & S_IXGRP || fi.st_mode & S_IXOTH && !(S_ISDIR(fi.st_mode) && (S_ISREG(fi.st_mode)))){
  if(color==0) color=32;
  }
  printf("\e[0;%dm%s\e[0m %s ", color, dirent->d_name, time);
  printf("\n");
}
}
return 0;
}

int main(int argc, char* argv[]){
int i;
int buf=0;
unsigned ind=0;
if(argc==1){
  for(i=1; i<argc-1; i++){
  if(argv[i][0]=='-') printf("yes\n");
  return 0;
  }
    
with_flags(argc);
return 0;
}
if(argc>=2){
  // TODO: come with a way to parse flags like -abcd and have it impact the program
  for(i=1; i<=argc-1; i++){
  if(argv[i][0]=='-'){
    if(strlen(argv[i])<2){
     if(argv[i][index]=='a') with_flags(0); 
    }
  ind++;
  if(argv[i][index]=='a');  
  }
  }
with_flags(argc);
return 0;
} 
}
