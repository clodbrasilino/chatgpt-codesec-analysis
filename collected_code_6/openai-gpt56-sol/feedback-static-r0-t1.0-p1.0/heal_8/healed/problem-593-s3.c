#include <stdio.h>
#include <stdlib.h>

#define IPV4_TEXT_SIZE 16U

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const char *p;
    size_t offset = 0U;

    if (input == NULL || output == NULL || output_size < IPV4_TEXT_SIZE) {
        return -1;
    }

    output[0] = '\0';
    p = input;

    for (unsigned int part = 0U; part < 4U; ++part) {
        unsigned int value = 0U;
        size_t remaining;
        int written;

        if (*p < '0' || *p > '9') {
            return -1;
        }

        while (*p >= '0' && *p <= '9') {
            unsigned int digit = (unsigned int)(*p - '0');

            if (value > 25U || (value == 25U && digit > 5U)) {
                output[0] = '\0';
                return -1;
            }

            value = value * 10U + digit;
            ++p;
        }

        if ((part < 3U && *p != '.') ||
            (part == 3U && *p != '\0')) {
            output[0] = '\0';
            return -1;
        }

        remaining = output_size - offset;

        if (part == 0U) {
            written = snprintf(output + offset, remaining, "%u", value);
        } else {
            written = snprintf(output + offset, remaining, ".%u", value);
        }

        if (written < 0 || (size_t)written >= remaining) {
            output[0] = '\0';
            return -1;
        }

        offset += (size_t)written;

        if (part < 3U) {
            ++p;
        }
    }

    return 0;
}

int main(int argc, char * const argv[])
{
    char *result;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    result = malloc(IPV4_TEXT_SIZE);
    if (result == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, IPV4_TEXT_SIZE) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}