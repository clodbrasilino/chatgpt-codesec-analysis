#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_regex(const char *str, const char *pattern)
{
    regex_t regex;
    regmatch_t match[1];
    char anchored_pattern[512];
    int ret;

    if (str == NULL || pattern == NULL) {
        return -1;
    }

    if (strlen(pattern) + 2 >= sizeof(anchored_pattern)) {
        return -1;
    }

    snprintf(anchored_pattern, sizeof(anchored_pattern), "^%s", pattern);

    ret = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 1, match, 0);
    regfree(&regex);

    if (ret == 0) {
        return match[0].rm_so == 0 ? 1 : 0;
    }

    if (ret == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    const char *text;
    const char *pattern;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <pattern>\n", argv[0]);
        return EXIT_FAILURE;
    }

    text = argv[1];
    pattern = argv[2];

    result = starts_with_regex(text, pattern);

    if (result < 0) {
        fprintf(stderr, "Error: invalid regex or pattern too long\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result ? "true" : "false");
    return EXIT_SUCCESS;
}