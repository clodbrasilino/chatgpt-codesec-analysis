#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum {
    IP_SUCCESS = 0,
    IP_INVALID_ARGUMENT,
    IP_INVALID_ADDRESS,
    IP_BUFFER_TOO_SMALL,
    IP_FORMAT_ERROR
} IpResult;

static size_t decimal_length(unsigned int value)
{
    if (value >= 100U) {
        return 3U;
    }

    if (value >= 10U) {
        return 2U;
    }

    return 1U;
}

static size_t write_octet(char *output, size_t position, unsigned int value)
{
    if (value >= 100U) {
        output[position++] = (char)('0' + value / 100U);
        value %= 100U;
        output[position++] = (char)('0' + value / 10U);
        output[position++] = (char)('0' + value % 10U);
    } else if (value >= 10U) {
        output[position++] = (char)('0' + value / 10U);
        output[position++] = (char)('0' + value % 10U);
    } else {
        output[position++] = (char)('0' + value);
    }

    return position;
}

IpResult remove_leading_zeroes(const char *input, char *output,
                               size_t output_size)
{
    unsigned int octets[4];
    const char *current;
    size_t required = 1U;
    size_t position = 0U;

    if (input == NULL || output == NULL || output_size == 0U) {
        return IP_INVALID_ARGUMENT;
    }

    current = input;

    for (size_t index = 0U; index < 4U; ++index) {
        unsigned int value = 0U;

        if (*current < '0' || *current > '9') {
            return IP_INVALID_ADDRESS;
        }

        do {
            unsigned int digit = (unsigned int)(*current - '0');

            if (value > (255U - digit) / 10U) {
                return IP_INVALID_ADDRESS;
            }

            value = value * 10U + digit;
            ++current;
        } while (*current >= '0' && *current <= '9');

        octets[index] = value;
        required += decimal_length(value);

        if (index < 3U) {
            if (*current != '.') {
                return IP_INVALID_ADDRESS;
            }

            ++current;
            ++required;
        } else if (*current != '\0') {
            return IP_INVALID_ADDRESS;
        }
    }

    if (output_size < required) {
        return IP_BUFFER_TOO_SMALL;
    }

    for (size_t index = 0U; index < 4U; ++index) {
        position = write_octet(output, position, octets[index]);

        if (index < 3U) {
            output[position++] = '.';
        }
    }

    output[position] = '\0';
    return IP_SUCCESS;
}

int main(int argc, char **const argv)
{
    char *normalized;
    IpResult result;
    int status = EXIT_FAILURE;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    normalized = malloc(16U);
    if (normalized == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    result = remove_leading_zeroes(argv[1], normalized, 16U);

    if (result == IP_SUCCESS) {
        if (puts(normalized) != EOF) {
            status = EXIT_SUCCESS;
        }
    } else {
        fputs("Invalid IPv4 address\n", stderr);
    }

    free(normalized);
    return status;
}