#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces(char *str) {
    regex_t re;
    regmatch_t pmatch[1];
    char pattern[] = "\\s";

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NEWLINE) == 0) {
        while (regexec(&re, str, 1, pmatch, 0) == 0) {
            /* Possible weaknesses found:
             *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'match_len' during its initialization is never read [deadcode.DeadStores]
             */
            size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, strlen(str + pmatch[0].rm_eo) + 1);
        }
        regfree(&re);
    }
}

int main() {
    char input[] = "  Hello   World  ";
    remove_whitespaces(input);
    printf("%s\n", input);
    return 0;
}