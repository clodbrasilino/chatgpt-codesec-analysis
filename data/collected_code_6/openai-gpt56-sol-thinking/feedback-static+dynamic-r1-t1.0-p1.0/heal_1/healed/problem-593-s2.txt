#include <stdio.h>
#include <stdlib.h>

static int parse_octet(const char **cursor, unsigned int *result)
{
    const char *position;
    unsigned int value = 0U;

    if (cursor == NULL || *cursor == NULL || result == NULL) {
        return -1;
    }

    position = *cursor;

    if (*position < '0' || *position > '9') {
        return -1;
    }

    while (*position >= '0' && *position <= '9') {
        unsigned int digit = (unsigned int)(*position - '0');

        if (value > (255U - digit) / 10U) {
            return -1;
        }

        value = (value * 10U) + digit;
        ++position;
    }

    *cursor = position;
    *result = value;
    return 0;
}

static size_t decimal_digits(unsigned int value)
{
    if (value >= 100U) {
        return 3U;
    }

    if (value >= 10U) {
        return 2U;
    }

    return 1U;
}

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    const char *cursor;
    unsigned int first;
    unsigned int second;
    unsigned int third;
    unsigned int fourth;
    size_t required_size;
    int length;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    cursor = input;

    if (parse_octet(&cursor, &first) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &second) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &third) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &fourth) != 0 || *cursor != '\0') {
        return -1;
    }

    required_size = decimal_digits(first)
                  + decimal_digits(second)
                  + decimal_digits(third)
                  + decimal_digits(fourth)
                  + 4U;

    if (required_size > output_size) {
        return -1;
    }

    length = snprintf(
        output,
        output_size,
        "%u.%u.%u.%u",
        first,
        second,
        third,
        fourth
    );

    if (length < 0 || (size_t)length + 1U != required_size) {
        return -1;
    }

    return 0;
}

int main(int argc, char * const argv[])
{
    char *normalized;
    int result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    normalized = malloc(16U);
    if (normalized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = remove_leading_zeroes(argv[1], normalized, 16U);
    if (result != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        free(normalized);
        return EXIT_FAILURE;
    }

    printf("%s\n", normalized);
    free(normalized);
    return EXIT_SUCCESS;
}