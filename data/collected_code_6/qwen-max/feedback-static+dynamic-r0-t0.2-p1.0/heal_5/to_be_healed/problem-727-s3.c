#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void clean_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str, *src, *dst;
    /* Possible weaknesses found:
     *  Variable 'offset' is assigned a value that is never used. [unreadVariable]
     */
    int offset = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        int len = match[0].rm_eo - match[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        for (src = p + len, dst = p; src < p + strlen(p); src++, dst++) {
            *dst = *src;
        }
        *dst = '\0';
        p += len;
        /* Possible weaknesses found:
         *  Variable 'offset' is assigned a value that is never used. [unreadVariable]
         */
        offset -= len;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello! This is a test. 12345";
    clean_string(input);
    printf("%s\n", input);
    return 0;
}