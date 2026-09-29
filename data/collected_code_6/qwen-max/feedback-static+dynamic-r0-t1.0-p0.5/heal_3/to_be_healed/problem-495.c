#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    int rc;
    /* Possible weaknesses found:
     *  Although the value stored to 'rc' is used in the enclosing expression, the value is never actually read from 'rc' [deadcode.DeadStores]
     */
    while ((rc = regexec(&regex, str, 1, pmatch, 0)) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + start, str + end, strlen(str + end) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs.";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}