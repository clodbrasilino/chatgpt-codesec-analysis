#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate_road(const char *input, size_t input_length)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_length = sizeof target - 1;
    const size_t replacement_length = sizeof replacement - 1;
    size_t position = 0;
    size_t output_position = 0;
    size_t output_length = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    while (position < input_length) {
        if (input_length - position >= target_length &&
            memcmp(input + position, target, target_length) == 0) {
            if (output_length > SIZE_MAX - replacement_length) {
                return NULL;
            }
            output_length += replacement_length;
            position += target_length;
        } else {
            if (output_length == SIZE_MAX) {
                return NULL;
            }
            ++output_length;
            ++position;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    position = 0;

    while (position < input_length) {
        if (input_length - position >= target_length &&
            memcmp(input + position, target, target_length) == 0) {
            if (replacement_length > output_length - output_position) {
                free(output);
                return NULL;
            }

            memcpy(output + output_position, replacement, replacement_length);
            output_position += replacement_length;
            position += target_length;
        } else {
            if (output_position >= output_length) {
                free(output);
                return NULL;
            }

            output[output_position++] = input[position++];
        }
    }

    if (output_position != output_length) {
        free(output);
        return NULL;
    }

    output[output_position] = '\0';
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

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

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

    result = abbreviate_road(input, length);
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