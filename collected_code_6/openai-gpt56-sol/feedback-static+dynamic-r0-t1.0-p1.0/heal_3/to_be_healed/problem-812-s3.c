#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate_road(const char *input)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_length = sizeof(target) - 1;
    const size_t replacement_length = sizeof(replacement) - 1;
    const size_t reduction = target_length - replacement_length;
    size_t input_length;
    size_t output_length;
    size_t count = 0;
    const char *cursor;
    const char *match;
    char *output;
    char *destination;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    cursor = input;

    while ((match = strstr(cursor, target)) != NULL) {
        ++count;
        cursor = match + target_length;
    }

    if (count > input_length / reduction) {
        return NULL;
    }

    output_length = input_length - count * reduction;

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    cursor = input;
    destination = output;

    while ((match = strstr(cursor, target)) != NULL) {
        size_t prefix_length = (size_t)(match - cursor);
        size_t used_length = (size_t)(destination - output);

        if (used_length > output_length ||
            prefix_length > output_length - used_length) {
            free(output);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, cursor, prefix_length);
        destination += prefix_length;
        used_length += prefix_length;

        if (replacement_length > output_length - used_length) {
            free(output);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, replacement, replacement_length);
        destination += replacement_length;
        cursor = match + target_length;
    }

    {
        size_t consumed_length = (size_t)(cursor - input);
        size_t used_length = (size_t)(destination - output);
        size_t remaining_length;

        if (consumed_length > input_length || used_length > output_length) {
            free(output);
            return NULL;
        }

        remaining_length = input_length - consumed_length;

        if (remaining_length > output_length - used_length) {
            free(output);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, cursor, remaining_length);
        destination += remaining_length;
    }

    if ((size_t)(destination - output) != output_length) {
        free(output);
        return NULL;
    }

    output[output_length] = '\0';
    return output;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input;
    char *result;
    int ch = EOF;

    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(input);
            fprintf(stderr, "Input is too large.\n");
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate input buffer.\n");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    result = abbreviate_road(input);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to abbreviate input.\n");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}