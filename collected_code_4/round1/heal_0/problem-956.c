#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void SplitStringAtUpperCase(char *str) {
    const char delim[2] = " ";
    char *token;
    token = strtok(str, delim);

    while (token != NULL) {
        
        if (isupper((unsigned char)token[0])){
            printf("%s\n", token);
        }

        token = strtok(NULL, delim);
    }
}

int main() {
    char str[] = "this Is The Test String To check Function";
    SplitStringAtUpperCase(str);
    return 0;
}