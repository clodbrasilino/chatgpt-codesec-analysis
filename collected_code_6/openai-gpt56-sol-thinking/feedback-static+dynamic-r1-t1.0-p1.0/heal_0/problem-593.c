#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    unsigned int octets[4];
    const char *cursor;
    char normalized[16];
    int written;
    size_t i;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    cursor = input;

    for (i = 0U; i < 4U; ++i) {
        unsigned int value = 0U;

        if (*cursor < '0' || *cursor > '9') {
            return -1;
        }

        while (*cursor >= '0' && *cursor <= '9') {
            unsigned int digit = (unsigned int)(*cursor - '0');

            if (value > (255U - digit) / 10U) {
                return -1;
            }

            value = (value * 10U) + digit;
            ++cursor;
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

    written = snprintf(normalized, sizeof(normalized), "%u.%u.%u.%u",
                       octets[0], octets[1], octets[2], octets[3]);

    if (written < 0 || (size_t)written >= sizeof(normalized) ||
        (size_t)written >= output_size) {
        return -1;
    }

    memcpy(output, normalized, (size_t)written + 1U);
    return 0;
}

int main(int argc, char *argv[])
{
    char normalized[16];

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <IPv4 address>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, sizeof(normalized)) != 0) {
        if (fprintf(stderr, "Invalid IPv4 address\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(normalized) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}