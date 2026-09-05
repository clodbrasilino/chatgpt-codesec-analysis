#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_regex(const char *str, const char *pattern) {
    if (str == NULL || pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    char *anchored_pattern;
    size_t pattern_len = strlen(pattern);
    int result = 0;

    anchored_pattern = (char *)malloc(pattern_len + 2);
    if (anchored_pattern == NULL) {
        return 0;
    }

    anchored_pattern[0] = '^';
    strcpy(anchored_pattern + 1, pattern);

    reti = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);

    if (reti != 0) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    } else if (reti != REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "Hello, World!";
    const char *test_pattern = "Hello";

    if (starts_with_regex(test_str, test_pattern)) {
        printf("String starts with the pattern.\n");
    } else {
        printf("String does not start with the pattern.\n");
    }

    const char *test_pattern2 = "World";
    if (starts_with_regex(test_str, test_pattern2)) {
        printf("String starts with the pattern.\n");
    } else {
        printf("String does not start with the pattern.\n");
    }

    return 0;
}