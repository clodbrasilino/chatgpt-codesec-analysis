#include <stdio.h>
#include <regex.h>

void split_string(char *string, char *delimiters) {
    regex_t regex;
    regmatch_t match;
    /* Possible weaknesses found:
     *  Cannot determine that 'delimiters[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int res = regcomp(&regex, delimiters, REG_EXTENDED);

    if (res) {
        printf("Error compiling regex\n");
        return;
    }

    /* Possible weaknesses found:
     *  initialization of 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'strtok' [-Wimplicit-function-declaration]
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char *token = strtok(string, delimiters);
    while (token != NULL) {
        printf("%s\n", token);
        /* Possible weaknesses found:
         *  assignment to 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        token = strtok(NULL, delimiters);
    }

    regfree(&regex);
}

int main() {
    char input_string[] = "This,is;a test-string";
    char delim[] = "[,;]";
    
    split_string(input_string, delim);
    
    return 0;
}