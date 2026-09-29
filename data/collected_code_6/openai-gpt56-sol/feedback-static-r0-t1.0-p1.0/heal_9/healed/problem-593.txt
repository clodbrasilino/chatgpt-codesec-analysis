#include <stdio.h>
#include <stdlib.h>

#define IPV4_PARTS 4U
#define IPV4_OUTPUT_SIZE (sizeof("255.255.255.255"))

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const unsigned char *cursor;
    size_t written = 0U;

    if (input == NULL || output == NULL || output_size < IPV4_OUTPUT_SIZE) {
        return -1;
    }

    cursor = (const unsigned char *)input;
    output[0] = '\0';

    for (size_t part = 0U; part < IPV4_PARTS; ++part) {
        unsigned int value = 0U;
        size_t digits = 0U;
        int length;
        const char *format;

        while (*cursor >= (unsigned char)'0' &&
               *cursor <= (unsigned char)'9') {
            if (digits >= 3U) {
                output[0] = '\0';
                return -1;
            }

            value = value * 10U +
                    (unsigned int)(*cursor - (unsigned char)'0');
            ++cursor;
            ++digits;

            if (value > 255U) {
                output[0] = '\0';
                return -1;
            }
        }

        if (digits == 0U) {
            output[0] = '\0';
            return -1;
        }

        if (part + 1U < IPV4_PARTS) {
            if (*cursor != (unsigned char)'.') {
                output[0] = '\0';
                return -1;
            }
            ++cursor;
        } else if (*cursor != (unsigned char)'\0') {
            output[0] = '\0';
            return -1;
        }

        format = (part == 0U) ? "%u" : ".%u";
        length = snprintf(output + written, output_size - written,
                          format, value);

        if (length < 0 || (size_t)length >= output_size - written) {
            output[0] = '\0';
            return -1;
        }

        written += (size_t)length;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char output[IPV4_OUTPUT_SIZE];

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], output, sizeof output) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}