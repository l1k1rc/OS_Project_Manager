/*!
 * @version
 * @author Saint-Amand Matthieu, Castelain Julien, Hachoud Rassem
 * @brief ensemble des commandes
 * @file command.c
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "command.func.h"

#define GREEN "\033[1;32m" // Bold green == ANSI color
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"
#define RED "\033[0;31m"
#define RESET_COLOR "\033[0m" // When a color is launched in parameter, you have to reset it after the string

/* Allow to tell to the user how the command works and what parameters it should set*/
/*Add pointer to identify the command and what usage send */
void Usage() {
    fprintf(stderr, "\nUsage: exec [OPTION]... [DIR]...\n");
    fprintf(stderr, "List DIR's (directory) contents\n");
    fprintf(stderr, "\nOptions\n-R\tlist subdirectories recursively\n");
}
/*allows you to recursively browse all files in the current path*/
void RecDir(char *path, int flag) {
    DIR * dp = opendir(path);
    if(!dp) {
        perror(path);
    }
    struct dirent * ep;
    char newdir[512];
    //to be adapted for a parameter send with the "ls" command
    while((ep = readdir(dp)))
        if(strncmp(ep->d_name, ".", 1))
            printf(GREEN "\t%s\n" RESET_COLOR, ep->d_name);
    closedir(dp);
    dp = opendir(path);
    while((ep = readdir(dp))) if(strncmp(ep->d_name, ".", 1)) {
        if(flag && ep->d_type == 4) {
            sprintf(newdir, "%s/%s", path, ep->d_name);
            RecDir(newdir, 1);
        }
    }
    closedir(dp);
}
/*Call the function with the parameter of the current path *** To be adapted *** */
void list_file() {
	if(strcmp(".", "-R") == 0) Usage();
	else RecDir(".", 0);
    }
/* Allow to copy a file in another or create this one if it doesn't exist yet */
void copy_file(){
       char ch, source_file[20], target_file[20];
       FILE *source, *target;
     
       printf("Enter name of file to copy\n");
       gets(source_file);// set the program in waiting and send the characters entered to the variable "source_file"
       /*open the source file to copy*/
       source = fopen(source_file, "r");
       /*if it doesn't exist, send a message error */
       if( source == NULL )
       {
          printf(RED "That file doesn't exist...\n" RESET_COLOR);
	  return;
       }
     
       printf("Enter name of target file\n");
       gets(target_file);
       /*if it doesn't exist, create a new file with the name entered */
       target = fopen(target_file, "w");

       if( target == NULL )
       {
          fclose(source);
          printf("Press any key to exit...\n");
	  return;
       }
     
       while( ( ch = fgetc(source) ) != EOF )
          fputc(ch, target);
     
       printf(GREEN "File copied successfully.\n" RESET_COLOR);
     
       fclose(source);
       fclose(target);
}
/*Use open() to create a file and notify the user if the file has been created
------ADD CONDITION IF THE FILE ALREADY EXIST------
*/
void create_file(char *buf){
	int fd2 = open(buf, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	printf(GREEN "Fichier créé\n" RESET_COLOR);
}
void create_directory(char *buf){
	struct stat st = {0};

	if (stat(buf, &st) == -1) {
	    mkdir(buf, 0700);
	    printf(GREEN "Directory created\n" RESET_COLOR);
	}
}
void remove_file (char *file) {
   int ret;

   ret = remove(file);

   if(ret == 0) {
      printf(GREEN "File deleted successfully\n" RESET_COLOR);
   } else {
      printf("Error: unable to delete the file\n");
   }
}
void testInode(){
   FILE *file = fopen("notes.txt", "r");
   int fd = fileno(file); /* Just for fun - extract the file descriptor from a C FILE struct */
   struct stat s;
   fstat(fd, &s);
   printf("Last accessed %s", ctime(&s.st_atime));
}
void file_info(char *nameFile){

	long size; //st_size can be a 64-bit int.
	struct stat *buf = malloc(sizeof(struct stat)); //allocates memory for stat structure.

	if(stat(nameFile, buf) == 0)
	{
	    size = buf->st_size;
	    printf("Size of");
	    printf(GREEN " %s" RESET_COLOR,nameFile);
	    printf(" is %lld bytes.\n", size);
	}
	else
	{
	    perror(nameFile);    //if stat fails, print a diagnostic.
	}
}
void createDir(char nameDirectory[]){

	int pid = getpid();
	char dirName[NAME_MAX+1];
	char *prefix = nameDirectory;

	snprintf(dirName, NAME_MAX + 1,"%s%d", prefix, pid);
	printf("%s\n",dirName);
	struct stat st = {0};
	if (stat(dirName, &st) == -1) {
		if(mkdir(dirName, 0755) != -1){
			char libPath[PATH_MAX+1];
			snprintf(libPath, PATH_MAX + 1, "%s/library.txt", dirName);
			FILE *fLib = fopen(libPath , "w+");
			fclose(fLib);
		}else{
			perror("mkdir: ");
		}
	}
}
  
long int findSize(char file_name[]) 
{ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r"); 
  
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    long int res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
} 
