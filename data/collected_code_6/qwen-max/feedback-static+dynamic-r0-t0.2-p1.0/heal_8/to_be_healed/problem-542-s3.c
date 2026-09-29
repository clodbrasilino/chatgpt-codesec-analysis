#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *new_str = malloc(str_len + 1);
    if (new_str == NULL) return;
    new_str[str_len] = '\0';

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        free(new_str);
        return;
    }

    size_t i = 0, j = 0;
    while (regexec(&regex, str + i, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so + i;
        size_t match_end = pmatch[0].rm_eo + i;
        size_t copy_len = match_start - i;
        if (j + copy_len <= str_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(new_str + j, str + i, copy_len);
            j += copy_len;
        }
        if (j < str_len) {
            new_str[j++] = ':';
        }
        i = match_end;
    }
    size_t remaining = str_len - i;
    if (j + remaining <= str_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str + j, str + i, remaining);
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, str_len + 1);
    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}