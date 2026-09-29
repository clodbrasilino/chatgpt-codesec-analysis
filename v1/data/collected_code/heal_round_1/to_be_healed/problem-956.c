#include <stdio.h>
#include <regex.h>

void splitString(char* str) {
    regex_t regex;
    char* pattern = "[A-Z]";
    int reti;

    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        printf("Could not compile regex\n");
        return;
    }

    /* Possible weaknesses found:
     *  initialization of 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'strtok' [-Wimplicit-function-declaration]
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char* token = strtok(str, pattern);
    while (token != NULL) {
        printf("%s\n", token);
        /* Possible weaknesses found:
         *  assignment to 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        token = strtok(NULL, pattern);
    }

    regfree(&regex);
}

int main() {
    char str[] = "SplitThisString";
    splitString(str);
    return 0;
}