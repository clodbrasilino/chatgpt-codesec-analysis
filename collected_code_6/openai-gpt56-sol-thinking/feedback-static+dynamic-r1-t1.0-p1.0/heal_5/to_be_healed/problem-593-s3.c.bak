#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    IP_SUCCESS = 0,
    IP_INVALID_ARGUMENT,
    IP_INVALID_ADDRESS,
    IP_BUFFER_TOO_SMALL,
    IP_FORMAT_ERROR
} IpResult;

IpResult remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    char normalized[16];
    const char *current;
    size_t used = 0U;

    if (input == NULL || output == NULL || output_size == 0U) {
        return IP_INVALID_ARGUMENT;
    }

    current = input;

    for (unsigned int octet = 0U; octet < 4U; ++octet) {
        unsigned int value = 0U;
        size_t remaining;
        int written;

        if (*current < '0' || *current > '9') {
            return IP_INVALID_ADDRESS;
        }

        while (*current >= '0' && *current <= '9') {
            unsigned int digit = (unsigned int)(*current - '0');

            if (value > (255U - digit) / 10U) {
                return IP_INVALID_ADDRESS;
            }

            value = (value * 10U) + digit;
            ++current;
        }

        remaining = sizeof(normalized) - used;
        written = snprintf(normalized + used, remaining, "%u", value);

        if (written < 0 || (size_t)written >= remaining) {
            return IP_FORMAT_ERROR;
        }

        used += (size_t)written;

        if (octet < 3U) {
            if (*current != '.' || used + 1U >= sizeof(normalized)) {
                return IP_INVALID_ADDRESS;
            }

            normalized[used++] = '.';
            ++current;
        } else if (*current != '\0') {
            return IP_INVALID_ADDRESS;
        }
    }

    normalized[used] = '\0';

    if (output_size < used + 1U) {
        return IP_BUFFER_TOO_SMALL;
    }

    memcpy(output, normalized, used + 1U);
    return IP_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    char normalized[16];
    IpResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = remove_leading_zeroes(argv[1], normalized, sizeof(normalized));

    if (result != IP_SUCCESS) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(normalized) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}