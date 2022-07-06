#include "headers.h"
#include "foreground.h"
#include "global_variables.h"



void foreground(char* cmnd)
{

    char temp[10000];
    strcpy(temp,cmnd);
    temp[strlen(cmnd)]='\0';
    pid_t pid;
    
    pid = fork();
    char * argv[10000];
    int argc = 0;
    char* token = strtok(cmnd, " ");  

    while(token != NULL)
    {
        argv[argc] = token;
        argv[argc][strlen(argv[argc])] = '\0';
        argc++;
        token = strtok(NULL, " ");
    }

    // printf("argc = %d\n", argc);
    // for(int i = 0; i < argc; i++)
    // {
    //     printf("argv[%d] = %s\n", i, argv[i]);
    // }
     argv[argc] = NULL;
    // printf("argv[argc] = %s\n", argv[argc]);




    if(pid<0)
    {
        printf("Error: fork() failed\n");
        return;
    }
    else if(pid==0)
    {
        // printf("%d",pid);
        int check = execvp(argv[0], argv);
        if(check<0)
        {
            printf("Error: execvp() failed\n");
            printf("Command %s not found\n", argv[0]);
        }
        exit(0);
    }
    else
    {
        jobs_in_fg++;
        job_list_fg[jobs_in_fg].pid = pid;
        strcpy(job_list_fg[jobs_in_fg].command, temp);
        job_list_fg[jobs_in_fg].job_run_status = '+';
        job_list_fg[jobs_in_fg].job_id = jobs_in_fg;
        // printf("%d",pid);
        int status;

       // pid_t waitpid(pid_t pid, int *wstatus, int options);
        waitpid(pid, &status, WUNTRACED); 
       //  WUNTRACED   also return if a child has stopped (but not traced via ptrace(2)).  Status for traced children which have stopped is provided even if this   // option is not specified.

    }

    




    
}