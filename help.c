#include "headers.h"
#include "help.h"


void help()
{
    printf(CYN"quit -> to quit the shell\n"RESET);
    printf(CYN"cd -> change directory\n"RESET);
    printf(CYN"ls -> list files\n"RESET);
    printf(CYN"pwd -> print working directory\n"RESET);
    printf(CYN"echo -> echo command\n"RESET);
    printf(CYN"pinfo -> process info\n"RESET);
    printf(CYN"for repeat command-> repeat <num> <command>\n"RESET);
    printf(CYN"redirection instructions in README.md\n"RESET);
    printf(CYN"history -> to see history\n"RESET);
    printf(CYN"sig <job_id> <sig_num> for sig command\n"RESET);
    printf(CYN"jobs -> to see jobs\n"RESET);


}

