#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate_road(const char *input, size_t input_length,
                      size_t *result_length)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_length = sizeof target - 1;
    const size_t replacement_length = sizeof replacement - 1;
    const size_t reduction = target_length - replacement_length;
    size_t count = 0;
    size_t cursor = 0;
    size_t output_length;
    size_t destination = 0;
    char *output;

    if (result_length == NULL ||
        (input == NULL && input_length != 0)) {
        return NULL;
    }

    *result_length = 0;

    while (cursor <= input_length - (cursor <= input_length
                                     ? cursor : input_length) &&
           input_length - cursor >= target_length) {
        if (memcmp(input + cursor, target, target_length) == 0) {
            count++;
            cursor += target_length;
        } else {
            cursor++;
        }
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

    cursor = 0;

    while (cursor < input_length) {
        if (input_length - cursor >= target_length &&
            memcmp(input + cursor, target, target_length) == 0) {
            if (destination > output_length ||
                replacement_length > output_length - destination) {
                free(output);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + destination, replacement, replacement_length);
            destination += replacement_length;
            cursor += target_length;
        } else {
            if (destination >= output_length) {
                free(output);
                return NULL;
            }

            output[destination++] = input[cursor++];
        }
    }

    if (destination != output_length) {
        free(output);
        return NULL;
    }

    output[output_length] = '\0';
    *result_length = output_length;
    return output;
}

int main(void)
{
    char *input = NULL;
    char *result;
    size_t capacity = 0;
    size_t length = 0;
    size_t result_length = 0;
    int ch = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate input buffer.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    result = abbreviate_road(input, length, &result_length);
    free(input);

    if (result == NULL) {
        fputs("Failed to abbreviate input.\n", stderr);
        return EXIT_FAILURE;
    }

    if ((result_length > 0 &&
         fwrite(result, 1, result_length, stdout) != result_length) ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        free(result);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}