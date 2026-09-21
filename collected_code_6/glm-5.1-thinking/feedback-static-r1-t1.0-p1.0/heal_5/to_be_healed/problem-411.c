#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str, size_t str_len) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strnlen(snake_str, str_len);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t camel_idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_' && i + 1 < len && islower((unsigned char)snake_str[i + 1])) {
            camel_str[camel_idx++] = toupper((unsigned char)snake_str[++i]);
        } else {
            camel_str[camel_idx++] = snake_str[i];
        }
    }

    camel_str[camel_idx] = '\0';
    return camel_str;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        const char *test = "hello_world_example";
        char *result = snake_to_camel(test, sizeof("hello_world_example"));
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char *result = snake_to_camel(argv[i], strlen(argv[i]) + 1);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    return 0;
}