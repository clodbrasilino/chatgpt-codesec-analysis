#include <stdio.h>
#include <stdlib.h>

enum { IPV4_OUTPUT_SIZE = sizeof "255.255.255.255" };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const unsigned char *cursor = (const unsigned char *)input;
    size_t written = 0;

    if (input == NULL || output == NULL ||
        output_size < IPV4_OUTPUT_SIZE) {
        return -1;
    }

    output[0] = '\0';

    for (size_t part = 0; part < 4; ++part) {
        unsigned int value = 0;
        size_t digits = 0;
        char normalized[4];
        int count;

        while (*cursor >= '0' && *cursor <= '9') {
            value = value * 10U + (unsigned int)(*cursor - '0');
            ++cursor;
            ++digits;

            if (digits > 3 || value > 255U) {
                output[0] = '\0';
                return -1;
            }
        }

        if (digits == 0 ||
            (part < 3 && *cursor != '.') ||
            (part == 3 && *cursor != '\0')) {
            output[0] = '\0';
            return -1;
        }

        if (part < 3) {
            ++cursor;
        }

        count = snprintf(normalized, sizeof normalized, "%u", value);
        if (count < 1 || (size_t)count >= sizeof normalized) {
            output[0] = '\0';
            return -1;
        }

        if (part != 0) {
            if (written + 1 >= output_size) {
                output[0] = '\0';
                return -1;
            }
            output[written++] = '.';
        }

        if ((size_t)count >= output_size - written) {
            output[0] = '\0';
            return -1;
        }

        for (int i = 0; i < count; ++i) {
            output[written++] = normalized[i];
        }
        output[written] = '\0';
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char output[IPV4_OUTPUT_SIZE];

    if (argc != 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], output, sizeof output) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}