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

    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;
    while (1) {
        reti = regexec(&regex, str, 1, match, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            regfree(&regex);
            return;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str);
        for (int i = match[0].rm_eo; i <= len; i++) {
            str[i - (match[0].rm_eo - match[0].rm_so)] = str[i];
        }
        str[len - (match[0].rm_eo - match[0].rm_so)] = '\0';
    }

    regfree(&regex);
}

int main() {
    char input[] = "HeLlO WoRlD";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}