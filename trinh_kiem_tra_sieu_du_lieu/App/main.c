// include header files
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// global function definition
int main(int argc, char *argv[]) //Kiem tra so luong tham so
{
 if (argc!=2) {
    fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
    return EXIT_FAILURE;
 }
 const char *file_path=argv[1];
 struct stat fileStat;
 if (lstat(file_path, &fileStat) == -1) //Goi lstat de lay thong tin inode
 {
    perror("lstat");
    return EXIT_FAILURE;
 }
 printf ("File Path: %s\n", file_path); //in thong tin
 
 printf ("File Type: "); //Xac dinh loai tep
 if (S_ISREG(fileStat.st_mode))
    printf ("Regular File\n");
 else if (S_ISDIR(fileStat.st_mode))
    printf ("Directory\n");
 else if (S_ISLNK(fileStat.st_mode))
    printf ("Symbolic Link\n");
 else
    printf ("Other\n");

 printf("Size:%lld byte\n", (long long)fileStat.st_size); //In kich thuoc

 char timebuf[100];
 struct tm *tm_info = localtime(&fileStat.st_mtime);
 strftime (timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
 printf("Last Modified: %s\n", timebuf);

    return EXIT_SUCCESS;
}


