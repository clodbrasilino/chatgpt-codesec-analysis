#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len;

    len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static int needs_separator(const char *s, size_t i, size_t len)
{
    if (i == 0) {
        return 0;
    }
    if (islower((unsigned char)s[i - 1]) || isdigit((unsigned char)s[i - 1])) {
        return 1;
    }
    if (isupper((unsigned char)s[i - 1]) && i + 1 < len &&
        islower((unsigned char)s[i + 1])) {
        return 1;
    }
    return 0;
}

char *camel_to_snake(const char *src)
{
    size_t len;
    size_t extra;
    size_t i;
    size_t j;
    char *result;

    if (src == NULL) {
        return NULL;
    }

    len = bounded_strlen(src, MAX_INPUT_LENGTH + 1);
    if (len > MAX_INPUT_LENGTH) {
        return NULL;
    }

    extra = 0;
    for (i = 0; i < len; i++) {
        if (isupper((unsigned char)src[i]) && needs_separator(src, i, len)) {
            extra++;
        }
    }

    if (len > SIZE_MAX - extra - 1) {
        return NULL;
    }

    result = (char *)malloc(len + extra + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (isupper((unsigned char)src[i])) {
            if (needs_separator(src, i, len)) {
                result[j] = '_';
                j++;
            }
            result[j] = (char)tolower((unsigned char)src[i]);
            j++;
        } else {
            result[j] = src[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "helloWorld",
        "ThisIsATest",
        "XMLHttpRequest",
        "already_snake",
        "simple",
        "a",
        ""
    };
    const size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *snake = camel_to_snake(tests[i]);
        if (snake == NULL) {
            fprintf(stderr, "conversion failed for input %zu\n", i);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], snake);
        free(snake);
    }

    return EXIT_SUCCESS;
}