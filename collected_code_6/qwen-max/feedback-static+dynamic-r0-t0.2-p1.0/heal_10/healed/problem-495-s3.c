#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    int offset = 0;

    while (regexec(&regex, str + offset, 1, match, 0) == 0) {
        size_t len_so = match[0].rm_so;
        size_t len_eo = match[0].rm_eo;
        memmove(str + offset + len_so, str + offset + len_eo, strlen(str + offset + len_eo) + 1);
        offset += len_so;
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesT123abc456DEF789";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}