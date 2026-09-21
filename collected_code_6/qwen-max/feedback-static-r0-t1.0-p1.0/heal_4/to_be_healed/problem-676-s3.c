#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_non_alphanumeric(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;
    /* Possible weaknesses found:
     *  Variable 'offset' is assigned a value that is never used. [unreadVariable]
     */
    int offset = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(p + match[0].rm_eo);
        memmove(p + match[0].rm_so, p + match[0].rm_eo, len + 1);
        /* Possible weaknesses found:
         *  Variable 'offset' is assigned a value that is never used. [unreadVariable]
         */
        offset += match[0].rm_eo - match[0].rm_so;
        p = str; // reset p to the start of the string after each removal
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello! This is a test. @123";
    remove_non_alphanumeric(str);
    printf("%s\n", str);
    return 0;
}