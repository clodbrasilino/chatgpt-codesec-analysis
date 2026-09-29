#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void clean_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;
    int len, offset = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        len = match[0].rm_eo - match[0].rm_so;
        memmove(p + offset, p + len, strlen(p + len) + 1);
        p += len;
        offset -= len;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello! This is a test. 12345";
    clean_string(input);
    printf("%s\n", input);
    return 0;
}