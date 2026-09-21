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
    IPV4_STRING_CAPACITY = 16
};

IpResult remove_leading_zeroes(const char *input, char *output,
                               size_t output_size)
{
    unsigned int octets[4];
    const char *current;
    int required;
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
            const unsigned int digit = (unsigned int)(*current - '0');

            if (value > (255U - digit) / 10U) {
                return IP_INVALID_ADDRESS;
            }

            value = value * 10U + digit;
            ++current;
        }

        octets[i] = value;

        if (i < 3U) {
            if (*current != '.') {
                return IP_INVALID_ADDRESS;
            }

            ++current;
        } else if (*current != '\0') {
            return IP_INVALID_ADDRESS;
        }
    }

    required = snprintf(NULL, 0, "%u.%u.%u.%u",
                        octets[0], octets[1], octets[2], octets[3]);

    if (required < 0) {
        return IP_FORMAT_ERROR;
    }

    if ((size_t)required >= output_size) {
        return IP_BUFFER_TOO_SMALL;
    }

    written = snprintf(output, output_size, "%u.%u.%u.%u",
                       octets[0], octets[1], octets[2], octets[3]);

    if (written != required) {
        return IP_FORMAT_ERROR;
    }

    return IP_SUCCESS;
}

int main(int argc, char *argv[const])
{
    char normalized[IPV4_STRING_CAPACITY];
    IpResult result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    result = remove_leading_zeroes(
        argv[1], normalized, sizeof normalized);

    if (result != IP_SUCCESS) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(normalized) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}