#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    const char *p;
    size_t offset = 0;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    p = input;

    for (int part = 0; part < 4; ++part) {
        char *end = NULL;
        unsigned long value;
        int written;
        size_t remaining;

        if (*p == '\0') {
            return -1;
        }

        errno = 0;
        value = strtoul(p, &end, 10);

        if (errno != 0 || end == p || value > 255) {
            return -1;
        }

        if ((part < 3 && *end != '.') ||
            (part == 3 && *end != '\0')) {
            return -1;
        }

        remaining = output_size - offset;
        written = snprintf(output + offset, remaining,
                           part == 0 ? "%lu" : ".%lu", value);

        if (written < 0 || (size_t)written >= remaining) {
            return -1;
        }

        offset += (size_t)written;
        p = part < 3 ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char * const argv[])
{
    char result[16];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n", argv[0]);
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