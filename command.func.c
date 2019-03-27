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

}
void testInode(){

}

}
void createDir(char nameDirectory[]){

}
  
long int findSize(char file_name[]) 
{ 

} 
