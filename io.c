#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "repeat.h"
#include "foreground.h"
#include "ls.h"
#include "background.h"
#include "pinfo.h"
#include "help.h"
#include "jobs.h"
#include "io.h"
#include "strcompare.h"

void input_output(char *cmnd_arg0, char *prog_home, char *cmnd)
{
    // CASES :
    // 1. cat/echo/ls > file
    // 2. >>
    // 3. cat < file
    // 4. < >
    // 5. < >>

    // printf("inside input_output fn\n");

    int out_flag = 0, in_flag = 0, append_flag = 0;
    int out_flag_posn = 0, in_flag_posn = 0, append_flag_posn = 0;
    char *out_file, *in_file, *append_file;

    for (int i = 0; i < strlen(cmnd); i++)
    {
        if (cmnd[i] == '>' && cmnd[i + 1] == '>')
        {

            append_flag = 1;
            append_flag_posn = i;
            i++;
        }
        else if (cmnd[i] == '>')
        {
            out_flag = 1;
            out_flag_posn = i;
        }
        else if (cmnd[i] == '<')
        {
            in_flag = 1;
            in_flag_posn = i;
        }
    }

    // printf("out_flag = %d\n", out_flag);
    // printf("in_flag = %d\n", in_flag);
    // printf("append_flag = %d\n", append_flag);
    // printf("out_flag_posn = %d\n", out_flag_posn);
    // printf("in_flag_posn = %d\n", in_flag_posn);
    // printf("append_flag_posn = %d\n", append_flag_posn);

    // CASES:
    // single : >, >>, <
    // doubled: < >, < >>, > <

    // >, >>, < -> simple printf and scanf
    // command arg < file1 > file2
    // command arg < file1 >> file2

    if (in_flag == 1 && out_flag == 0 && append_flag == 0)
    {
        in_file = (char *)malloc(sizeof(char) * (strlen(cmnd) - in_flag_posn));
        strncpy(in_file, cmnd + in_flag_posn + 2, strlen(cmnd) - in_flag_posn - 1);
        in_file[strlen(cmnd) - in_flag_posn - 1] = '\0';
        // printf("%s\n", in_file);

        just_in(in_file, cmnd, cmnd_arg0, prog_home);
        //scanf("%s", in_file);
        //printf("%s", in_file);
    }
    else if (in_flag == 0 && out_flag == 1 && append_flag == 0)
    {
        // printf("check2\n");
        out_file = (char *)malloc(sizeof(char) * (strlen(cmnd) - out_flag_posn));
        strncpy(out_file, cmnd + out_flag_posn + 2, strlen(cmnd) - out_flag_posn - 1);
        out_file[strlen(cmnd) - out_flag_posn - 1] = '\0';
        // printf("%s\n", out_file);


        just_out(out_file, cmnd, cmnd_arg0, prog_home);

        //scanf("%s", out_file);
        //printf("%s", out_file);
    }

    else if (in_flag == 0 && out_flag == 0 && append_flag == 1)
    {
        append_file = (char *)malloc(sizeof(char) * (strlen(cmnd) - append_flag_posn));
        strncpy(append_file, cmnd + append_flag_posn + 3, strlen(cmnd) - append_flag_posn - 2);
        append_file[strlen(cmnd) - append_flag_posn - 2] = '\0';
        //printf("%s\n", append_file);
        
        just_out_append(append_file, cmnd, cmnd_arg0, prog_home);
        // scanf("%s", append_file);
        // printf("%s", append_file);
    }
      else if (in_flag == 1 && out_flag == 1 && append_flag == 0 && out_flag_posn > in_flag_posn)
    {
        // case : cat < file 1 > file 2
        in_file = (char *)malloc(sizeof(char) * (10000));
        out_file = (char *)malloc(sizeof(char) * (10000));

        int j = 0;
        for(int i=in_flag_posn+2; i<out_flag_posn-1; i++)
        {
            in_file[j] = cmnd[i];
            j++;
        }
        in_file[j] = '\0';
        //printf("\"%s\"\n", in_file);

        j = 0;
        for(int i=out_flag_posn+2; i<strlen(cmnd); i++)
        {
            out_file[j] = cmnd[i];
            j++;
        }
        out_file[j] = '\0';
        //printf("\"%s\"\n", out_file);

        in_out(in_file, out_file, cmnd, cmnd_arg0, prog_home);
    }
    else if (in_flag == 1 && out_flag == 0 && append_flag == 1 && append_flag_posn > in_flag_posn)
    {
        // case : cat < file 1 > file 2
        in_file = (char *)malloc(sizeof(char) * (10000));
        append_file = (char *)malloc(sizeof(char) * (10000));

        int j = 0;
        for(int i=in_flag_posn+2; i<append_flag_posn-1; i++)
        {
            in_file[j] = cmnd[i];
            j++;
        }
        in_file[j] = '\0';
        // printf("%s\n", in_file);

        j = 0;
        for(int i=append_flag_posn+3; i<strlen(cmnd); i++)
        {
            append_file[j] = cmnd[i];
            j++;
        }
        append_file[j] = '\0';
        // printf("%s\n", append_file);

        in_out_append(in_file, append_file, cmnd, cmnd_arg0,prog_home);
    }
    
    
}








//------------------------------------------------------//
//SECTION 3: REDIRECTING FUNCTIONS//
//------------------------------------------------------//










//SECTION 3.1//
void just_in(char *in_file, char *Cmnd, char *cmnd_arg0, char *prog_home)
{
    // printf("inside just_in\n");
    // printf("%s\n", in_file);
    // printf("%s\n", Cmnd);

    int fd;
    fd = open(in_file, O_RDONLY);

   // printf("%d\n", fd);
   //  printf("reached here\n");
    if (fd == -1)
    {
        printf("No such file or directory\n");
        exit(1);
    }
    
   //  printf("reached here\n");
    int original = dup(STDIN_FILENO);
    // printf("%d\n", original);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }
     
    // printf("reached here\n");
    // whether or not the original fd is closed, the duplicated fd remains accessible
    close(fd);

    //--------------------------------------------------------//
    //SECTION 2: Command execution//
    //--------------------------------------------------------//

    // printf("reached here");
    int i = 0;
    char Cmnd_List[10000];
    while (Cmnd[i + 1] != '<')
    {
        Cmnd_List[i] = Cmnd[i];
        i++;
    }
    Cmnd_List[i] = '\0';

    // printf("%s\n", Cmnd_List);

    strcompare(cmnd_arg0, prog_home, Cmnd_List);

    // restore the original fd
    dup2(original, STDIN_FILENO);
    close(original);
}






//SECTION 3.2//
void just_out(char* out_file, char* cmnd, char* cmnd_arg0, char* prog_home)
{

    
    int fd;
    fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("No such file or directory");
        exit(1);

    }

    int original = dup(STDOUT_FILENO);
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }
    
    close(fd);

    int i = 0;
    char Cmnd_List[10000];
    while (cmnd[i + 1] != '>')
    {
        Cmnd_List[i] = cmnd[i];
        i++;
    }
    Cmnd_List[i] = '\0';

    strcompare(cmnd_arg0, prog_home, Cmnd_List);

    dup2(original, STDOUT_FILENO);
    close(original);


}



//SECTION 3.3//
void just_out_append(char* append_file, char* cmnd, char* cmnd_arg0,char* prog_home)
{

    int i = 0;
    char Cmnd_List[10000];
    while (cmnd[i + 1] != '>')
    {
         
        Cmnd_List[i] = cmnd[i];
        i++;
    
    }
    Cmnd_List[i] = '\0';
    // printf("%s\n",Cmnd_List);


    // printf("Reached here\n");
    int fd;
    fd = open(append_file, O_APPEND | O_CREAT | O_WRONLY , 0644);
    // printf("%d\n", fd);

    if (fd == -1)
    {
        printf("No such file or directory");
        exit(1);
    }

    int original = dup(STDOUT_FILENO);
    printf("%d\n", original);
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }

    close(fd);
   
    
    strcompare(cmnd_arg0, prog_home, Cmnd_List);

    dup2(original, STDOUT_FILENO);
    close(original);

}


void in_out(char* in_file,char* out_file, char* cmnd, char* cmnd_arg0, char* prog_home)
{
    // printf("inside in_out\n");
   

    int fd;
    fd = open(in_file, O_RDONLY);
    if (fd == -1)
    {
        printf("No such file or directory\n");
        exit(1);
    }

    int original = dup(STDIN_FILENO);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }

    close(fd);

    int fd2;
    fd2 = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1)
    {
        printf("No such file or directory\n");
        exit(1);
    }

    int original2 = dup(STDOUT_FILENO);

    if (dup2(fd2, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }

    close(fd2);
    

    int i = 0;
    char Cmnd_List[10000];
    while (cmnd[i + 1] != '<')
    {
        Cmnd_List[i] = cmnd[i];
        i++;
    }
    Cmnd_List[i] = '\0';

    // printf("%s\n", Cmnd_List);

    strcompare(cmnd_arg0, prog_home, Cmnd_List);

    
    dup2(original, STDIN_FILENO);
    close(original);

    dup2(original2, STDOUT_FILENO);
    close(original2);


}



void in_out_append(char* in_file, char* append_file, char* cmnd, char* cmnd_arg0,char* prog_home)
{

    int fd;
    fd = open(in_file, O_RDONLY);
    if (fd == -1)
    {
        printf("No such file or directory\n");
        exit(1);
    }

    int original = dup(STDIN_FILENO);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }

    close(fd);

    int fd2;
    fd2 = open(append_file, O_APPEND | O_CREAT | O_WRONLY, 0644);
    if (fd2 == -1)
    {
        printf("No such file or directory\n");
        exit(1);
    }

    int original2 = dup(STDOUT_FILENO);

    if (dup2(fd2, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }

    close(fd2);
    

    int i = 0;
    char Cmnd_List[10000];
    while (cmnd[i + 1] != '<')
    {
        Cmnd_List[i] = cmnd[i];
        i++;
    }
    Cmnd_List[i] = '\0';

    // printf("%s\n", Cmnd_List);

    strcompare(cmnd_arg0, prog_home, Cmnd_List);

    
    dup2(original, STDIN_FILENO);
    close(original);

    dup2(original2, STDOUT_FILENO);
    close(original2);


        


}

