#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_substring(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return 0;
    }

    size_t sub_len = strlen(sub);
    if (sub_len == 0) {
        return 1;
    }

    size_t pattern_len = sub_len + 4;
    char *pattern = (char *)malloc(pattern_len);
    if (pattern == NULL) {
        return 0;
    }

    snprintf(pattern, pattern_len, "^%s", sub);

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);
    pattern = NULL;

    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0 ? 1 : 0;
}

int main(void) {
    const char *text = "Hello, world!";
    const char *sub = "Hello";
    const char *fail_sub = "World";
    const char *null_str = NULL;

    printf("%d\n", starts_with_substring(text, sub));
    printf("%d\n", starts_with_substring(text, fail_sub));
    printf("%d\n", starts_with_substring(text, null_str));
    printf("%d\n", starts_with_substring(null_str, sub));

    return 0;
}