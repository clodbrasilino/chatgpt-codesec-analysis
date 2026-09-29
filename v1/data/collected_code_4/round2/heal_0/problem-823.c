#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

int starts_with_substring(const char* string, const char* substring) {
    regex_t regex;
    int ret;
    char pattern[4096];
   
    snprintf(pattern, sizeof(pattern), "^%s", substring);
    ret = regcomp(&regex, pattern, 0);

    if (ret) {
        regfree(&regex);
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main() {
    const char* string = "Hello, world!";
    const char* substring = "Hello";

    if (starts_with_substring(string, substring)) {
        printf("The string starts with the substring.\n");
    } else {
        printf("The string does not start with the substring.\n");
    }

    return 0;
}