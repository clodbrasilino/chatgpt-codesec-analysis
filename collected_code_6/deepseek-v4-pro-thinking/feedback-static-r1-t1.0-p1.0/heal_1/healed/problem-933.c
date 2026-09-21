#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    size_t upper_count = 0;
    const char *p = input;
    while (*p != '\0') {
        if (isupper((unsigned char)*p)) {
            upper_count++;
        }
        len++;
        p++;
    }

    size_t out_size = len + upper_count + 1;
    char *output = malloc(out_size);
    if (output == NULL) {
        return NULL;
    }

    const char *src = input;
    char *dst = output;
    int first = 1;

    while (*src != '\0') {
        unsigned char c = *src;
        if (isupper(c)) {
            if (!first) {
                *dst++ = '_';
            }
            *dst++ = (char)tolower(c);
        } else {
            *dst++ = c;
        }
        first = 0;
        src++;
    }
    *dst = '\0';

    return output;
}

int main(void) {
    const char *input = "camelCaseString";
    char *result = camel_to_snake(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}