#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
  
int main()
{
    char str[] = "Geeks-for-Geeks";
  
    // Returns first token
    char* token = strtok(str, "-");
  
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "-");
    }
  

    char * cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);
    char * token2 = strtok(cwd, "/");
    while (token2 != "UG2-1") {
        printf("%s\n", token2);
        token2 = strtok(NULL, "/");
    }
    
    

}