#include <stdio.h>
#include <stdlib.h>

enum { IPV4_TEXT_SIZE = sizeof "255.255.255.255" };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const char *cursor;
    size_t used = 0;

    if (input == NULL || output == NULL || output_size < IPV4_TEXT_SIZE) {
        return -1;
    }

    cursor = input;
    output[0] = '\0';

    for (unsigned int octet_index = 0; octet_index < 4; ++octet_index) {
        unsigned int value = 0;
        size_t digits = 0;
        int written;

        while (*cursor >= '0' && *cursor <= '9') {
            if (value > 25U ||
                (value == 25U && (unsigned int)(*cursor - '0') > 5U)) {
                output[0] = '\0';
                return -1;
            }

            value = value * 10U + (unsigned int)(*cursor - '0');
            ++cursor;
            ++digits;
        }

        if (digits == 0 ||
            (octet_index < 3 && *cursor != '.') ||
            (octet_index == 3 && *cursor != '\0')) {
            output[0] = '\0';
            return -1;
        }

        if (octet_index < 3) {
            ++cursor;
        }

        if (octet_index == 0) {
            written = snprintf(output + used, output_size - used,
                               "%u", value);
        } else {
            written = snprintf(output + used, output_size - used,
                               ".%u", value);
        }

        if (written < 0 || (size_t)written >= output_size - used) {
            output[0] = '\0';
            return -1;
        }

        used += (size_t)written;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[IPV4_TEXT_SIZE];

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4-address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized,
                              sizeof normalized) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", normalized) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}