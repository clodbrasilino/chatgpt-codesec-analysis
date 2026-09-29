#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *p = str, *end = str + strlen(str);

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (p < end) {
        if (regexec(&regex, p, 1, match, 0) == 0) {
            memmove(p + match[0].rm_so, p + match[0].rm_eo, end - (p + match[0].rm_eo) + 1);
            end -= (match[0].rm_eo - match[0].rm_so);
        } else {
            p++;
        }
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_string(input);
    printf("%s\n", input);
    return 0;
}