#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }

    char *out = malloc(len * 2 + 1);
    if (out == NULL) {
        return NULL;
    }

    if (len == 0) {
        out[0] = '\0';
        return out;
    }

    size_t out_pos = 0;
    size_t max_out = len * 2;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c)) {
            unsigned char prev = i > 0 ? (unsigned char)str[i - 1] : 0;
            unsigned char next = (i + 1 < len) ? (unsigned char)str[i + 1] : 0;
            int insert_underscore = 0;
            if ((prev >= 'a' && prev <= 'z') || (prev >= '0' && prev <= '9')) {
                insert_underscore = 1;
            } else if (isupper(prev) && (next >= 'a' && next <= 'z')) {
                insert_underscore = 1;
            }
            if (insert_underscore) {
                if (out_pos >= max_out) {
                    free(out);
                    return NULL;
                }
                out[out_pos++] = '_';
            }
            if (out_pos >= max_out) {
                free(out);
                return NULL;
            }
            out[out_pos++] = (char)tolower(c);
        } else {
            if (out_pos >= max_out) {
                free(out);
                return NULL;
            }
            out[out_pos++] = str[i];
        }
    }
    out[out_pos] = '\0';
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