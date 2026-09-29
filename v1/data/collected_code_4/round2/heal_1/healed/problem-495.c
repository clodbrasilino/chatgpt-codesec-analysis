#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdio.h>

char *removeLowercase(char *str) {
    regex_t regex;
    regmatch_t matches[2];
    char *newStr = NULL;
    char *pattern = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return NULL;
    }
    
    newStr = (char*) malloc(strlen(str)+1);
    if (!newStr) {
        regfree(&regex);
        return NULL;
    }
    strcpy(newStr, str);

    while(!regexec(&regex, newStr, 2, matches, 0)) {
        memcpy(newStr+matches[0].rm_so,
               newStr+matches[0].rm_eo,
               strlen(newStr) - matches[0].rm_eo + 1);
    }

    regfree(&regex);
    return newStr;
}

int main() {
    char input[] = "HeLlO WoRlD!";
    char *output = removeLowercase(input);
  
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}