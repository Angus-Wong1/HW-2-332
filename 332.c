#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <getopt.h>
//cite
int fsize(const char *file){
    struct stat st;

    if (stat(file,&st)==0)
        return st.st_size;

    return -1;
}


char *filetype(unsigned char type) {
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}

void listdir(char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
        
            if (!(strcmp(filetype(entry->d_type),"symbolic link"))){
            char path[1024];
            char bff[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            readlink(path,bff,sizeof(bff)-1);
            //printf("%*s %s %s \n", indent, "", entry->d_name,(path));
            printf("%*s %s", indent, " ", entry->d_name);
            printf("symbolic link ->(%s)\n",bff);
            continue;
            }
            else{
            char path[1024];

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s %s\n", indent, " ", entry->d_name);
            }
        }
    }
    closedir(dir);
}
void S(char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            S(path, indent + 2);
        } else {
        
            if (!(strcmp(filetype(entry->d_type),"symbolic link"))){
            char path[1024];
            char bff[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            readlink(path,bff,sizeof(bff)-1);
            //printf("%*s %s %s \n", indent, "", entry->d_name,(path));
            printf("%*s %s", indent, " ", entry->d_name);
            printf("symbolic link ->(%s) (%d)\n",bff,fsize(path));
            }
            else{
            char path[1024];

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s %s (%d)\n", indent, " ", entry->d_name,fsize(path));
                        }
        }
    }
    closedir(dir);
}

void s(char *name, int indent, int bytes)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            s(path, indent + 2,bytes);
        } else {
        
            if (!(strcmp(filetype(entry->d_type),"symbolic link"))){
            char path[1024];
            char bff[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            readlink(path,bff,sizeof(bff)-1);
            //printf("%*s %s %s \n", indent, "", entry->d_name,(path));
            if (fsize(path)>= bytes)
            {
                printf("%*s %s", indent, " ", entry->d_name);
            printf("symbolic link ->(%s) (%d)\n",bff,fsize(path));
            
            }
            }
            else{

            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            if (fsize(path)>= bytes)
            {

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
         printf("%*s %s (%d)\n", indent, " ", entry->d_name,fsize(path));
         
            
                        }
        }
    }
    }
    closedir(dir);
}
void f(char *name, int indent, char* pattern)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR ){
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 )
                continue;
            {
                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

            if (strstr(entry->d_name,pattern)){
            printf("%*s[%s]\n", indent, "", entry->d_name);
            }
            f(path, indent + 2,pattern);
        }} else {
        
            if (!(strcmp(filetype(entry->d_type),"symbolic link"))){
            char path[1024];
            char bff[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            readlink(path,bff,sizeof(bff)-1);
            //printf("%*s %s %s \n", indent, "", entry->d_name,(path));
            if (strstr(entry->d_name,pattern))
            {
                printf("%*s %s", indent, " ", entry->d_name);
            printf("symbolic link ->(%s) (%d)\n",bff,fsize(path));
            
            }
            }
            else{

            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            if (strstr(entry->d_name,pattern))
            {

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
         printf("%*s %s (%d)\n", indent, " ", entry->d_name,fsize(path));
         
            
                        }
        }
    }
    }
    closedir(dir);
}


int main(int argc,char **argv) {
    if(argc<2){
        listdir(".", 0);
        exit(-1);
    }
    printf("\nFUNCTION FOR LOWERCASE S, sorry");
    s(argv[1], 0,100);

    printf("\n\n\n\n\nFUNCTION FOR S ,\n ");
    S(argv[1],0);


    printf("\n\n\n\n\nFUNCTION FOR f ,\n ");

    f(argv[1], 0,"out");
    return 0;}

