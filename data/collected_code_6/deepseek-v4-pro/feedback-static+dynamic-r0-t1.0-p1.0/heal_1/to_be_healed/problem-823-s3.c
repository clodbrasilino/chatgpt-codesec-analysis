#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_regex(const char *str, const char *pattern) {
    if (str == NULL || pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char anchored_pattern[1024];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t pattern_len = strlen(pattern);

    if (pattern_len >= sizeof(anchored_pattern) - 2) {
        return 0;
    }

    anchored_pattern[0] = '^';
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(anchored_pattern + 1, pattern);
    anchored_pattern[pattern_len + 1] = '\0';

    ret = regcomp(&regex, anchored_pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return (ret == 0) ? 1 : 0;
}

int main(void) {
    const char *test_strings[] = {
        "hello world",
        "world hello",
        "hello",
        "hell",
        "hellish dream",
        "test123",
        ""
    };

    const char *patterns[] = {
        "hello",
        "^hello",
        "hel+o",
        "world",
        "^h.*o",
        "test[0-9]+",
        "."
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t num_patterns = sizeof(patterns) / sizeof(patterns[0]);

    for (size_t i = 0; i < num_tests; i++) {
        for (size_t j = 0; j < num_patterns; j++) {
            int result = starts_with_regex(test_strings[i], patterns[j]);
            printf("starts_with_regex(\"%s\", \"%s\") = %d\n",
                   test_strings[i], patterns[j], result);
        }
    }

    return 0;
}