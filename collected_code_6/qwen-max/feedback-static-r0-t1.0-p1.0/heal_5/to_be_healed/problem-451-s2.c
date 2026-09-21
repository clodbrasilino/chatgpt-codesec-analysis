#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces(char *str) {
    regex_t re;
    regmatch_t pmatch[2];
    char pattern[] = "\\s";

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NEWLINE) == 0) {
        /* Possible weaknesses found:
         *  The scope of the variable 'len' can be reduced. [variableScope]
         */
        size_t len;
        while (1) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            len = strlen(str);
            if (regexec(&re, str, 2, pmatch, 0) != 0) break;
            /* Possible weaknesses found:
             *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'match_len' during its initialization is never read [deadcode.DeadStores]
             */
            size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, len - pmatch[0].rm_eo + 1);
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