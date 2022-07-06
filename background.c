#include "headers.h"
#include "global_variables.h"
#include "background.h"
pid_t pid;



void background(char* cmnd){
    
char temp[10000];

strcpy(temp,cmnd);
temp[strlen(temp)]='\0';

    

    pid = fork();
   
//    printf("%d\n",pid);
//    printf("%s\n",cmnd);
     
    char * argv[10000];
    int argc = 0;
    char* token = strtok(cmnd, " ");  

     while(token != NULL)
    {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }

    argv[argc] = NULL;

     if(pid<0)
    {
        printf("Error: fork() failed\n");
        return;
    }
    else if(pid==0)
    {
         pid_t pid1 = getpid();

         int check = execvp(argv[0], argv);
        if(check<0)
        {
            printf("Error: execvp() failed\n");
            printf("Command %s not found", argv[0]);
        }

        if(strcmp(argv[0],"vi")==0)
        {
            
            kill(pid1, SIGSTOP);
        }

        exit(0);

    }
    else
    {
        jobs_in_bg++;
       // printf("[%d] %d\n",jobs_in_bg,pid);
        printf("%d %s\n", pid, argv[0]);
        job_list[jobs_in_bg].pid = pid;
        strcpy(job_list[jobs_in_bg].command, temp);
        job_list[jobs_in_bg].job_id = jobs_in_bg;
        job_list[jobs_in_bg].job_run_status = '+';
        printf("[%d] %d\n",jobs_in_bg,pid);
        

    }

    
}