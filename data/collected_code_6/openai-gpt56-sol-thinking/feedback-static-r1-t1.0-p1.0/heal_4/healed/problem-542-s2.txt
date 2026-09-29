#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_with_colons(const char *string, char **output)
{
    char *copy;
    size_t capacity = 16;
    size_t length = 0;

    if (output == NULL) {
        return EINVAL;
    }

    *output = NULL;

    if (string == NULL) {
        return EINVAL;
    }

    copy = malloc(capacity);
    if (copy == NULL) {
        return ENOMEM;
    }

    while (string[length] != '\0') {
        char character = string[length];

        if (length == capacity - 1) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(copy);
                return ENOMEM;
            }

            new_capacity = capacity * 2;
            resized = realloc(copy, new_capacity);
            if (resized == NULL) {
                free(copy);
                return ENOMEM;
            }

            copy = resized;
            capacity = new_capacity;
        }

        copy[length] =
            character == ' ' || character == ',' || character == '.'
                ? ':'
                : character;

        ++length;
    }

    copy[length] = '\0';
    *output = copy;

    return 0;
}

int main(int argc, char **argv)
{
    char *result_string = NULL;
    int result;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    result = replace_with_colons(argv[1], &result_string);
    if (result != 0) {
        if (fprintf(stderr, "Replacement failed: %s\n", strerror(result)) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(result_string) == EOF) {
        free(result_string);
        return EXIT_FAILURE;
    }

    free(result_string);
    return EXIT_SUCCESS;
}