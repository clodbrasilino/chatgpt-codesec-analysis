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
    size_t match_count = 0;
    size_t output_length;
    const char *cursor;
    const char *match;
    char *output;
    char *destination;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    cursor = input;

    while ((match = strstr(cursor, target)) != NULL) {
        ++match_count;
        cursor = match + target_length;
    }

    if (match_count > input_length / target_length) {
        return NULL;
    }

    output_length =
        input_length - match_count * (target_length - replacement_length);

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
        size_t used = (size_t)(destination - output);

        if (used > output_length ||
            prefix_length > output_length - used) {
            free(output);
            return NULL;
        }

        memcpy(destination, cursor, prefix_length);
        destination += prefix_length;

        used = (size_t)(destination - output);

        if (used > output_length ||
            replacement_length > output_length - used) {
            free(output);
            return NULL;
        }

        memcpy(destination, replacement, replacement_length);
        destination += replacement_length;
        cursor = match + target_length;
    }

    {
        size_t consumed = (size_t)(cursor - input);
        size_t used = (size_t)(destination - output);
        size_t remaining;

        if (consumed > input_length || used > output_length) {
            free(output);
            return NULL;
        }

        remaining = input_length - consumed;

        if (remaining > output_length - used) {
            free(output);
            return NULL;
        }

        memcpy(destination, cursor, remaining);
        destination += remaining;
    }

    if ((size_t)(destination - output) != output_length) {
        free(output);
        return NULL;
    }

    *destination = '\0';
    return output;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);
    char *result;
    int ch = EOF;

    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
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

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}