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
    size_t reduction;
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
        if (count == SIZE_MAX) {
            return NULL;
        }
        ++count;
        cursor = match + target_length;
    }

    if (count > input_length / (target_length - replacement_length)) {
        return NULL;
    }

    reduction = count * (target_length - replacement_length);
    output_length = input_length - reduction;

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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, cursor, prefix_length);
        destination += prefix_length;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, replacement, replacement_length);
        destination += replacement_length;

        cursor = match + target_length;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t suffix_length = strlen(cursor);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, cursor, suffix_length);
        destination += suffix_length;
    }

    *destination = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *result;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(input);
                    fprintf(stderr, "Input is too large.\n");
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
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

    if (length == SIZE_MAX) {
        free(input);
        fprintf(stderr, "Input is too large.\n");
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            fprintf(stderr, "Failed to allocate input buffer.\n");
            return EXIT_FAILURE;
        }
        input = new_input;
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