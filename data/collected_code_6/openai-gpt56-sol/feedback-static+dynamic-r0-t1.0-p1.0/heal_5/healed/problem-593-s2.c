#include <stdio.h>
#include <stdlib.h>

#define IPV4_TEXT_SIZE (sizeof("255.255.255.255"))

static int normalize_ipv4(const char *input, char *output, size_t output_size)
{
    unsigned int octets[4] = {0U, 0U, 0U, 0U};
    const char *cursor;
    int written;

    if (input == NULL || output == NULL || output_size < IPV4_TEXT_SIZE) {
        return -1;
    }

    output[0] = '\0';
    cursor = input;

    for (size_t i = 0U; i < 4U; ++i) {
        unsigned int value = 0U;
        size_t digits = 0U;

        while (*cursor >= '0' && *cursor <= '9') {
            unsigned int digit = (unsigned int)(*cursor - '0');

            if (value > 25U || (value == 25U && digit > 5U)) {
                return -1;
            }

            value = value * 10U + digit;
            ++cursor;
            ++digits;
        }

        if (digits == 0U) {
            return -1;
        }

        octets[i] = value;

        if (i < 3U) {
            if (*cursor != '.') {
                return -1;
            }
            ++cursor;
        } else if (*cursor != '\0') {
            return -1;
        }
    }

    written = snprintf(output, output_size, "%u.%u.%u.%u",
                       octets[0], octets[1], octets[2], octets[3]);

    if (written < 0 || (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char normalized[IPV4_TEXT_SIZE];

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <IPv4-address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (normalize_ipv4(argv[1], normalized, sizeof normalized) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", normalized) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}