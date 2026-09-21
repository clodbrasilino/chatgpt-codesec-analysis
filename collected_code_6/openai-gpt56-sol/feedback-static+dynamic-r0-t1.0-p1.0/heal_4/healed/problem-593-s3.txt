#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum { IPV4_STRING_SIZE = sizeof("255.255.255.255") };

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
        char *end;
        unsigned long value;
        int written;
        size_t remaining;

        if (*p == '\0') {
            return -1;
        }

        errno = 0;
        end = NULL;
        value = strtoul(p, &end, 10);

        if (errno != 0 || end == p || value > 255UL) {
            output[0] = '\0';
            return -1;
        }

        if ((part < 3U && *end != '.') ||
            (part == 3U && *end != '\0')) {
            output[0] = '\0';
            return -1;
        }

        remaining = output_size - offset;

        if (part == 0U) {
            written = snprintf(output + offset, remaining, "%lu", value);
        } else {
            written = snprintf(output + offset, remaining, ".%lu", value);
        }

        if (written < 0 || (size_t)written >= remaining) {
            output[0] = '\0';
            return -1;
        }

        offset += (size_t)written;
        p = part < 3U ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program);
        return EXIT_FAILURE;
    }

    result = malloc(IPV4_STRING_SIZE);
    if (result == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, IPV4_STRING_SIZE) != 0) {
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