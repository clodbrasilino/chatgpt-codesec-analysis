#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_regex(const char *str, const char *pattern) {
    regex_t regex;
    int ret;
    char *anchored_pattern;
    size_t pattern_len;
    int result = 0;

    if (str == NULL || pattern == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_len = strlen(pattern);
    anchored_pattern = malloc(pattern_len + 2);
    if (anchored_pattern == NULL) {
        return 0;
    }

    anchored_pattern[0] = '^';
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(anchored_pattern + 1, pattern);

    ret = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);

    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret != REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "hello world";
    const char *pattern = "hello";

    if (starts_with_regex(test_string, pattern)) {
        printf("String starts with the pattern.\n");
    } else {
        printf("String does not start with the pattern.\n");
    }

    return 0;
}