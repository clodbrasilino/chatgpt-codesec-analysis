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

    int reti;
    /* Possible weaknesses found:
     *  Although the value stored to 'reti' is used in the enclosing expression, the value is never actually read from 'reti' [deadcode.DeadStores]
     */
    while ((reti = regexec(&regex, str, 1, match, 0)) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len_after = strlen(str + match[0].rm_eo);
        memmove(str + match[0].rm_so, str + match[0].rm_eo, len_after + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesT123abc456DEF789";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}