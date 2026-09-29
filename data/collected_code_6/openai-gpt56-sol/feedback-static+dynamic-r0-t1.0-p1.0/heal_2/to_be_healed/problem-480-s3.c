#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *data,
                                 size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    unsigned int max_character = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    for (unsigned int i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            max_character = i;
        }
    }

    *result = (unsigned char)max_character;
    return 1;
}

int main(void)
{
    size_t capacity = 256;
    size_t length = 0;
    unsigned char *input = malloc(capacity);
    unsigned char result;
    int ch;

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            unsigned char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        free(input);
        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%c\n", result) < 0) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}