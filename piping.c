#include "headers.h"
#include "piping.h"
#include "strcompare.h"

void piping(char *cmnd_arg0, char *prog_home, char *cmnd_list, int pipe_count)

{

    // SECTION 1: Extracting commands
    char cmnd_list_copy[10000];

    int t = 0;
    int s = 0;

    while (cmnd_list[t] != '\0')
    {
        if (!(cmnd_list[t] == ' ' && cmnd_list[t + 1] == '|') && !(cmnd_list[t - 1] == '|' && cmnd_list[t] == ' '))
        {
            cmnd_list_copy[s] = cmnd_list[t];
            // printf("%c\n",cmnd_list_copy[s]);
            s++;
        }

        t++;
    }

    cmnd_list_copy[s] = '\0';

    // printf("REACHED HERE HERE\n");

    // printf("%s\n",cmnd_list_copy);
    // printf("REACHED HERE HERE\n");

    char *cmnd_array[10000];

    char *token = strtok(cmnd_list_copy, "|");
    int i = 0;
    while (token != NULL)
    {
        cmnd_array[i] = token;
        cmnd_array[i][strlen(cmnd_array[i])] = '\0';
        token = strtok(NULL, "|");
        i++;
    }

    // printf("%d\n", i);
    // printf("%d\n", pipe_count);

    // printf("%c\n",cmnd_array[0][strlen(cmnd_array[0])]);

    // for (int j = 0; j < i; j++)
    // {
    //     printf("\"%s\"\n", cmnd_array[j]);
    // }
    
    // SECTION 2: Creating pipes


    int f = open("pipe_stdout.txt", O_WRONLY | O_CREAT |O_TRUNC, 0644);
    close(f);
    int original_in = dup(STDIN_FILENO);
    int original_out = dup(STDOUT_FILENO);

    int fd[2];
        fd[0] = open("pipe_stdout.txt", O_WRONLY | O_CREAT , 0644);
        fd[1] = open("pipe_stdout.txt", O_RDONLY);




    int j = 0;
    for (int j = 0; j < pipe_count; j++)
    {

        char cmnd_arg0_left[10000];

        int k = 0;

        // printf("reached here\n");
        // printf("%d\n",strlen(cmnd_array[j]));
        while (k < strlen(cmnd_array[j]))
        {
            if(cmnd_array[j][k] == ' ')
            break;
            else {
            cmnd_arg0_left[k] = cmnd_array[j][k];
            // printf("%c\n", cmnd_arg0_left[k]);
            //printf("%s\n", cmnd_array[j]);
            }
             k++;
        }

        cmnd_arg0_left[k] = '\0';
       // printf("%s\n", cmnd_arg0_left);

        char cmnd_arg0_right[10000];
        k = 0;
        while (k < strlen(cmnd_array[j+1]))
        {
            if(cmnd_array[j+1][k] == ' ')
            break;
            else {
            cmnd_arg0_right[k] = cmnd_array[j+1][k];
            // printf("%c\n", cmnd_arg0_right[k]);
            //printf("%s\n", cmnd_array[j]);
            }
             k++;
        }

        cmnd_arg0_right[k] = '\0';
        // printf("%s\n", cmnd_arg0_right);





       ////////////////////////////////// SECTION : CREATING PIPE /////////////////////////////////////////////////
       // ls -> wc -l   
       // fd1 fd2 
       // ls -> fd1 , fd2 <- wc -l -> fd1 <- cat > 1.txt
       // printf("this shell\n");


        
        


        dup2(fd[0], STDOUT_FILENO);  // ls -> fd[j][0]
        
        
        if(j==0)
        strcompare(cmnd_arg0_left, prog_home, cmnd_array[j]);   // ls -> fd[j][0]

        close(fd[0]);
        
        if(j==pipe_count-1)
        {
            dup2(original_out, STDOUT_FILENO);
        }
        
        

        
        
        dup2(fd[1], STDIN_FILENO);
        close(fd[1]);
        

        strcompare(cmnd_arg0_right, prog_home, cmnd_array[j+1]);

        
        // dup2(original_in, STDIN_FILENO);
        // if(j==pipe_count-1)
        // {
        //     dup2(original_in, STDIN_FILENO);
        // }

       

        // printf("end\n");
    }
     


     dup2(original_in, STDIN_FILENO);
     dup2(original_out, STDOUT_FILENO);
        
}

