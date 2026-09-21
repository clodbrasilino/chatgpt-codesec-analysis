#include <errno.h>
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
        char *end = NULL;
        unsigned long value;
        int written;
        size_t remaining;

        if (*p == '\0' || *p < '0' || *p > '9') {
            return -1;
        }

        errno = 0;
        value = strtoul(p, &end, 10);

        if (errno == ERANGE || end == p || value > 255UL) {
            return -1;
        }

        if ((part < 3U && *end != '.') ||
            (part == 3U && *end != '\0')) {
            return -1;
        }

        remaining = output_size - offset;
        written = snprintf(output + offset, remaining,
                           part == 0U ? "%lu" : ".%lu", value);

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
    char result[IPV4_TEXT_SIZE] = {0};

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
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