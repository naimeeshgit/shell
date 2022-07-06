#include "headers.h"
#include "global_variables.h"

// alphabetical and -r,-s not implemented

void jobs(char *cmnd)
{

    // printf("Reached here\n");
    int r_flag = 0;
    int s_flag = 0;

    for (int i = 0; i < strlen(cmnd); i++)
    {
        if (cmnd[i] == '-')
        {
            if (cmnd[i + 1] == 'r')
            {
                r_flag = 1;
            }
            else if (cmnd[i + 1] == 's')
            {
                s_flag = 1;
            }
            break;
        }
    }

    // printf("%d\n", r_flag);
    // printf("%d\n", s_flag);
    // printf("%d\n",jobs_in_bg);

    for (int i = 1; i <= jobs_in_bg; i++)
    {
        int pid_job = job_list[i].pid;
        // printf("[%d] %d %s\n",i,pid_job,job_list[i].command);

        for(int j=0;j<100;j++)
        {
            fflush(stdout);
        }

         if (job_list[i].job_run_status != 'o')
        {
            // printf("read-jobs\n");
            fflush(stdout);
            char file[10000];
            fflush(stdout);
            sprintf(file, "/proc/%d/stat", pid_job);
            FILE *fp = fopen(file, "r");

            char status;

            

            if (fp < 0)
            {
                printf("No such process exists.\n");
                exit(0);
            }
            else
            {
                

                fscanf(fp,"%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);

               
                fclose(fp);
            }

           
            

            if (status == 'T')
            {

                if (r_flag != 1)
                    printf("[%d] Stopped %s [%d]\n", i, job_list[i].command, pid_job);
            }

            else
            {

                if (s_flag != 1)
                    printf("[%d] Running %s [%d]\n", i, job_list[i].command, pid_job);
            }
        }
    }
}