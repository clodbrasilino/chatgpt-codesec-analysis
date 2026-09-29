#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return;
    }

    while (1) {
        int reti = regexec(&regex, str, 1, match, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            regfree(&regex);
            return;
        }

        /* Possible weaknesses found:
         *  Value stored to 'len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        size_t len = match[0].rm_eo - match[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + match[0].rm_so, str + match[0].rm_eo, strlen(str + match[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "HeLlO WoRlD";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}