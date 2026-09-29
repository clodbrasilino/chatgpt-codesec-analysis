#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(const char *string)
{
    size_t current_run = 0;
    size_t maximum_run = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isupper((unsigned char)*string)) {
            ++current_run;
            if (current_run > maximum_run) {
                maximum_run = current_run;
            }
        } else {
            current_run = 0;
        }
        ++string;
    }

    return maximum_run;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character = EOF;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    size_t result = max_uppercase_run(input);

    if (printf("%zu\n", result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}