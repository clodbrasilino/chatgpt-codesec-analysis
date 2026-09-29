#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) return NULL;

    size_t len = strlen(input);
    char *output = malloc(len * 2 + 1);
    if (output == NULL) return NULL;

    const char *src = input;
    char *dst = output;

    while (*src != '\0') {
        if (isupper((unsigned char)*src)) {
            if (dst != output) {
                *dst++ = '_';
            }
            *dst++ = (char)tolower((unsigned char)*src);
        } else {
            *dst++ = *src;
        }
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