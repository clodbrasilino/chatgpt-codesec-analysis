#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "[a-z]+";
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    while ((reti = regexec(&regex, str, 1, match, 0)) == 0) {
        memmove(str + match[0].rm_so, str + match[0].rm_eo, strlen(str + match[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesT123abc456DEF789";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}