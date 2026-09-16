#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *temporary;

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = (*capacity == 0U) ? 1U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    temporary = realloc(*buffer, new_capacity);
    if (temporary == NULL) {
        return -1;
    }

    *buffer = temporary;
    *capacity = new_capacity;
    return 0;
}

static char *camel_to_snake(const char *input)
{
    char *output;
    size_t input_length;
    size_t capacity;
    size_t output_length;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        return NULL;
    }

    capacity = input_length + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        return NULL;
    }

    output_length = 0U;

    for (i = 0U; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];
        int add_separator = 0;

        if (i > 0U && isupper(current)) {
            unsigned char previous = (unsigned char)input[i - 1U];

            if (islower(previous) || isdigit(previous)) {
                add_separator = 1;
            } else if (isupper(previous) &&
                       i + 1U < input_length &&
                       islower((unsigned char)input[i + 1U])) {
                add_separator = 1;
            }
        }

        if (add_separator) {
            if (output_length > SIZE_MAX - 2U ||
                grow_buffer(&output, &capacity, output_length + 2U) != 0) {
                free(output);
                return NULL;
            }

            output[output_length++] = '_';
        }

        if (output_length > SIZE_MAX - 2U ||
            grow_buffer(&output, &capacity, output_length + 2U) != 0) {
            free(output);
            return NULL;
        }

        output[output_length++] = (char)tolower(current);
    }

    output[output_length] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    char *result;

    if (argc != 2) {
        const char *program_name =
            (argc > 0 && argv[0] != NULL) ? argv[0] : "camel_to_snake";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}