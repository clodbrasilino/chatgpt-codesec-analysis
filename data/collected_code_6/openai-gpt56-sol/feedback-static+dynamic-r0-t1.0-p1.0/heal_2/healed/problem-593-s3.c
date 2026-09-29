#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum { IPV4_STRING_SIZE = 16 };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const char *p;
    size_t offset = 0;

    if (input == NULL || output == NULL || output_size < IPV4_STRING_SIZE) {
        return -1;
    }

    output[0] = '\0';
    p = input;

    for (unsigned int part = 0; part < 4U; ++part) {
        char *end = NULL;
        unsigned long value;
        int written;

        if (*p == '\0') {
            return -1;
        }

        errno = 0;
        value = strtoul(p, &end, 10);

        if (errno != 0 || end == p || value > 255UL) {
            return -1;
        }

        if ((part < 3U && *end != '.') ||
            (part == 3U && *end != '\0')) {
            return -1;
        }

        written = snprintf(output + offset, output_size - offset,
                           part == 0U ? "%lu" : ".%lu", value);

        if (written < 0 || (size_t)written >= output_size - offset) {
            output[0] = '\0';
            return -1;
        }

        offset += (size_t)written;
        p = part < 3U ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    char result[IPV4_STRING_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, sizeof result) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}