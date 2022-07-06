#include "headers.h"
#include "prompt.h"
#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "repeat.h"
#include "strcompare.h"
#include "background.h"
#include "foreground.h"
#include "ls.h"
#include "help.h"
#include "pinfo.h"

#define MAX_TOKENS 10000

void repeat(char *cmnd, char *prog_home)
{

    //------------------------------------------------------------------//
    // SECTION 1  //
    //------------------------------------------------------------------//

    //-------------------------------------------------------------------//
    // SECTION 1.1: tokenizing the command and storing//
    //-------------------------------------------------------------------//

    int i = 0;
    char *token = strtok(cmnd, " ");
    char *tokens[MAX_TOKENS];
    while (token != NULL)
    {
        tokens[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    int j = atoi(tokens[1]);
    int arg_count = i;
    // printf("%d\n",j);

    // repeat 3 cd dir
    // token = repeat
    // tokens[0] = repeat
    // token = 3
    // i = 1
    // tokens[1] = 3
    // token = cd
    // i = 2
    // tokens[2] = cd
    // token = dir
    // i = 3
    // tokens[3] = dir
    // token = NULL
    // i = 4

    // i = 4, no. of rows in tokens = 4
    // tokens[0] , tokens [1] -> used/stored

    //-------------------------------------------------------------------//
    // SECTION 1.2: adding null char in the end of each token//
    //-------------------------------------------------------------------//

    for (int k = 0; k < arg_count; arg_count++)
    {
        tokens[arg_count][strlen(tokens[arg_count])] = '\0';
    }

    //-------------------------------------------------------------------//
    // SECTION 1.3: storing the command to be repeated in a 2D array where no. of rows = no. of times to be repeated = j and every row has command + adding a null char//
    //-------------------------------------------------------------------//

    int t = 0;
    char extracted_cmnd[j][10000];

    int count_cmnds = 0;
    for (t = 0; t < j; t++)
    {
        for (int k = 2; k < i - 1; k++)
        {
            strcat(extracted_cmnd[t], tokens[k]);
            strcat(extracted_cmnd[t], " ");
        }
        strcat(extracted_cmnd[t], tokens[i - 1]);            // last token no need to add space
        extracted_cmnd[t][strlen(extracted_cmnd[t])] = '\0'; // null terminate the string

        // printf("insidefor: %s\n",extracted_cmnd[t]);
    }

    // printf("token2: %s\n",tokens[2]);

    t = 0;

    // tokens[0] = repeat
    // tokens[1] = number
    // tokens[2] = command
    // tokens[3] = command arguments

    // extracted_cmnd[] = cmnd_list













    //------------------------------------------------------------------//
    // SECTION 2: While(j--)  //
    //------------------------------------------------------------------//

    while (j--)
    {

        if (strcmp(tokens[2], "cd") == 0) // If command is cd
        {
            // printf("dcm8.1: %s\n", cmnd_arg0);
            // printf("dcm8.2: %s\n", cmnd);
            cd(extracted_cmnd[t], prog_home); // WORKING
            //  printf("yo cd returns\n");
            t++;
        }

        else if (strcmp(tokens[2], "ls") == 0) // If command is ls
        {
            // printf("dcm8.3: %s\n", cmnd_arg0);
            // printf("dcm8.4: %s\n", cmnd);
            ls(extracted_cmnd[t], prog_home);
            t++;
        }
        else if (strcmp(tokens[2], "pwd") == 0) // If command is pwd
        {
            // printf("dcm8.5: %s\n", cmnd_arg0);
            // printf("dcm8.6: %s\n", cmnd);
            pwd();
            t++;
        }
        else if (strcmp(tokens[2], "echo") == 0) // If command is echo
        {
            // printf("dcm8.7: %s\n", cmnd_arg0);
            // printf("dcm8.8: %s\n", cmnd);
            echo(extracted_cmnd[t]);
            t++;
        }

        else if (strcmp(tokens[2], "exit") == 0) // If command is exit
        {
            return;
        }

        else if (strcmp(tokens[2], "help") == 0) // If command is help
        {

            // printf("dcm9.1: %s\n", cmnd_arg0);
            // printf("dcm9.2: %s\n", cmnd);
            help();
            t++;
        }

        else if (strcmp(tokens[2], "repeat") == 0) // If command is repeat
        {
            repeat(extracted_cmnd[t], prog_home); // WORKING
            t++;
        }

        else if (strcmp(tokens[2], "pinfo") == 0) // If command is pinfo
        {
            // printf("dcm10.1: %s\n", cmnd_arg0);
            // printf("dcm10.2: %s\n", cmnd);
            pinfo(extracted_cmnd[t], prog_home);
            t++;
        }

        else
        {
            // printf("dcm11.1: %s\n", cmnd_arg0);
            // printf("dcm11.2: %s\n", cmnd);
            // printf("%s\n", cmnd_list);
            // printf("lastchar:\"%c\"\n",cmnd_list[strlen(cmnd_list)-1]);

            if (extracted_cmnd[t][strlen(extracted_cmnd[t]) - 1] == '&')
            {
                background(extracted_cmnd[t]);
                t++;
            }
            else
            {
                foreground(extracted_cmnd[t]);
                t++;
            }
        }
    }
}