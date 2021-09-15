#include "prompt.h"
#include "headers.h"
#include "unistd.h"
#include "limits.h"
#include "stdlib.h"
#include <stdio.h>
#include "string.h"
// #include "conio.h"

#define MAX_CMND 1024

int main()
{
    char *username = getlogin();
    char hostname[256];
    int host = gethostname(hostname, sizeof(hostname));
    char *cwd = getcwd(NULL, 0);
    char* name_dir = strrchr(cwd, '/');
    printf("%s",name_dir);
    if (host == -1)
    {
        perror("gethostname");
        hostname[0] = 'U';
        hostname[1] = 'n';
        hostname[2] = 'k';
        hostname[3] = 'n';
        hostname[4] = 'o';
        hostname[5] = 'w';
        hostname[6] = 'n';
        hostname[7] = '\0';
    }
    char *prog_home = getcwd(NULL, 0); // get the current working directory
    //  printf("dcm0: %s\n",cwd);
    //  char *home = getenv("HOME");
    //  char *path = getenv("PATH");
    //  char *shell = getenv("SHELL");
    //  char *term = getenv("TERM");

    while (1)
    {
        prompt(username, hostname); // Prompt user for command
        getcwd(cwd, sizeof(cwd));
        


        if(strcmp(cwd, prog_home) == 0)
        {
            cwd = "~";
        }
        else{
           int  a = strlen(cwd);
           int  b = strlen(prog_home);
           int  c = a - b;
           if(c>0)
           {
               char* relative_path = cwd;
               char** relative_path_array ;
               
               
               int i = 0;
               while(strcmp(relative_path_array[i], name_dir) != 0)
               {
                   i++;
                   
               }
               
               while()


           }

        }
        char a[PATH_MAX];                   // Buffer for command
        char commands[PATH_MAX];    // after removing spaces from a


        gets(a); // Get command from user
        if (strlen(a) > 4096)
        {
            printf("Command too long\n"); // If command is too long
            continue;                     // Continue to prompt user for command
        }
        int i = 0;
        int j = 0;

        while (a[i] != '\0')
        {
            if (!(a[i] == ' ' && a[i + 1] == ' '))
            {
                commands[j] = a[i];
                j++;
            }
            i++;
        }

        commands[j] = '\0';

     // debug check main 1
     //  printf("dcm1: %s\n", commands);
        
        
        char *token;
        char *cmnd_list[MAX_CMND];
        int count = 1;
        cmnd_list[0] = strtok(commands, ";");

        while ((token = strtok(NULL, ";")) != NULL)
        {
            cmnd_list[count] = token;
            count++;
        }


        // dcm2 :
        // for (int i = 0; i < count; i++)
        // {
        //     printf("dcm2: %s\n", cmnd_list[i]);
        // }

        // TAKE INPUT HERE

        for(int i = 0; i < count; i++)
        {
            char * cmnd = cmnd_list[i];
            // printf("cmnd: %s\n", cmnd);
            
            if(strcmp(cmnd, "exit") == 0)
            {
                continue;
            }
            else if(strcmp(cmnd, "clear") == 0)
            {
                //
            }
            else if(strcmp(cmnd, "cd") == 0)
            {
                  printf("cd");
            }
            else if(strcmp(cmnd, "pwd") == 0)
            {
                printf("pwd");
            }
            else if(strcmp(cmnd, "ls") == 0)
            {
                printf("ls");
            }

        }


    }
}
