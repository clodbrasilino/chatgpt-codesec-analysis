#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char* str) {
    regex_t regex;
    char *p = str;
    int ret;
    regmatch_t match;

    if (regcomp(&regex, "  +", 0)) {
        printf("Could not compile regex\n");
        return;
    }

    while (!regexec(&regex, p, 1, &match, 0)) {
        memmove(p + match.rm_so + 1, p + match.rm_eo, strlen(p + match.rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char str[] = "This  is   a    test";
    printf("Before: %s\n", str);
    remove_multiple_spaces(str);
    printf("After: %s\n", str);
    return 0;
}