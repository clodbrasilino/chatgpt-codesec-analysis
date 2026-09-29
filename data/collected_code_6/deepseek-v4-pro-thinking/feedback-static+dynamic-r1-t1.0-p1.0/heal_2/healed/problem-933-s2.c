#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) return NULL;

    size_t capacity = 64;
    size_t out_len = 0;
    char *out = malloc(capacity);
    if (out == NULL) return NULL;

    const size_t max_input_len = 1048576;
    size_t i = 0;
    while (str[i] != '\0') {
        if (i >= max_input_len) {
            free(out);
            return NULL;
        }
        unsigned char c = (unsigned char)str[i];
        int add_underscore = 0;
        if (isupper(c)) {
            if (i > 0) {
                unsigned char prev = (unsigned char)str[i - 1];
                if ((prev >= 'a' && prev <= 'z') || (prev >= '0' && prev <= '9')) {
                    add_underscore = 1;
                } else if (prev >= 'A' && prev <= 'Z') {
                    unsigned char next = (unsigned char)str[i + 1];
                    if (next >= 'a' && next <= 'z') {
                        add_underscore = 1;
                    }
                }
            }
        }

        size_t needed = out_len + 1 + (add_underscore ? 1 : 0);
        if (needed > capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity < needed) new_capacity = needed;
            char *new_out = realloc(out, new_capacity);
            if (new_out == NULL) {
                free(out);
                return NULL;
            }
            out = new_out;
            capacity = new_capacity;
        }

        if (add_underscore) {
            out[out_len++] = '_';
        }
        out[out_len++] = isupper(c) ? (char)tolower(c) : (char)c;
        i++;
    }

    if (out_len + 1 > capacity) {
        char *new_out = realloc(out, out_len + 1);
        if (new_out == NULL) {
            free(out);
            return NULL;
        }
        out = new_out;
    }
    out[out_len] = '\0';
    return out;
}

int main(void) {
    const char *tests[] = {
        "camelCaseString",
        "HTTPServer",
        "getHTTPResponse",
        "fooBARBaz",
        "CamelCase",
        "hello",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; ++i) {
        char *result = camel_to_snake(tests[i]);
        if (result != NULL) {
            printf("%s -> %s\n", tests[i], result);
            free(result);
        } else {
            printf("%s -> (null)\n", tests[i]);
        }
    }

    return 0;
}