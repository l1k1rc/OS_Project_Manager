/*!
 * @version 4
 * @author Saint-Amand Matthieu, Castelain Julien, Hachoud Rassem
 * @brief File header
 * @file command.func.h
 * @see command.func.c
 */
#ifndef include_fichier_h
#define include_fichier_h
void Usage();
void RecDir(char *path, int flag);
void list_file();
void copy_file();
void remove_file (char *file);
void testInode();
void file_info(char *nameFile);
void createDir(char *nameDirectory);
void create_file(char *buf);
long int findSize(char file_name[]);
#endif /* #ifndef __include_fichier_h__ */
