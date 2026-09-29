#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int needs_boundary(
    const unsigned char *begin,
    const unsigned char *current)
{
    unsigned char previous;
    unsigned char value;
    unsigned char next;

    if (current == begin) {
        return 0;
    }

    previous = current[-1];
    value = current[0];
    next = current[1];

    if (!is_ascii_upper(value)) {
        return 0;
    }

    return is_ascii_lower(previous) ||
           is_ascii_digit(previous) ||
           (is_ascii_upper(previous) && is_ascii_lower(next));
}

char *camel_to_snake(const char *input)
{
    const unsigned char *begin;
    const unsigned char *current;
    char *result;
    char *output;
    size_t output_length = 0U;

    if (input == NULL) {
        return NULL;
    }

    begin = (const unsigned char *)input;

    for (current = begin; *current != '\0'; ++current) {
        size_t increment = needs_boundary(begin, current) ? 2U : 1U;

        if (increment > SIZE_MAX - output_length) {
            return NULL;
        }

        output_length += increment;
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(output_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    output = result;

    for (current = begin; *current != '\0'; ++current) {
        if (needs_boundary(begin, current)) {
            *output++ = '_';
        }

        *output++ = (char)tolower((unsigned char)*current);
    }

    *output = '\0';
    return result;
}

int main(int argc, char **argv)
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