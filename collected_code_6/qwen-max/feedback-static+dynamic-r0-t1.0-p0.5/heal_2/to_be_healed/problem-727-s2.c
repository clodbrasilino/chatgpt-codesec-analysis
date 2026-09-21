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

    /* Possible weaknesses found:
     *  Although the value stored to 'rc' is used in the enclosing expression, the value is never actually read from 'rc' [deadcode.DeadStores]
     */
    while ((rc = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(ptr + pmatch[0].rm_so, ptr + pmatch[0].rm_eo, strlen(ptr + pmatch[0].rm_eo) + 1);
        ptr += pmatch[0].rm_so;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    remove_non_alnum(input);
    printf("%s\n", input);
    return 0;
}