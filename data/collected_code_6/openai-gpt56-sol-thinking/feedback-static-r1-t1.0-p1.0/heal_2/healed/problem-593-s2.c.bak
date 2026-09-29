#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    const char *cursor;
    unsigned int octets[4];
    char normalized[16];
    int length;
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
            const unsigned int digit = (unsigned int)(*cursor - '0');

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

    length = snprintf(
        normalized,
        sizeof(normalized),
        "%u.%u.%u.%u",
        octets[0],
        octets[1],
        octets[2],
        octets[3]
    );

    if (length < 0 || (size_t)length >= sizeof(normalized)) {
        return -1;
    }

    if ((size_t)length + 1U > output_size) {
        return -1;
    }

    memmove(output, normalized, (size_t)length + 1U);

    return 0;
}

int main(int argc, char *argv[const])
{
    char normalized[16];
    const char *program_name;

    program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "ipv4-normalize";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, sizeof(normalized)) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", normalized);

    return EXIT_SUCCESS;
}