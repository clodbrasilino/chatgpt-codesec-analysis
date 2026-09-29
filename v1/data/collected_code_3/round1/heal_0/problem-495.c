#include <stdio.h>
#include <string.h>
#include <regex.h>

void removeLowercaseSubstrings(char *str) {
    regex_t regex;
    regcomp(&regex, "[a-z]+", 0);
    regmatch_t match;

    while (regexec(&regex, str, 1, &match, 0) == 0) {
        int length = strlen(str);
        memmove(&str[match.rm_so], &str[match.rm_eo], length - match.rm_eo + 1);
    }

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}