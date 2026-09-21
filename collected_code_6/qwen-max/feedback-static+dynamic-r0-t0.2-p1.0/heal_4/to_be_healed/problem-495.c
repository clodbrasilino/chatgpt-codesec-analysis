#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (1) {
        if (regexec(&regex, str, 1, pmatch, 0) == REG_NOMATCH) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str);
        memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, len - pmatch[0].rm_eo + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}