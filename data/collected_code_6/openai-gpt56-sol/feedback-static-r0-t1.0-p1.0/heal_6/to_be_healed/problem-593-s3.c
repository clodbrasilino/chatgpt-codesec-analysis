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
        unsigned int value = 0U;
        size_t digits = 0U;
        int written;
        size_t remaining;

        if (*p < '0' || *p > '9') {
            return -1;
        }

        while (*p >= '0' && *p <= '9') {
            const unsigned int digit = (unsigned int)(*p - '0');

            if (value > 25U || (value == 25U && digit > 5U)) {
                output[0] = '\0';
                return -1;
            }

            value = value * 10U + digit;
            ++digits;
            ++p;
        }

        if (digits == 0U ||
            (part < 3U && *p != '.') ||
            (part == 3U && *p != '\0')) {
            output[0] = '\0';
            return -1;
        }

        remaining = output_size - offset;
        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        written = snprintf(output + offset, remaining,
                           part == 0U ? "%u" : ".%u", value);

        if (written < 0 || (size_t)written >= remaining) {
            output[0] = '\0';
            return -1;
        }

        offset += (size_t)written;

        if (part < 3U) {
            ++p;
        }
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    char *result;
    int status = EXIT_FAILURE;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    result = malloc(IPV4_TEXT_SIZE);
    if (result == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, IPV4_TEXT_SIZE) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
    } else if (puts(result) != EOF) {
        status = EXIT_SUCCESS;
    }

    free(result);
    return status;
}