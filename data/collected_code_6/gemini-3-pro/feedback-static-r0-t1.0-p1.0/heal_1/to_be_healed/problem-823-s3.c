#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_regex(const char *string, const char *pattern) {
    if (string == NULL || pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t pattern_len = strlen(pattern);
    char *anchored_pattern = malloc(pattern_len + 2);
    
    if (anchored_pattern == NULL) {
        return 0;
    }

    anchored_pattern[0] = '^';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(anchored_pattern + 1, pattern, pattern_len);
    anchored_pattern[pattern_len + 1] = '\0';

    reti = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);

    if (reti) {
        return 0;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *target_string = "Hello, World!";
    const char *substring = "Hello";

    int result = starts_with_regex(target_string, substring);

    if (result) {
        printf("The string starts with the substring.\n");
    } else {
        printf("The string does not start with the substring.\n");
    }

    return 0;
}