#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void split_string_at_uppercase(const char *input, size_t len) {
    regex_t regex;
    regmatch_t matches[2];
    int match_count;

    if (regcomp(&regex, "([A-Z])", REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(EXIT_FAILURE);
    }

    const char *p = input;
    /* Possible weaknesses found:
     *  Although the value stored to 'match_count' is used in the enclosing expression, the value is never actually read from 'match_count' [deadcode.DeadStores]
     */
    while ((match_count = regexec(&regex, p, 2, matches, 0)) == 0) {
        if (matches[0].rm_so > 0) {
            printf("%.*s\n", (int)(matches[0].rm_so), p);
        }
        p += matches[0].rm_eo;
    }

    if (p - input < len) {
        size_t remaining_length = len - (p - input);
        printf("%.*s\n", (int)remaining_length, p);
    }

    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    split_string_at_uppercase(input, strlen(input));
    return 0;
}