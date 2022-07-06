#include "headers.h"
# include "cd.h"

void cd(char *cmnd,char* home)
{
   
     cmnd[strlen(cmnd)]='\0';  
    

      char* temcd_token = strtok(cmnd, " ");
      // printf("%s\n",temcd_token);
      int count = 0;
      int len = 0;
      char  PATH_OR_DIR[10000];
      while(temcd_token != NULL)
      {
            temcd_token = strtok(NULL, " ");
            // printf("beforecount: %s\n",temcd_token);
            count++;

             // printf("afterct: %d\n",count);


            if(count == 1)
            {
                 for(int i = 0; i < strlen(temcd_token); i++)
                    {
                       PATH_OR_DIR[i] = temcd_token[i];
                     }
                  
                  len = strlen(temcd_token);
                 // printf("insideif: %s\n",PATH_OR_DIR);
            }
            
            // printf("afterif: %d\n",count);
            fflush(stdout);
           
      }
      
      PATH_OR_DIR[len] = '\0';
      // printf("while_out: %s\n",PATH_OR_DIR);

     // token/strtok is better   -> count argument // dir name/path 

     if(count>2)
     {
           printf("too many arguments bruh, cd just asks for one\n"); 

     }

     else if(count==1)
     {
          chdir(home);
     }
     else if(count==2)
     {
          

          // Case 1 : cd ..
          if(strcmp(PATH_OR_DIR,"..")==0)
          {
             chdir("..");
          }
          // Case 2 : cd ~
          else if(strcmp(PATH_OR_DIR,"~")==0)
          {
             chdir(home);
          }
          // Case 3 : cd .
          else if(strcmp(PATH_OR_DIR,".")==0)
          {
             chdir(".");
          }
          // Case 4 : cd -
          else if(strcmp(PATH_OR_DIR,"-")==0)
          {
             chdir("..");     // doubtful
          }
          // Case 5 : cd <directory>
          else if(PATH_OR_DIR[0]=='.')
          {
             if(strlen(PATH_OR_DIR)>1)
             {
               chdir(PATH_OR_DIR);
             }
            

          }
          else if(PATH_OR_DIR[0]=='~')
          {
             if(strlen(PATH_OR_DIR)>1)
             {
                // printf("%s\n",PATH_OR_DIR);
                 char temp[10000];
                  strcpy(temp,home);
               strcat(temp,PATH_OR_DIR+1);
               // printf("%s\n",home);
               // printf("%s\n",temp);
               chdir(temp);


             }
             else{
               chdir(home);
             }
          }
          else {
           int i =  chdir(PATH_OR_DIR);
           if(i==-1)
            {
               printf(MAG"cd: %s: No such file or directory\n"RESET,PATH_OR_DIR);
            }

          }
         

     }
}
