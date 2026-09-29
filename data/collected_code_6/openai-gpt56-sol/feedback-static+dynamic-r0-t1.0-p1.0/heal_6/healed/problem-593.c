#include <stdio.h>
#include <stdlib.h>

#define IPV4_OCTETS 4U
#define IPV4_TEXT_SIZE (sizeof("255.255.255.255"))

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
            unsigned int digit = (unsigned int)(*cursor - '0');

            if (value > (255U - digit) / 10U) {
                goto error;
            }

            value = value * 10U + digit;
            ++cursor;
            ++digits;
        }

        if (digits == 0U) {
            goto error;
        }

        if (part + 1U < IPV4_OCTETS) {
            if (*cursor != '.') {
                goto error;
            }
        } else if (*cursor != '\0') {
            goto error;
        }

        remaining = output_size - written;

        if (part == 0U) {
            count = snprintf(output + written, remaining, "%u", value);
        } else {
            count = snprintf(output + written, remaining, ".%u", value);
        }

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
    char output[IPV4_TEXT_SIZE];

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}