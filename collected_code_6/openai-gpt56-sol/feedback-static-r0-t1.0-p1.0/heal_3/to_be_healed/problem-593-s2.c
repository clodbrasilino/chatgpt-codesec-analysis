#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum { IPV4_STRING_SIZE = 16 };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const char *cursor;
    size_t used = 0;
    unsigned int octet_index;

    if (input == NULL || output == NULL || output_size < IPV4_STRING_SIZE) {
        return -1;
    }

    cursor = input;
    output[0] = '\0';

    for (octet_index = 0; octet_index < 4; ++octet_index) {
        char *end;
        unsigned long value;
        int written;
        size_t remaining;

        if (*cursor == '\0') {
            output[0] = '\0';
            return -1;
        }

        errno = 0;
        end = NULL;
        value = strtoul(cursor, &end, 10);

        if (errno != 0 || end == cursor || value > 255) {
            output[0] = '\0';
            return -1;
        }

        if ((octet_index < 3 && *end != '.') ||
            (octet_index == 3 && *end != '\0')) {
            output[0] = '\0';
            return -1;
        }

        for (const char *p = cursor; p < end; ++p) {
            if (*p < '0' || *p > '9') {
                output[0] = '\0';
                return -1;
            }
        }

        remaining = output_size - used;

        if (octet_index == 0) {
            written = snprintf(output + used, remaining, "%lu", value);
        } else {
            written = snprintf(output + used, remaining, ".%lu", value);
        }

        if (written < 0 || (size_t)written >= remaining) {
            output[0] = '\0';
            return -1;
        }

        used += (size_t)written;
        cursor = octet_index < 3 ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[IPV4_STRING_SIZE];

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4-address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, sizeof normalized) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", normalized) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}