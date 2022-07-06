#include "prompt.h"
#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "repeat.h"
#include "strcompare.h"
#include "foreground.h"
#include "ls.h"
#include "background.h"
#include "pinfo.h"
#include "help.h"
#include "jobs.h"
#include "io.h"
#include "piping.h"
#include "signal.h"

//******************************************************************************
void strcompare(char *cmnd_arg0, char *prog_home, char *cmnd_list)
{

  // printf("\"%s\"\n", cmnd_arg0);
  // printf("\"%s\"\n", prog_home);
  // printf("\"%s\"\n", cmnd_list);

  //---------------------------------------------//
  // SECTION 1: check piping//
  //---------------------------------------------//
  int pipe_flag = 0;
  int pipe_count = 0;

  for (int i = 0; i < strlen(cmnd_list); i++)
  {
    if (cmnd_list[i] == '|')
    {
      pipe_flag = 1;
      pipe_count++;
    }
  }

  if (pipe_flag == 1)
  {
    piping(cmnd_arg0, prog_home, cmnd_list, pipe_count);
  }

  else
  {

    //----------------------------------------------//
    // SECTION 2: Check io redirectrion//
    //----------------------------------------------//
    int io_flag = 0;
    for (int i = 0; i < strlen(cmnd_list); i++)
    {
      // printf("this has been reached\n");
      if (cmnd_list[i] == '>' || cmnd_list[i] == '<')
      {
        // printf("above void input_output fn\n");
        // printf("%s\n",cmnd_list);
        input_output(cmnd_arg0, prog_home, cmnd_list);
        io_flag = 1;
        // printf("below void input_output fn\n");
        break;
      }
    }

    //----------------------------------------------//
    // SECTION 2: normal command execution//
    //----------------------------------------------//

    if (io_flag == 0)
    {
      if (cmnd_list[0] == 'c' && cmnd_list[1] == 'd' && (cmnd_list[2] == ' ' || cmnd_list[2] == '\0')) // If command is cd
      {
        // printf("dcm8.1: %s\n", cmnd_arg0);
        // printf("dcm8.2: %s\n", cmnd);
        cd(cmnd_list, prog_home); // WORKING
                                  //  printf("yo cd returns\n");
      }

      else if (cmnd_list[0] == 'l' && cmnd_list[1] == 's' && (cmnd_list[2] == ' ' || cmnd_list[2] == '\0')) // If command is ls
      {
        // printf("dcm8.3: %s\n", cmnd_arg0);
        // printf("dcm8.4: %s\n", cmnd);
        ls(cmnd_list, prog_home);
      }
      else if (cmnd_list[0] == 'p' && cmnd_list[1] == 'w' && cmnd_list[2] == 'd' && cmnd_list[3] == '\0') // If command is pwd
      {
        // printf("dcm8.5: %s\n", cmnd_arg0);
        // printf("dcm8.6: %s\n", cmnd);
        pwd();
      }
      else if (cmnd_list[0] == 'e' && cmnd_list[1] == 'c' && cmnd_list[2] == 'h' && cmnd_list[3] == 'o' && (cmnd_list[4] == '\0' || cmnd_list[4] == ' ')) // If command is echo
      {
        //  printf("dcm8.7:\"%s\"\n", cmnd_arg0);
        //  printf("dcm8.8:\"%s\"\n", cmnd_list);
        echo(cmnd_list);
      }

      else if (cmnd_list[0] == 'h' && cmnd_list[1] == 'e' && cmnd_list[2] == 'l' && cmnd_list[3] == 'p' && cmnd_list[4] == '\0') // If command is help
      {

        // printf("dcm9.1: %s\n", cmnd_arg0);
        // printf("dcm9.2: %s\n", cmnd);
        help();
      }

      else if (cmnd_list[0] == 'r' && cmnd_list[1] == 'e' && cmnd_list[2] == 'p' && cmnd_list[3] == 'e' && cmnd_list[4] == 'a' && cmnd_list[5] == 't' && cmnd_list[6] == ' ') // If command is repeat
      {
        // repeat(cmnd_list, prog_home);       // WORKING
      }

      else if (cmnd_list[0] == 'p' && cmnd_list[1] == 'i' && cmnd_list[2] == 'n' && cmnd_list[3] == 'f' && cmnd_list[4] == 'o' && (cmnd_list[5] == ' ' || cmnd_list[5] == '\0')) // If command is pinfo
      {
        // printf("dcm10.1: %s\n", cmnd_arg0);
        // printf("dcm10.2: %s\n", cmnd);
        pinfo(cmnd_list, prog_home);
      }

      else if (cmnd_arg0[0] == 'j' && cmnd_arg0[1] == 'o' && cmnd_arg0[2] == 'b' && cmnd_arg0[3] == 's')
      {
        // printf("Reace here \n");
        jobs(cmnd_list);
      }

      else if (cmnd_list[0] == 's' && cmnd_list[1] == 'i' && cmnd_list[2] == 'g')
      {
        // printf("signal \n");
        signal_handler(cmnd_list);
      }
      //----------------------------------------------//
      // SECTION 3: foreground and background command execution//
      //----------------------------------------------//

      else
      {

        // printf("dcm11.1: %s\n", cmnd_arg0);
        // printf("%s\n", cmnd_list);
        // printf("lastchar:\"%c\"\n", cmnd_list[strlen(cmnd_list) - 1]);

        if (cmnd_list[strlen(cmnd_list) - 1] == '&')
        {
          background(cmnd_list);
        }
        else
        {
          // printf("Reace here fore\n");
          foreground(cmnd_list);
        }
      }
    }
  }
}