#include "headers.h"
#include "signal.h"
#include "global_variables.h"


void signal_handler(char* cmnd)
{

    char* token = strtok(cmnd, " ");
    token = strtok(NULL, " ");
    char* job_no = token;
    token = strtok(NULL, " ");
    char* signal_num = token;

    int job_num = atoi(job_no);
    int sig_num = atoi(signal_num);

    if(job_num == 0)
    {
        printf("Invalid job number\n");
        return;
    }

    if(job_num > jobs_in_bg)
    {
        printf("Invalid job number\n");
        return;
    }
    
    int job_pid = job_list[job_num].pid;
    
    kill(job_pid, sig_num);
    

}