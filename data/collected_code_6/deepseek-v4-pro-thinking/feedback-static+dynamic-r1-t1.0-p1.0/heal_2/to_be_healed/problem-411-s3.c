#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t out = 0;
    int capitalize = 1;

    for (size_t i = 0; i < len; i++) {
        char c = snake[i];
        if (c == '_') {
            capitalize = 1;
        } else {
            if (capitalize) {
                result[out++] = (char)toupper((unsigned char)c);
                capitalize = 0;
            } else {
                result[out++] = (char)tolower((unsigned char)c);
            }
        }
    }

    result[out] = '\0';
    return result;
}

int main(int argc, char **argv) {
    const char *input = (argc > 1) ? argv[1] : "snake_case_string";
    char *camel = snake_to_camel(input);

    if (camel == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", camel);
    free(camel);
    return EXIT_SUCCESS;
}