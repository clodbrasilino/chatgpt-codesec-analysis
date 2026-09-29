#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t max_uppercase_run(const char *string)
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
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        size_t required_capacity;
        char *resized_input;

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        required_capacity = length + 2;

        if (required_capacity > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required_capacity) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required_capacity;
                    break;
                }
                new_capacity *= 2;
            }

            resized_input = realloc(input, new_capacity);
            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
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

    if (printf("%zu\n", max_uppercase_run(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}