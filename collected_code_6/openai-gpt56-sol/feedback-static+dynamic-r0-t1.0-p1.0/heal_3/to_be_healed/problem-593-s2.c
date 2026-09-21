#include <errno.h>
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

    for (int octet_index = 0; octet_index < 4; ++octet_index) {
        const char *p = cursor;
        char *end = NULL;
        unsigned long value;
        int written;

        if (*cursor == '\0') {
            return -1;
        }

        while (*p != '\0' && *p != '.') {
            if (*p < '0' || *p > '9') {
                return -1;
            }
            ++p;
        }

        errno = 0;
        value = strtoul(cursor, &end, 10);

        if (errno != 0 || end == cursor || end != p || value > 255UL) {
            return -1;
        }

        if ((octet_index < 3 && *end != '.') ||
            (octet_index == 3 && *end != '\0')) {
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        written = snprintf(output + used, output_size - used,
                           octet_index == 0 ? "%lu" : ".%lu", value);

        if (written < 0 || (size_t)written >= output_size - used) {
            output[0] = '\0';
            return -1;
        }

        used += (size_t)written;
        cursor = octet_index < 3 ? end + 1 : end;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[IPV4_TEXT_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4-address>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, sizeof normalized) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", normalized) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}