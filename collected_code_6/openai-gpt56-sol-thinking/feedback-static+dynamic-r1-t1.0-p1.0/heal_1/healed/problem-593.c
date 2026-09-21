#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define IPV4_OUTPUT_SIZE (sizeof("255.255.255.255"))

static int parse_octet(const char **cursor, unsigned int *octet)
{
    unsigned int value = 0U;

    if (cursor == NULL || *cursor == NULL || octet == NULL) {
        return -1;
    }

    if (**cursor < '0' || **cursor > '9') {
        return -1;
    }

    while (**cursor >= '0' && **cursor <= '9') {
        unsigned int digit = (unsigned int)(**cursor - '0');

        if (value > (255U - digit) / 10U) {
            return -1;
        }

        value = (value * 10U) + digit;
        ++(*cursor);
    }

    *octet = value;
    return 0;
}

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    unsigned int octet1;
    unsigned int octet2;
    unsigned int octet3;
    unsigned int octet4;
    const char *cursor;
    int written;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    output[0] = '\0';
    cursor = input;

    if (parse_octet(&cursor, &octet1) != 0 || *cursor++ != '.' ||
        parse_octet(&cursor, &octet2) != 0 || *cursor++ != '.' ||
        parse_octet(&cursor, &octet3) != 0 || *cursor++ != '.' ||
        parse_octet(&cursor, &octet4) != 0 || *cursor != '\0') {
        return -1;
    }

    written = snprintf(output, output_size, "%u.%u.%u.%u",
                       octet1, octet2, octet3, octet4);

    if (written < 0 || (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(int argc, char * const argv[])
{
    char *normalized;
    const char *program_name;
    int result = EXIT_FAILURE;

    program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    normalized = malloc(IPV4_OUTPUT_SIZE);
    if (normalized == NULL) {
        (void)fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, IPV4_OUTPUT_SIZE) != 0) {
        (void)fputs("Invalid IPv4 address\n", stderr);
    } else if (puts(normalized) != EOF) {
        result = EXIT_SUCCESS;
    }

    free(normalized);
    return result;
}