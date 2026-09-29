#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_substrings(const char *str, size_t *result)
{
    size_t frequencies[256] = {0};
    size_t length;
    size_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        if (total > SIZE_MAX - frequencies[character] - 1U) {
            return -1;
        }

        total += frequencies[character] + 1U;
        ++frequencies[character];
    }

    *result = total;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t count;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (count_substrings(input, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}