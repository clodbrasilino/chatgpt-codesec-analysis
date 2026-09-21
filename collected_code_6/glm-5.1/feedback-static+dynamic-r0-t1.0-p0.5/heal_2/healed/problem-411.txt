#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t write_idx = 0;
    int capitalize_next = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[write_idx++] = snake_str[i] >= 'a' && snake_str[i] <= 'z' ? snake_str[i] - 32 : snake_str[i];
                capitalize_next = 0;
            } else {
                camel_str[write_idx++] = snake_str[i];
            }
        }
    }

    camel_str[write_idx] = '\0';

    char *final_str = realloc(camel_str, write_idx + 1);
    if (final_str == NULL) {
        free(camel_str);
        return NULL;
    }

    return final_str;
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