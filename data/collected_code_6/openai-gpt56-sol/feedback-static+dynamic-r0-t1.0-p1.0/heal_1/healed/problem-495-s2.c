#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int remove_lowercase_substrings(const char *input, size_t input_len,
                                       char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;

    if (input == NULL || output == NULL || input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;
    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if (ch < (unsigned char)'a' || ch > (unsigned char)'z') {
            result[write_pos++] = (char)ch;
        }
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            fprintf(stderr, "Input is too large.\n");
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
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

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
                return EXIT_FAILURE;
            }

            input = resized;
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

    if (length + 1 > capacity) {
        char *resized = realloc(input, length + 1);

        if (resized == NULL) {
            free(input);
            fprintf(stderr, "Failed to allocate memory.\n");
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (remove_lowercase_substrings(input, length, &output) != 0) {
        free(input);
        fprintf(stderr, "Failed to process input.\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}