#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_non_repeated_character(const char *str, unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    const unsigned char *current;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (current = (const unsigned char *)str; *current != '\0'; ++current) {
        ++frequencies[*current];
    }

    for (current = (const unsigned char *)str; *current != '\0'; ++current) {
        if (frequencies[*current] == 1) {
            *result = *current;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    unsigned char result;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            fprintf(stderr, "Input is too long.\n");
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fprintf(stderr, "Input is too long.\n");
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        fprintf(stderr, "No input provided.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    if (first_non_repeated_character(input, &result)) {
        printf("%c\n", (int)result);
    } else {
        puts("No non-repeated character found.");
    }

    free(input);
    return EXIT_SUCCESS;
}