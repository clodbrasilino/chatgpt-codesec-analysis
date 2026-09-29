#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t max_limit = 8192;
    size_t src_len = 0;
    size_t dst_len = 0;

    while (src_len < max_limit && camel_case[src_len] != '\0') {
        if (isupper((unsigned char)camel_case[src_len])) {
            if (src_len > 0) {
                dst_len += 2;
            } else {
                dst_len += 1;
            }
        } else {
            dst_len += 1;
        }
        src_len++;
    }

    if (src_len == max_limit) {
        return NULL;
    }

    char *snake_case = malloc(dst_len + 1);
    
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0) {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = camel_case[i];
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(void) {
    const char *inputs[] = {
        "camelCase",
        "CamelCaseString",
        "already_snake",
        "simple",
        "",
        NULL
    };

    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < num_inputs; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else if (inputs[i] == NULL) {
            printf("NULL\n");
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}