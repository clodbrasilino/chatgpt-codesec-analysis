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
        char *end = NULL;
        unsigned long value;
        int written;
        const char *format = part == 0U ? "%lu" : ".%lu";

        if (*p == '\0') {
            return -1;
        }

        errno = 0;
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

        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        written = snprintf(output + offset, output_size - offset,
                           format, value);

        if (written < 0 || (size_t)written >= output_size - offset) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[IPV4_STRING_SIZE];

    if (argc != 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, sizeof result) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}