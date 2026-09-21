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

    for (unsigned int part = 0; part < 4; ++part) {
        char *end = NULL;
        unsigned long value;
        int written;
        const char *format;

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

        format = part == 0U ? "%lu" : ".%lu";
        written = snprintf(output + offset, output_size - offset,
                           format, value);

        if (written < 0 || (size_t)written >= output_size - offset) {
            return -1;
        }

        offset += (size_t)written;
        p = part < 3U ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char result[sizeof("255.255.255.255")];

    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
                                       ? argv[0]
                                       : "program";
        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, sizeof(result)) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}