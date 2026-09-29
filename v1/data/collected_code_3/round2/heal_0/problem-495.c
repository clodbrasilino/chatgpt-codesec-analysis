#include <stdio.h>
#include <string.h>
#include <regex.h>

void removeLowercaseSubstrings(char *str) {
    regex_t regex;
    regcomp(&regex, "[a-z]+", REG_EXTENDED);
    regmatch_t matches[1];
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        int pos = matches[0].rm_so;
        int len = matches[0].rm_eo - matches[0].rm_so;
        memmove(&str[pos], &str[pos + len], strlen(str) - len - pos + 1);
    }
    regfree(&regex);
}

int main() {
    char str[] = "HelloWORLD123abcXYZ";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}