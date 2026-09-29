#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_non_alphanumeric(char *str) {
    regex_t regex;
    regmatch_t match[1];
    int offset = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, str + offset, 1, match, 0) == 0) {
        size_t so = match[0].rm_so;
        size_t eo = match[0].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + offset + so, str + offset + eo, strlen(str + offset + eo) + 1);
        offset += eo - so;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello! This is a test. @123";
    remove_non_alphanumeric(str);
    printf("%s\n", str);
    return 0;
}