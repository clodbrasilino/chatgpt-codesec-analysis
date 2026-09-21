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

    new_capacity = *capacity != 0U ? *capacity : 1U;

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

static char *camel_to_snake(const char *input, size_t input_length)
{
    char *output;
    size_t capacity;
    size_t input_index;
    size_t output_index;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    capacity = input_length + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        return NULL;
    }

    output_index = 0U;

    for (input_index = 0U; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];
        int insert_separator = 0;

        if (isupper(current) && input_index > 0U) {
            unsigned char previous = (unsigned char)input[input_index - 1U];
            int followed_by_lowercase =
                input_index + 1U < input_length &&
                islower((unsigned char)input[input_index + 1U]);

            if (islower(previous) || isdigit(previous) ||
                (isupper(previous) && followed_by_lowercase)) {
                insert_separator = 1;
            }
        }

        if (insert_separator) {
            if (output_index > SIZE_MAX - 2U ||
                grow_buffer(&output, &capacity, output_index + 2U) != 0) {
                free(output);
                return NULL;
            }

            output[output_index++] = '_';
        }

        if (output_index > SIZE_MAX - 2U ||
            grow_buffer(&output, &capacity, output_index + 2U) != 0) {
            free(output);
            return NULL;
        }

        output[output_index++] = (char)tolower(current);
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result;
    size_t input_length;
    size_t maximum_length;

    if (argc != 2 || argv == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "camel_to_snake";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    if (input == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    maximum_length = SIZE_MAX / 2U - 1U;
#ifdef _SC_ARG_MAX
    {
        long argument_limit = sysconf(_SC_ARG_MAX);

        if (argument_limit > 0 &&
            (uintmax_t)argument_limit < (uintmax_t)maximum_length) {
            maximum_length = (size_t)argument_limit;
        }
    }
#endif

    input_length = strnlen(input, maximum_length);
    if (input_length == maximum_length) {
        fputs("Input is too long or not properly terminated\n", stderr);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(input, input_length);
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