#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX 100

void SpaceCapitals(char * str) {
    regmatch_t match[MAX];
    regex_t regex;
    
    if(regcomp(&regex, "[A-Z]", 0) != 0) {
        printf("Failed to compile regex.\n");
        return; 
    }

    char temp[MAX];
    int offset = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'regex_exec'; did you mean 'regwnexec'? [-Wimplicit-function-declaration]
         */
        if (regex_exec(&regex, str + i, 1, match, 0) == 0) {
            if (match[0].rm_so != -1 && i != 0) {
                temp[offset++] = ' ';
            }
        }
        temp[offset++] = str[i];
    }
    temp[offset] = '\0';
    strcpy(str, temp);
    regfree(&regex);
}

int main() {
    char str[MAX];
    printf("Enter a string\n");
    fgets(str, MAX, stdin);
    str[strlen(str) - 1] = '\0';
    SpaceCapitals(str);
    printf("Modified string: %s\n", str);
    return 0;
}