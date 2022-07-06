#include "prompt.h"
#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "repeat.h"
#include "strcompare.h"
#include "global_variables.h"

#define MAX_CMND 10000


void done()
        {
            
            // printf("done\n");
            pid_t pid_job;
            int status;
            pid_job = waitpid(-1, &status, WNOHANG);

            for (int i = 1; i < jobs_in_bg;i++)
            {
                if(pid_job<0)
                {
                    perror("waitpid");

                }
                const int exit = WEXITSTATUS(status);
                if(pid_job == job_list[i].pid && WIFEXITED(status))
                {
                           job_list[i].job_run_status = 'o';
                           if(exit==0)
                           {
                                 printf("\n %s with pid %d exited normally\n",job_list[i].command,job_list[i].pid);
                           }
                           else printf("\n %s with pid %d exited abnormally\n", job_list[i].command, job_list[i].pid);

                }
            }

        }



void ctrl_c (int sig)
{
    pid_t pid_job = getpid();
     if(pid_job < 0)
    {
        perror("getpid");
    }
    if(pid_job != shell_pid)
    {
        return;
    }
   
    if(pid_job==shell_pid && job_list_fg[jobs_in_fg].pid == -1)
    {
        printf("\n");
        fflush(stdout);
        return;
    }

    if(job_list_fg[jobs_in_fg].pid != 1)
    {
        kill(job_list_fg[jobs_in_fg].pid, SIGINT);
    }
    
}

void ctrl_z (int sig)
{
    pid_t pid_job = getpid();
    if(pid_job < 0)
    {
        perror("getpid");
    }
    if(pid_job != shell_pid)
    {
        return;
    }
    if(pid_job==shell_pid && job_list_fg[jobs_in_fg].pid == -1)
    {
        fflush(stdout);
        return;
    }
    if(job_list_fg[jobs_in_fg].pid != 1)
    {
        kill(job_list_fg[jobs_in_fg].pid, SIGTTIN);
        kill(job_list_fg[jobs_in_fg].pid, SIGTSTP);
        job_list_fg[jobs_in_fg].job_run_status = 's';
        
        jobs_in_bg++;
        job_list[jobs_in_bg].pid = job_list_fg[jobs_in_fg].pid;
        job_list[jobs_in_bg].job_run_status = 's';
        strcpy(job_list[jobs_in_bg].command,job_list_fg[jobs_in_fg].command);
    }
    


}


void ctrl_d() {

    pid_t pid_job = getpid();
    // printf("Seg fault as shell is trying to exit itself\n");
    exit_num = 1;
    return;

}

int main()
{


    

    shell_pid = getpid();
    printf("%d\n",shell_pid);
    printf(BLU "WELCOME TO THE naimeeSH SHELL" RESET "\n\n");

    exit_num = 0; // exit_num is used to check if the user wants to exit the shell

    //--------------SECTION 1--------------------------------------------//
    // obtaining :- username, hostname, home dir //
    //-------------------------------------------------------------------//

    char *username = getlogin();                        // get username
    char hostname[10000];                               // get hostname
    int host = gethostname(hostname, sizeof(hostname)); // get hostname

    char *prog_home = getcwd(NULL, 0); // get the home working directory (from where shell is initiated)

    // printf("Section1 check1: %s@%s:%s$ \n", username, hostname, prog_home); // print the prompt
    char *name_dir = strrchr(prog_home, '/'); // get name of directory
    // printf("S1 C2: %s\n", name_dir);                              // print name of directory

    // if hostname is not found, print error message
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

    //--------------------------------------------------------//
    // SECTION 2: shell loop //
    //--------------------------------------------------------//

    while (1) // infinite loop to keep prompting
    {

        //--------------------------------------------------------//
        // SECTION 2.1: prompt //
        //--------------------------------------------------------//

        char *cwd = getcwd(NULL, 0); // get the current working directory
                                     // printf("dcm2: %s\n", cwd);

        // //
        if (strcmp(cwd, prog_home) == 0) // if current working directory is the same as the program home directory
        {
            cwd = "~"; // set cwd to ~
        }
        else
        {
            int a = strlen(cwd);
            int b = strlen(prog_home);
            int c = a - b;
            if (c < 0)
            {
                cwd = getcwd(NULL, 0);
            }
            if (c > 0)
            {

                //  printf("dcm3 : %d %d\n", strlen(prog_home), strlen(cwd));

                //  printf("dcm3 : %c %c\n",str[strlen(prog_home)-1],str2[strlen(prog_home)]);

                char rel_temp[10000];

                fflush(stdout);

                int j = 0;
                for (int i = strlen(prog_home); i < strlen(cwd); i++)
                {

                    rel_temp[j] = cwd[i];

                    j++;
                }

                rel_temp[j] = '\0';

                // printf("%s\n", rel_temp);

                char address[10000];
                address[0] = '~';
                address[1] = '\0';
                // printf("%c\n",rel_temp[0]);
                // printf("%c\n", address[1]);
                strcat(address, rel_temp);
                // printf("%s\n", cwd);
                // printf("%s\n", rel_temp);
                // printf("%s\n", address);
                cwd = address;
            }
        }

        prompt(username, hostname, cwd); // Prompt user for command

        // ---------------------------------------------------------//
        // SECTION 2.2: command input //
        // ---------------------------------------------------------//

        //---------------------------------------------------------//
        // SECTION 2.2.1: command input + removing new line at the end + removing extra spaces + adding a null char to the commands string //
        //---------------------------------------------------------//

        char a[10000];        // Buffer for command
        char commands[10000]; // after removing spaces from a

        fgets(a, 10000, stdin); // Get command from user
        if(a[0]=='\n')
        {
            continue;
        }
       
        
        // printf("hekklo");

        // printf("dcm4: %s\n", a);     // temporary check - to be commented out

        int i = 0; // Iterator
        int j = 0; // Iterator

        a[strlen(a) - 1] = '\0'; // remove newline character from command

        while (a[i] != '\0') // While not end of string
        {
            if (!(a[i] == ' ' && a[i + 1] == ' ')) // If not two spaces in a row
            {
                commands[j] = a[i]; // Copy character to commands
                j++;                // Increment j
            }
            i++; // Increment i
        }

        commands[j] = '\0'; // Add null terminator to commands

        // printf("S2.2.1 C1: %s\n", commands);    // temporary check - to be commented out

        //---------------------------------------------------------//
        // SECTION 2.2.2: tokenization for ; char at the end of a command //
        //---------------------------------------------------------//

        char *token;                          // Token for strtok
        char *cmnd_list[MAX_CMND];            // Array of commands
        int count = 1;                        // Count of commands
        cmnd_list[0] = strtok(commands, ";"); // Get first command

        while ((token = strtok(NULL, ";")) != NULL) // While not end of string
        {
            cmnd_list[count] = token; // Get next command
            // printf("S2.2.2 C1:\"%s\"\n", cmnd_list[count]);  // temporary check - to be commented out
            count++; // Increment count
        }

        //  printf("S2.2.2 C2: %d", count); // temporary check - to be commented out

        //---------------------------------------------------------//
        // SECTION 2.2.3: removing begining and ending spaces + also adding null char at the end of all cmnds //
        //---------------------------------------------------------//

        for (int i = 0; i < count; i++)
        {

            //////////// removing begining spaces ////////////////
            // printf("S2.2.3 C1:\"%s\"\n", cmnd_list[i]); // temporary check - to be commented out
            // printf("S2.2.3 C2 0char:\"%c\"\n",cmnd_list[i][0]); // temporary check - to be commented out
            // printf("S2.2.3 C3 end char:\"%c\"\n",cmnd_list[i][strlen(cmnd_list[i])-1]); // temporary check - to be commented out
            if (cmnd_list[i][strlen(cmnd_list[i]) - 1] == ' ')
            {
                cmnd_list[i][strlen(cmnd_list[i]) - 1] = '\0'; // Remove trailing space
            }

            // printf("S2.2.3 C4 end char:\"%c\"\n",cmnd_list[i][strlen(cmnd_list[i])-1]); // temporary check - to be commented out

            // printf("\n");
            if (cmnd_list[i][0] == ' ')
            {

                for (int j = 1; j < strlen(cmnd_list[i]); j++)
                {
                    cmnd_list[i][j - 1] = cmnd_list[i][j];
                }
                cmnd_list[i][strlen(cmnd_list[i]) - 1] = '\0'; // Remove leading space
            }

            if (cmnd_list[i][strlen(cmnd_list[i]) - 1] == ' ')
            {
                cmnd_list[i][strlen(cmnd_list[i]) - 1] = '\0'; // Remove trailing space
            }
            //   printf("S2.2.3 C5:\"%c\"\n",cmnd_list[i][0]); // temporary check - to be commented out
            //   printf("S2.2.3 C6:\"%c\"\n",cmnd_list[i][strlen(cmnd_list[i])-1]); // temporary check - to be commented out
            //   printf("\n\n");
        }

        

        //---------------------------------------------------------//
        // SECTION 2.2.4: signals//
        //---------------------------------------------------------//
         signal(SIGCHLD, done);
        signal(SIGINT, ctrl_c);
        signal(SIGTSTP, ctrl_z);
        

        // ---------------------------------------------------------//
        // SECTION 2.3: Executing the Command //
        // ---------------------------------------------------------//

        for (int i = 0; i < count; i++) // For each command
        {

            //---------------------------------------------------------//
            // SECTION 2.3.1: tokenization for " " to get first argument of any command - like cd, ls, etc //
            //---------------------------------------------------------//
            int jj = 0;
            char cmnd[10000];
            for (int j = 0; j < strlen(cmnd_list[i]); j++)
            {
                cmnd[j] = cmnd_list[i][j];
            }
            // printf("S2.3.1 C1: cmnd: %s\n", cmnd);

            cmnd[strlen(cmnd)] = '\0';

            char *cmnd_arg0 = strtok(cmnd, " "); // Get first argument
            // printf("S2.3.1 C2: cmnd_arg0\"%s\"", cmnd_arg0);
            cmnd_arg0[strlen(cmnd_arg0)] = '\0';

            // char cmnd_arg0[10000];
            // for (int k = 0; k < strlen(cmnd_arg0); k++)
            // {
            //     cmnd_arg0[k] = cmnd_arg0[k];
            // }
            // cmnd_arg0[strlen(cmnd_arg0)] = '\0';

            // printf("S2.3.1 C3: cmnd_arg0:\"%s\"\n", cmnd_arg0);
            // printf("S2.3.1 C4: cmnd_list[i]:\"%s\"\n", cmnd_list[i]);
            // printf("S2.3.1 C5: lastchar:\"%c\"\n", cmnd_list[i][strlen(cmnd_list[i]) - 1]);
            // printf("S2.3.1 C6: firstchar:\"%c\"\n", cmnd_list[i][0]);
            // printf("S2.3.1 C7: cmnd:\"%s\"\n", cmnd);

            
            //------------------------------------------------------------//
            // SECTION 2.3.2: checking for exit command //
            //------------------------------------------------------------//

            if (cmnd_arg0[0] == 'e' && cmnd_arg0[1] == 'x' && cmnd_arg0[2] == 'i' && cmnd_arg0[3] == 't')
            {
                // printf("nd\n");
                exit_num = -1;
                // printf("%d", exit_num);
                break;
            }

            //------------------------------------------------------------//
            // SECTION 2.3.3: sending to strcompare fn //
            //------------------------------------------------------------//

            else
            {
                // printf("reached\n");
                strcompare(cmnd_arg0, prog_home, cmnd_list[i]);
            }

            // cmnd_arg0 -> command name ex- ls,cd,repeat
            // cmnd_arg0 == cmnd_arg0 -> command name ex- ls,cd,repeat
            // cmnd -> not useful
            // prog_home -> stores the string = address of the home directory
            // cmnd_list[i] -> cfull command example cd dir , ls -l etc
        }

        // ---------------------------------------------------------//
        // SECTION 2.4: checking for exit//
        // ---------------------------------------------------------//

        if (exit_num == -1)
        {
            printf(RED "EXITING SHELL" RESET "\n\n");
            break;
        }
    }
}

