#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with(const char *str, const char *prefix)
{
    regex_t regex;
    char *pattern;
    size_t prefix_len;
    size_t i;
    size_t j;
    int ret;
    int result;

    if (str == NULL || prefix == NULL) {
        return -1;
    }

    prefix_len = strlen(prefix);
    pattern = malloc(prefix_len * 2 + 2);
    if (pattern == NULL) {
        return -1;
    }

    j = 0;
    pattern[j++] = '^';
    for (i = 0; i < prefix_len; i++) {
        if (strchr(".^$*+?()[]{}|\\", prefix[i]) != NULL) {
            pattern[j++] = '\\';
        }
        pattern[j++] = prefix[i];
    }
    pattern[j] = '\0';

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    free(pattern);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        result = -1;
    }

    return result;
}

int main(void)
{
    const char *text = "Hello, world!";
    const char *prefix = "Hello";
    int result;

    result = starts_with(text, prefix);
    if (result < 0) {
        fprintf(stderr, "Error checking prefix\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("\"%s\" starts with \"%s\"\n", text, prefix);
    } else {
        printf("\"%s\" does not start with \"%s\"\n", text, prefix);
    }

    result = starts_with(text, "world");
    if (result < 0) {
        fprintf(stderr, "Error checking prefix\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("\"%s\" starts with \"world\"\n", text);
    } else {
        printf("\"%s\" does not start with \"world\"\n", text);
    }

    return EXIT_SUCCESS;
}