#include "pwd.h"
#include <unistd.h>
#include "headers.h"

void pwd()
{
    
    char* temp_pwd = getcwd(NULL, 0);
    printf("%s\n", temp_pwd);
    

}