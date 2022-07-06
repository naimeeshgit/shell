# include "echo.h"
# include "headers.h"

void echo(char* cmnd)
{
    // printf("%s\n", cmnd);
    char* term_token = strtok(cmnd, " ");
    term_token = strtok(NULL, " ");
    while(term_token != NULL)
    {
        printf("%s ", term_token);
        term_token = strtok(NULL, " ");
    }
    printf("\b");
    printf("\n");
    
}
