#include "headers.h"
#include "pinfo.h"

void pinfo(char* cmnd,char* home)
{
    char* token = strtok(cmnd, " ");
    char* arg1 = strtok(NULL, " ");
    pid_t pid ;



    if (arg1 == NULL)
    {
        pid = getpid();   // get current process id
         
    }
    else
    {
        pid = atoi(arg1);   // get pid from command line
    }

   //  for getting process status and memeory

    long long int v_mem ;
    char state;
    int pgrp = 0;
    int tpgid = 0;
    int check_plus = 0;

     
    char file[10000];
    sprintf(file, "/proc/%d/stat", pid);  // if there is a process running, there is a file called /proc/<PID>/status
    // printf("%s\n", file);

    int fd = open(file, O_RDONLY);
    
    if (fd == -1)
    {
        printf("Process does not exist\n");
        return;

    }
    else
    {
        FILE *fp = fopen(file, "r");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }
        else
        {
            // extract state - 3rd number and memory- 23(v_size) information from /proc/<PID>/status
            fscanf(fp,"%*d %*s %c %*d %d %*d %*d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&state,&pgrp,&tpgid,&v_mem);

           //  printf("%d\n%d\n",pgrp,tpgid);
            if(pgrp == tpgid)
            {
                // printf("Process is in foreground\n");
                check_plus = 1;

            }
            
            
            // printf("State: %c\n", state);
            // printf("Memory: %lld\n", v_mem);
            fclose(fp);
        }


        // get executable path
        sprintf(file, "/proc/%d/exe", pid); // For executable path
        // printf("%s\n", file);

            // /proc/[pid]/exe
            //   Under Linux 2.2 and later, this file is a symbolic link
            //   containing the actual pathname of the executed command.
            //   This symbolic link can be dereferenced normally;
            //   attempting to open it will open the executable.

         char buffer[1000000];
        int ex_link = readlink(file, buffer, sizeof(buffer));
        buffer[ex_link] = '\0';  // null terminate the string

       //  printf("\"%s\"\n", buffer);
 
         
        int a = strlen(buffer);
        int b = strlen(home);
        int c = a - b;
        int check = 0;

        if(c>0)
        {
             for(int i=0;i<b;i++)
             {
                if(buffer[i]!=home[i])
                {
                    check = 1;
                     break;
                }

             }

             // if check = 1  -> buffer isnt inside home directory -> abs path
            // if check = 0  -> buffer is inside home directory -> rel path
        }
        
        else {
            check = 1;   // b>a -> buffer is not inside home directory -> abs path
        }

       
        // Now print all the info stored 

        printf("pid -- %d\n",pid);
        if(check_plus == 1 && (state == 'R' || state == 'S'))
        {
             printf("Process Status -- %c+\n",state);
        }
        else {
             printf("Process Status -- %c\n",state);
        }
        printf("memory -- %lld {Virtual Memory}\n",v_mem);

        if (check == 1)
        {
            printf("Executable Path -- %s\n",buffer);
        }

       else if(check == 0)
        {
             
             char rel_path[10000];
             rel_path[0] = '~';

             for(int i=b;i<a;i++)
            {
                rel_path[i-b+1] = buffer[i];
            }
            rel_path[a-b+1] = '\0';
            printf("Executable Path -- %s\n",rel_path);
             
        }
    

        

        
    }

            


        
        



}






