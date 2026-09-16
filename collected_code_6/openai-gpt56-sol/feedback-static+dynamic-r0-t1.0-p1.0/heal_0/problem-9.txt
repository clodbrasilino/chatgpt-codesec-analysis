#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t minimum_rotations(const char *str)
{
    size_t length;
    size_t *prefix;
    size_t i;
    size_t matched;
    size_t period;

    if (str == NULL) {
        return 0;
    }

    length = strlen(str);
    if (length == 0) {
        return 0;
    }

    prefix = calloc(length, sizeof(*prefix));
    if (prefix == NULL) {
        return 0;
    }

    for (i = 1, matched = 0; i < length; ++i) {
        while (matched > 0 && str[i] != str[matched]) {
            matched = prefix[matched - 1];
        }

        if (str[i] == str[matched]) {
            ++matched;
        }

        prefix[i] = matched;
    }

    period = length - prefix[length - 1];
    if (length % period != 0) {
        period = length;
    }

    free(prefix);
    return period;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    printf("%zu\n", minimum_rotations(input));

    free(input);
    return EXIT_SUCCESS;
}