#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_matching_positions(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') {
            character = (unsigned char)(character - (unsigned char)'A' +
                                        (unsigned char)'a');
        }

        if (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z' &&
            i == (size_t)(character - (unsigned char)'a')) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return EXIT_FAILURE;
        }
    }

    string[length] = '\0';

    size_t result = count_matching_positions(string);
    free(string);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}