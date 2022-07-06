#ifndef __IO_H__
#define __IO_H__


 void just_in(char* in_file, char* Cmnd,char* cmnd_arg0,char* prog_home);
void just_out(char* out_file, char* cmnd, char* cmnd_arg0, char* prog_home);
void just_out_append(char* append_file, char* cmnd, char* cmnd_arg0,char* prog_home);
void in_out(char* in_file,char* out_file, char* cmnd, char* cmnd_arg0, char* prog_home);
void in_out_append(char* in_file, char* append_file, char* cmnd, char* cmnd_arg0,char* prog_home);
void input_output(char* cmnd_arg0,char* prog_home, char *cmnd);

#endif