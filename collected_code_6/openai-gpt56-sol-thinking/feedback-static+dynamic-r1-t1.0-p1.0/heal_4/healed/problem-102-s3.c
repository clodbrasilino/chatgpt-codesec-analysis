#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *snake_to_camel(const char *input)
{
    const unsigned char *source;
    char *result;
    size_t capacity = 16;
    size_t destination_index = 0;
    int capitalize_next = 1;

    if (input == NULL) {
        return NULL;
    }

    result = malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    source = (const unsigned char *)input;

    while (*source != '\0') {
        unsigned char character = *source++;

        if (character == (unsigned char)'_') {
            capitalize_next = 1;
            continue;
        }

        if (destination_index == capacity - 1) {
            size_t new_capacity;
            char *resized_result;

            if (capacity > SIZE_MAX / 2) {
                if (capacity == SIZE_MAX) {
                    free(result);
                    return NULL;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            resized_result = realloc(result, new_capacity);
            if (resized_result == NULL) {
                free(result);
                return NULL;
            }

            result = resized_result;
            capacity = new_capacity;
        }

        if (capitalize_next) {
            character = (unsigned char)toupper((int)character);
            capitalize_next = 0;
        }

        result[destination_index++] = (char)character;
    }

    result[destination_index] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    const char *program_name;
    char *camel_case;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", program_name);
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
    if (camel_case == NULL) {
        fputs("Failed to convert string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(camel_case) == EOF) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}