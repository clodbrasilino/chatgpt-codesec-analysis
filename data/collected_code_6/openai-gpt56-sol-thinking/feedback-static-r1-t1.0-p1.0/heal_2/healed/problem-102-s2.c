#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *input)
{
    size_t capacity = 16;
    size_t write_index = 0;
    int capitalize_next = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    output = malloc(capacity);
    if (output == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; input[read_index] != '\0'; ++read_index) {
        unsigned char current = (unsigned char)input[read_index];

        if (current == (unsigned char)'_') {
            capitalize_next = 1;
            continue;
        }

        if (write_index == capacity - 1) {
            char *resized_output;

            if (capacity > SIZE_MAX / 2) {
                free(output);
                return NULL;
            }

            capacity *= 2;
            resized_output = realloc(output, capacity);
            if (resized_output == NULL) {
                free(output);
                return NULL;
            }

            output = resized_output;
        }

        if (capitalize_next) {
            current = (unsigned char)toupper(current);
            capitalize_next = 0;
        }

        output[write_index++] = (char)current;
    }

    output[write_index] = '\0';
    return output;
}

int main(int argc, char **const argv)
{
    char *converted;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fputs("Usage: program snake_case_string\n", stderr);
        return EXIT_FAILURE;
    }

    converted = snake_to_camel(argv[1]);
    if (converted == NULL) {
        fputs("Failed to convert the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(converted) == EOF) {
        fputs("Failed to write the converted string.\n", stderr);
        status = EXIT_FAILURE;
    }

    free(converted);
    return status;
}