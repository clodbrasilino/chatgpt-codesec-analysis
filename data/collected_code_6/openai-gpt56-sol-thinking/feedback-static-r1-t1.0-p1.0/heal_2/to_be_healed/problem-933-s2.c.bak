#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_ascii_upper(unsigned char value)
{
    return value >= (unsigned char)'A' && value <= (unsigned char)'Z';
}

static int is_ascii_lower(unsigned char value)
{
    return value >= (unsigned char)'a' && value <= (unsigned char)'z';
}

static int is_ascii_digit(unsigned char value)
{
    return value >= (unsigned char)'0' && value <= (unsigned char)'9';
}

char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t boundary_count = 0U;
    size_t output_length;
    size_t input_index;
    size_t output_index = 0U;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        return NULL;
    }

    for (input_index = 1U; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];
        unsigned char previous = (unsigned char)input[input_index - 1U];
        int has_lowercase_next =
            input_index + 1U < input_length &&
            is_ascii_lower((unsigned char)input[input_index + 1U]);

        if (is_ascii_upper(current) &&
            (is_ascii_lower(previous) ||
             is_ascii_digit(previous) ||
             (is_ascii_upper(previous) && has_lowercase_next))) {
            ++boundary_count;
        }
    }

    if (boundary_count > SIZE_MAX - input_length - 1U) {
        return NULL;
    }

    output_length = input_length + boundary_count;
    result = malloc(output_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (input_index = 0U; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (input_index > 0U && is_ascii_upper(current)) {
            unsigned char previous =
                (unsigned char)input[input_index - 1U];
            int has_lowercase_next =
                input_index + 1U < input_length &&
                is_ascii_lower((unsigned char)input[input_index + 1U]);

            if (is_ascii_lower(previous) ||
                is_ascii_digit(previous) ||
                (is_ascii_upper(previous) && has_lowercase_next)) {
                result[output_index++] = '_';
            }
        }

        result[output_index++] = (char)tolower(current);
    }

    result[output_index] = '\0';
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result);
    free(result);

    return EXIT_SUCCESS;
}