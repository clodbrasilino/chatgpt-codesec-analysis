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
    size_t input_length;
    size_t count = 0;
    size_t output_length;
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
        count++;
        cursor = match + target_length;
    }

    if (count > input_length / (target_length - replacement_length)) {
        return NULL;
    }

    output_length =
        input_length - count * (target_length - replacement_length);

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

        if (prefix_length > output_length -
                                (size_t)(destination - output)) {
            free(output);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, cursor, prefix_length);
        destination += prefix_length;

        if (replacement_length >
            output_length - (size_t)(destination - output)) {
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
        size_t remaining_length = input_length - (size_t)(cursor - input);
        size_t used_length = (size_t)(destination - output);

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

    *destination = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 128;
    size_t length = 0;
    char *result;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            fprintf(stderr, "Input is too large.\n");
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
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

        input[length++] = (char)ch;
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