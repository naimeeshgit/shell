#ifndef __LS_H__
#define __LS_H__


void just_ls();
void ls_dir(char *given_dir_file, char* prog_home,int t);
void ls_a(char* dir_or_file, char* prog_home,int t);
void ls_l(char *given_dir, char* prog_home, int t);
void ls(char* cmnd,char* prog_home);
void ls_l_a(char* given_dir, char* prog_home,int t);

#endif