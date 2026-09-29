#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;
    char *ptr = str;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (1) {
        reti = regexec(&regex, ptr, 1, pmatch, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            regfree(&regex);
            return;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(ptr + pmatch[0].rm_so, ptr + pmatch[0].rm_eo, strlen(ptr + pmatch[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}