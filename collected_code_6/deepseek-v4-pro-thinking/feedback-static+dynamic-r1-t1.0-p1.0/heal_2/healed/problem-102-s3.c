#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static const size_t MAX_SAFE_LEN = 1024;

char *snake_to_camel(const char *str) {
    size_t len;
    char *out;
    size_t write;
    int capitalize_next;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    len = 0;
    while (len < MAX_SAFE_LEN && str[len] != '\0') {
        len++;
    }
    if (len == MAX_SAFE_LEN) {
        return NULL;
    }

    out = malloc(len + 1);
    if (out == NULL) {
        return NULL;
    }

    write = 0;
    capitalize_next = 0;

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];

        if (c == '_') {
            if (write > 0) {
                capitalize_next = 1;
            }
        } else if (write == 0) {
            out[write++] = (char)toupper(c);
        } else if (capitalize_next) {
            out[write++] = (char)toupper(c);
            capitalize_next = 0;
        } else {
            out[write++] = str[i];
        }
    }

    out[write] = '\0';
    return out;
}

int main(void) {
    const char *tests[] = {
        "hello_world",
        "this_is_snake_case",
        "_leading_underscore",
        "python_language",
        "programming_language",
        "python_program"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t t;

    for (t = 0; t < num_tests; t++) {
        char *result = snake_to_camel(tests[t]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    return 0;
}