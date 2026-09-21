#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate_road(const char *input, size_t input_length)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_length = sizeof(target) - 1;
    const size_t replacement_length = sizeof(replacement) - 1;
    const size_t reduction_per_match = target_length - replacement_length;
    size_t count = 0;
    size_t cursor = 0;
    size_t output_length;
    size_t destination = 0;
    char *output;

    while (cursor <= input_length - (cursor <= input_length ? cursor : input_length) &&
           input_length - cursor >= target_length) {
        if (memcmp(input + cursor, target, target_length) == 0) {
            if (count == SIZE_MAX) {
                return NULL;
            }
            ++count;
            cursor += target_length;
        } else {
            ++cursor;
        }
    }

    if (count > input_length / reduction_per_match) {
        return NULL;
    }

    output_length = input_length - count * reduction_per_match;

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
            if (output_length - destination < replacement_length) {
                free(output);
                return NULL;
            }

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

    output[destination] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    char *result;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
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

    result = abbreviate_road(input, length);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to abbreviate input.\n");
        return EXIT_FAILURE;
    }

    if (fwrite(result, 1, strlen(result), stdout) != strlen(result) ||
        fputc('\n', stdout) == EOF) {
        free(result);
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}