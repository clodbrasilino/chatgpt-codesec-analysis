#include <stdio.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t matches[1];
    char pattern[] = "[a-z]+";
    int matchlen;

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, str, 1, matches, 0) == 0) {
        matchlen = matches[0].rm_eo - matches[0].rm_so;
        memmove(str + matches[0].rm_so, str + matches[0].rm_eo, strlen(str + matches[0].rm_eo) + 1);
        memset(str + strlen(str) - matchlen, 0, matchlen); 
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesTStrinG123";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}