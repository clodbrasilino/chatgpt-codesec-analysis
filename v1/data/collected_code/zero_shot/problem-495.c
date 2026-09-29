#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void removeLowercaseSubstrings(char* str) {
    regex_t regex;
    regcomp(&regex, "[a-z]+", REG_EXTENDED);

    size_t currIdx = 0;
    regmatch_t match;
    while (regexec(&regex, str + currIdx, 1, &match, 0) == 0) {
        int len = match.rm_eo - match.rm_so;
        for (int i = currIdx + match.rm_so; i < currIdx + match.rm_eo; i++) {
            str[i] = ' ';
        }
        currIdx += match.rm_eo;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello World! This is a test string.";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);

    return 0;
}