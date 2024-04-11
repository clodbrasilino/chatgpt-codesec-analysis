#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void removeLowercaseSubstrings(char *str) {
    regex_t regex;
    char *newStr = (char *)malloc(strlen(str) + 1);
    int index = 0;

    regcomp(&regex, "[a-z]+", REG_EXTENDED);

    char *p = str;
    regmatch_t match;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        int len = match.rm_so;
        strncpy(newStr + index, p, len);
        index += len;
        p += match.rm_eo;
    }

    strcpy(newStr + index, p);
    strcpy(str, newStr);

    free(newStr);
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}