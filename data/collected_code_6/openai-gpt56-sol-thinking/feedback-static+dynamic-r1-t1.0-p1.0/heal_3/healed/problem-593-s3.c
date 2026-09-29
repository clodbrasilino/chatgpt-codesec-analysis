#include <stdio.h>
#include <stdlib.h>

typedef enum {
    IP_SUCCESS = 0,
    IP_INVALID_ARGUMENT,
    IP_INVALID_ADDRESS,
    IP_BUFFER_TOO_SMALL,
    IP_FORMAT_ERROR
} IpResult;

enum {
    IPV4_STRING_CAPACITY = sizeof("255.255.255.255")
};

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

IpResult remove_leading_zeroes(const char *input, char *output,
                               size_t output_size)
{
    unsigned int octets[4];
    const char *current;
    size_t required = 3U;
    int written;

    if (input == NULL || output == NULL || output_size == 0U) {
        return IP_INVALID_ARGUMENT;
    }

    current = input;

    for (size_t i = 0U; i < 4U; ++i) {
        unsigned int value = 0U;

        if (*current < '0' || *current > '9') {
            return IP_INVALID_ADDRESS;
        }

        while (*current >= '0' && *current <= '9') {
            unsigned int digit = (unsigned int)(*current - '0');

            if (value > (255U - digit) / 10U) {
                return IP_INVALID_ADDRESS;
            }

            value = value * 10U + digit;
            ++current;
        }

        octets[i] = value;
        required += decimal_digits(value);

        if (i < 3U) {
            if (*current != '.') {
                return IP_INVALID_ADDRESS;
            }

            ++current;
        } else if (*current != '\0') {
            return IP_INVALID_ADDRESS;
        }
    }

    if (required >= output_size) {
        return IP_BUFFER_TOO_SMALL;
    }

    written = snprintf(output, output_size, "%u.%u.%u.%u",
                       octets[0], octets[1], octets[2], octets[3]);

    if (written < 0 || (size_t)written != required) {
        return IP_FORMAT_ERROR;
    }

    return IP_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *normalized;
    IpResult result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    normalized = malloc(IPV4_STRING_CAPACITY);

    if (normalized == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    result = remove_leading_zeroes(
        argv[1], normalized, IPV4_STRING_CAPACITY);

    if (result != IP_SUCCESS) {
        fputs("Invalid IPv4 address\n", stderr);
        free(normalized);
        return EXIT_FAILURE;
    }

    if (puts(normalized) == EOF) {
        free(normalized);
        return EXIT_FAILURE;
    }

    free(normalized);
    return EXIT_SUCCESS;
}