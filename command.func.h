 
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
#endif /* #ifndef __include_fichier_h__ */
