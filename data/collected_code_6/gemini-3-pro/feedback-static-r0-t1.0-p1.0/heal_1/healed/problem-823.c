#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static size_t get_safe_length(const char *str, size_t max_len) {
    size_t len = 0;
    if (!str) return 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int startsWithRegex(const char *string, const char *pattern) {
    if (string == NULL || pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    char *anchoredPattern;
    
    size_t max_pattern_len = 8192;
    size_t len = get_safe_length(pattern, max_pattern_len);
    
    if (len == max_pattern_len) {
        return 0;
    }

    anchoredPattern = (char *)malloc(len + 2);
    if (anchoredPattern == NULL) {
        return 0;
    }

    snprintf(anchoredPattern, len + 2, "^%s", pattern);

    ret = regcomp(&regex, anchoredPattern, REG_EXTENDED);
    free(anchoredPattern);
    
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *str1 = "Hello, world!";
    const char *pattern1 = "Hell";
    const char *pattern2 = "world";

    int result1 = startsWithRegex(str1, pattern1);
    int result2 = startsWithRegex(str1, pattern2);

    printf("'%s' starts with '%s': %s\n", str1, pattern1, result1 ? "true" : "false");
    printf("'%s' starts with '%s': %s\n", str1, pattern2, result2 ? "true" : "false");

    return 0;
}