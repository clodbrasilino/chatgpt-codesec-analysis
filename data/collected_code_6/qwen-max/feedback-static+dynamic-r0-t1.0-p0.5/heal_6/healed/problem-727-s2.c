#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_non_alnum(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int rc;
    char *ptr = str;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED)) {
        return;
    }

    while ((rc = regexec(&regex, ptr, 1, pmatch, 0)) == 0 && pmatch[0].rm_so != -1) {
        size_t len = strlen(ptr + pmatch[0].rm_eo);
        memmove(ptr + pmatch[0].rm_so, ptr + pmatch[0].rm_eo, len + 1);
        ptr += pmatch[0].rm_eo - pmatch[0].rm_so;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    remove_non_alnum(input);
    printf("%s\n", input);
    return 0;
}