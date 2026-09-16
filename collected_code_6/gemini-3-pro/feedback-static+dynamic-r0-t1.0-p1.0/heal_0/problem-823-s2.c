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
    size_t pattern_len = strlen(pattern);
    char *anchored_pattern = malloc(pattern_len + 2);
    
    if (anchored_pattern == NULL) {
        return 0;
    }

    snprintf(anchored_pattern, pattern_len + 2, "^%s", pattern);

    reti = regcomp(&regex, anchored_pattern, REG_EXTENDED | REG_NOSUB);
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
    const char *test_string = "hello world";
    const char *test_pattern = "hel";

    int result = starts_with_regex(test_string, test_pattern);

    if (result) {
        printf("Match found.\n");
    } else {
        printf("No match.\n");
    }

    return 0;
}