#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SAFE_STRING_LENGTH 1048576

static size_t safe_strlen(const char *str, size_t max)
{
    size_t i = 0;
    while (i < max && str[i] != '\0') {
        i++;
    }
    return i;
}

char *snake_to_camel(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(str, MAX_SAFE_STRING_LENGTH);
    if (len == MAX_SAFE_STRING_LENGTH) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t out = 0;
    int capitalize_next = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];

        if (c == '_') {
            if (out > 0) {
                capitalize_next = 1;
            }
        } else {
            if (capitalize_next) {
                result[out++] = (char)toupper(c);
                capitalize_next = 0;
            } else {
                result[out++] = (char)tolower(c);
            }
        }
    }

    result[out] = '\0';
    return result;
}

int main(void)
{
    const char *tests[] = {
        "snake_case_string",
        "hello_world",
        "this_is_a_longer_snake_case_example",
        "",
        "foo__bar",
        "_leading_underscore",
        "trailing_underscore_",
        "mixed_CASE_string",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        char *camel = snake_to_camel(tests[i]);

        if (camel == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        printf("%s -> %s\n", tests[i], camel);
        free(camel);
    }

    return EXIT_SUCCESS;
}