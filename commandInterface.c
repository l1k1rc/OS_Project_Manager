/*!
 * @version 4
 * @author Saint-Amand Matthieu, Castelain Julien, Hachoud Rassem
 * @brief The purpose of this file is to set up a shell-like management interface in which the memory, defined 
 *  at program launch, limits the possibilities of manipulation within the directory.
 *  The user will therefore be able to perform operations such as: 
 *	-viewing file data 
 *	-the visualization of the actions performed since the launch 
 *	-the creation of a file or folder (with limited memory) inside the management directory 
 *	-delete some data.
 * @file main.c
 *
 * @see command.func.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#include "command.func.h"

#define DIM 300
#define CYAN "\033[1;36m" // Bold cyan
#define RED "\033[0;31m" // simple red
#define RED_BOLD "\033[1;31m"//bold red
#define RESET_COLOR "\033[0m"

void talkWithUser(char buf[DIM], int *con,char *argv[],int argc);
void vider_stdin(void);

typedef struct disk {
	int totalSize;
	int inodePosition;
	char nameFile[];
};
/* 
 * This variable is used to store all the information 
 * related to the files created by the user.
 */
static struct disk Vdisk;

int main (int argc, char *argv[]){
	char buf[DIM]={0};
	int connected=1;
	/* 
	* When the user launch the program, a directory is created for the file management.
	* First of all, we check if the program has been launched correctly.
 	*/
	if(argc!=3){
		printf(RED "use: %s <nameFile> <memory>\n" RESET_COLOR, argv[0]);
		return 1;
	}
	if((int) strtol(argv[2], (char **)NULL, 10)<=10){
		printf(RED_BOLD "Insufficient file size : Please, enter a size greater than 10kB.\n " RESET_COLOR);
		return 1;
	}
	createDir(argv[1]);
	//f=fopen(argv[1],"r");
	/* 
	* The size of the disk that will be used as memory during the simulation is stored. 
	* Each time a file is created, its size is allocated and stored in the static 
	* structure variable Vdisk.
	*/
	Vdisk.totalSize=(int) strtol(argv[2], (char **)NULL, 10);
	Vdisk.totalSize*=1000; // 1kB = 1000bytes
	strcpy(Vdisk.nameFile,argv[1]);
	printf("Launching the directory [%s].... Memory assigned to %d bytes.\n", Vdisk.nameFile, Vdisk.totalSize);

	while(connected==1){
		talkWithUser(buf,&connected,argv,argc);
	}
	printf(CYAN "Disconnected.\n");
	return 0;
}
void talkWithUser(char buf[DIM], int *con,char *argv[],int argc){
    
	/* for each command and each arguments associated */
	char line[1024];
	char cmd[1024];
	char arg1[1024];
	char arg2[1024];
	int cursor, result, args;

        while (*con){
		printf("$cmd> ");
		fflush(stdout);

		if(!fgets(line,sizeof(line),stdin)) break;

		if(line[0]=='\n') continue;
		line[strlen(line)-1] = 0;
		/* 
		* In this case, we separate the command with 3 strings of character to use it easily		
		*/
		args = sscanf(line,"%s %s %s",cmd,arg1,arg2);
		if(args==0) continue;

		if(!strcmp(cmd,"ls")) {
			list_file();
		}else if(!strcmp(cmd,"info")) {
			if(args==2){
				cursor = atoi(arg1);
				file_info(arg1);	
			}else{
				printf("use: info <nameFile>\n");
			}
		}else if(!strcmp(cmd,"copy")) {
				copy_file();
		}else if(!strcmp(cmd,"rem")) {
			if(args==2){
				cursor = atoi(arg1);
				remove_file (arg1);	
			}else{
				printf("use: info <nameFile>\n");
			}
		}else if(!strcmp(cmd,"new")) {
			if(args==2){
				cursor = atoi(arg1);
				create_file (arg1);	
			}else{
				printf("use: info <nameFile>\n");
			}
		}else if(!strcmp(cmd,"debug")) {
			printf("The directory [%s] of size [%s] contains :");
			printf("%d inode(s)");
			printf("%d file(s) written in this session");
			printf("%d file(s) written in this session");
		} else if(!strcmp(cmd,"help")) {
			printf("Commands are:\n");
			printf("    info <name_file>\n");
			printf("    copy : indicate the source file then indicate the target file\n");
			printf("    rem <name_file>\n");
			printf("    new <name_file>\n");
			printf("    debug\n");
			printf("    copy\n");
			printf("    help\n");
			printf("    quit\n");
			printf("    exit\n");
		} else if(!strcmp(cmd,"quit")) {
			*con=0;
		} else if(!strcmp(cmd,"exit")) {
			*con=0;
		} else {
			printf("Unknown command: %s\n",cmd);
			printf("Type 'help' for a list of commands.\n");
		}
	}
}
