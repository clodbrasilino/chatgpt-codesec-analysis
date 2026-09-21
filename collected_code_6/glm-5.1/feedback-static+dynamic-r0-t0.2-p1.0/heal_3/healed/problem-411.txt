#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    size_t out_len = len + 1;
    char *camel_str = malloc(out_len);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    size_t in_idx = 0;
    int capitalize_next = 0;

    while (snake_str[in_idx] != '\0') {
        if (snake_str[in_idx] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[out_idx++] = toupper((unsigned char)snake_str[in_idx]);
                capitalize_next = 0;
            } else {
                camel_str[out_idx++] = snake_str[in_idx];
            }
        }
        in_idx++;
    }

    camel_str[out_idx] = '\0';

    if (out_idx < out_len) {
        char *shrunk = realloc(camel_str, out_idx + 1);
        if (shrunk != NULL) {
            camel_str = shrunk;
        }
    }

    return camel_str;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
        return 1;
    }

    char *result = snake_to_camel(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);
    return 0;
}