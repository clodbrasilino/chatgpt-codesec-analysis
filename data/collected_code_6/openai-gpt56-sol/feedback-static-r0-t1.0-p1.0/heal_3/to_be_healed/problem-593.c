#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum { IPV4_OUTPUT_SIZE = 16 };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const char *cursor;
    size_t written = 0;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    cursor = input;
    output[0] = '\0';

    for (size_t part = 0; part < 4; ++part) {
        char *end = NULL;
        unsigned long value;
        size_t remaining;
        int count;

        if (*cursor == '\0' || *cursor < '0' || *cursor > '9') {
            return -1;
        }

        errno = 0;
        value = strtoul(cursor, &end, 10);

        if (errno != 0 || end == cursor || value > 255UL) {
            return -1;
        }

        for (const char *p = cursor; p < end; ++p) {
            if (*p < '0' || *p > '9') {
                return -1;
            }
        }

        if ((part < 3 && *end != '.') ||
            (part == 3 && *end != '\0')) {
            return -1;
        }

        if (written >= output_size) {
            output[0] = '\0';
            return -1;
        }

        remaining = output_size - written;
        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        count = snprintf(output + written, remaining,
                         part == 0 ? "%lu" : ".%lu", value);

        if (count < 0 || (size_t)count >= remaining) {
            output[0] = '\0';
            return -1;
        }

        written += (size_t)count;
        cursor = part < 3 ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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