#include <stdio.h>
#include <stdlib.h>

enum { IPV4_OUTPUT_SIZE = sizeof "255.255.255.255" };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const unsigned char *cursor;
    size_t written = 0;

    if (input == NULL || output == NULL ||
        output_size < IPV4_OUTPUT_SIZE) {
        return -1;
    }

    cursor = (const unsigned char *)input;
    output[0] = '\0';

    for (size_t part = 0; part < 4; ++part) {
        unsigned int value = 0;
        size_t digits = 0;
        int count;

        while (*cursor >= (unsigned char)'0' &&
               *cursor <= (unsigned char)'9') {
            if (digits == 3) {
                output[0] = '\0';
                return -1;
            }

            value = value * 10U + (unsigned int)(*cursor - (unsigned char)'0');
            ++cursor;
            ++digits;

            if (value > 255U) {
                output[0] = '\0';
                return -1;
            }
        }

        if (digits == 0 ||
            (part < 3 && *cursor != (unsigned char)'.') ||
            (part == 3 && *cursor != (unsigned char)'\0')) {
            output[0] = '\0';
            return -1;
        }

        if (part < 3) {
            ++cursor;
        }

        if (part != 0) {
            if (written + 1 >= output_size) {
                output[0] = '\0';
                return -1;
            }

            output[written++] = '.';
        }

        count = snprintf(output + written, output_size - written, "%u", value);
        if (count < 0 || (size_t)count >= output_size - written) {
            output[0] = '\0';
            return -1;
        }

        written += (size_t)count;
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