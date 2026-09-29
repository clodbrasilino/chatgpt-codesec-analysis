#include <stdio.h>
#include <stdlib.h>

#define IPV4_OCTETS 4U
#define IPV4_TEXT_SIZE sizeof("255.255.255.255")

static int remove_leading_zeroes(const char *input,
                                 char *output,
                                 size_t output_size)
{
    const char *cursor;
    size_t written = 0U;

    if (input == NULL || output == NULL || output_size < IPV4_TEXT_SIZE) {
        return -1;
    }

    output[0] = '\0';
    cursor = input;

    for (size_t part = 0U; part < IPV4_OCTETS; ++part) {
        unsigned int value = 0U;
        size_t digits = 0U;
        int count;
        size_t remaining;

        while (*cursor >= '0' && *cursor <= '9') {
            value = value * 10U + (unsigned int)(*cursor - '0');
            if (value > 255U) {
                goto error;
            }

            ++cursor;
            ++digits;
        }

        if (digits == 0U) {
            goto error;
        }

        if ((part + 1U < IPV4_OCTETS && *cursor != '.') ||
            (part + 1U == IPV4_OCTETS && *cursor != '\0')) {
            goto error;
        }

        remaining = output_size - written;
        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        count = snprintf(output + written,
                         remaining,
                         part == 0U ? "%u" : ".%u",
                         value);

        if (count < 0 || (size_t)count >= remaining) {
            goto error;
        }

        written += (size_t)count;

        if (part + 1U < IPV4_OCTETS) {
            ++cursor;
        }
    }

    return 0;

error:
    output[0] = '\0';
    return -1;
}

int main(int argc, char *argv[])
{
    char *output;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    output = malloc(IPV4_TEXT_SIZE);
    if (output == NULL) {
        fprintf(stderr, "Unable to allocate output buffer\n");
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], output, IPV4_TEXT_SIZE) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        free(output);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}