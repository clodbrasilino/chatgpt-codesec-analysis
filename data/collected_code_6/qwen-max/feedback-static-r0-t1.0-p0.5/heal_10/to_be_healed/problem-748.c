#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_words(char *str, size_t max_size) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "([A-Z][^A-Z]*)";
    char replacement[] = " \\1";

    char *result = malloc(max_size);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    int start = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE)) {
        free(result);
        return;
    }

    while (regexec(&regex, str + start, 2, matches, 0) == 0) {
        int end = matches[0].rm_so + start;
        size_t len = end - start;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(result) + len + 1 < max_size) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            snprintf(result + strlen(result), max_size - strlen(result), "%.*s", (int)len, str + start);
        }

        size_t rep_len = sizeof(replacement) - 2;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(result) + rep_len + 1 < max_size) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            snprintf(result + strlen(result), max_size - strlen(result), "%.*s", (int)rep_len, replacement + 1);
        }

        start = matches[0].rm_eo + start;
    }

    char *remaining = str + start;
    size_t remaining_len = strnlen(remaining, max_size - (size_t)start);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t space_left = max_size - strlen(result) - 1;

    if (space_left > 0 && remaining_len < space_left) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        snprintf(result + strlen(result), max_size - strlen(result), "%.*s", (int)remaining_len, remaining);
    }

    snprintf(str, max_size, "%s", result);

    free(result);
    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024] = "HelloWorldThisIsATest";
    add_spaces_between_capital_words(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}