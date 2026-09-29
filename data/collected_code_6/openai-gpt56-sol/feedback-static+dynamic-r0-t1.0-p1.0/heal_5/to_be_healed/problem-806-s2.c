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
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity;
            char *temporary;

            if (new_capacity == 0) {
                new_capacity = 128;
            }

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (capacity <= length) {
        char *temporary;

        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        temporary = realloc(input, length + 1);
        if (temporary == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = temporary;
    }

    input[length] = '\0';

    if (printf("%zu\n", max_uppercase_run(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}