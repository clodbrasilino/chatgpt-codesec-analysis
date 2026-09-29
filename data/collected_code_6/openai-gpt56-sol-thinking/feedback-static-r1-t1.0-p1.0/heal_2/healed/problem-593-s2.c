#include <stdio.h>
#include <stdlib.h>

#define IPV4_TEXT_SIZE (sizeof("255.255.255.255"))

static int parse_octet(const char **cursor, unsigned int *octet)
{
    const char *current;
    unsigned int value = 0U;

    if (cursor == NULL || *cursor == NULL || octet == NULL) {
        return -1;
    }

    current = *cursor;

    if (*current < '0' || *current > '9') {
        return -1;
    }

    while (*current >= '0' && *current <= '9') {
        const unsigned int digit = (unsigned int)(*current - '0');

        if (value > (255U - digit) / 10U) {
            return -1;
        }

        value = (value * 10U) + digit;
        ++current;
    }

    *cursor = current;
    *octet = value;

    return 0;
}

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    const char *cursor;
    unsigned int octet1;
    unsigned int octet2;
    unsigned int octet3;
    unsigned int octet4;
    int required;
    int written;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    cursor = input;

    if (parse_octet(&cursor, &octet1) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &octet2) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &octet3) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &octet4) != 0 || *cursor != '\0') {
        return -1;
    }

    required = snprintf(
        NULL,
        0,
        "%u.%u.%u.%u",
        octet1,
        octet2,
        octet3,
        octet4
    );

    if (required < 0 || (size_t)required >= output_size) {
        return -1;
    }

    written = snprintf(
        output,
        output_size,
        "%u.%u.%u.%u",
        octet1,
        octet2,
        octet3,
        octet4
    );

    if (written != required) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *normalized;
    int result = EXIT_FAILURE;

    program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    normalized = malloc(IPV4_TEXT_SIZE);
    if (normalized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, IPV4_TEXT_SIZE) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        goto cleanup;
    }

    if (printf("%s\n", normalized) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(normalized);
    return result;
}