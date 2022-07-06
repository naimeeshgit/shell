#include "prompt.h"
#include "headers.h"


void prompt(char* username, char* hostname,char* cwd) {
        printf(RED"%s@%s:%s>"RESET, username,hostname,cwd);
}
