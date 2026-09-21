#include <stdio.h>
#include <stdlib.h>

#define IPV4_OCTETS 4U
#define IPV4_TEXT_SIZE sizeof("255.255.255.255")

static int remove_leading_zeroes(const char *input, char **output)
{
    const char *cursor;
    char *buffer;
    size_t written = 0U;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    buffer = malloc(IPV4_TEXT_SIZE);
    if (buffer == NULL) {
        return -1;
    }

    buffer[0] = '\0';
    cursor = input;

    for (size_t part = 0U; part < IPV4_OCTETS; ++part) {
        unsigned int value = 0U;
        size_t digits = 0U;
        size_t remaining;
        int count;

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

        remaining = IPV4_TEXT_SIZE - written;
        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        count = snprintf(buffer + written, remaining,
                         part == 0U ? "%u" : ".%u", value);

        if (count < 0 || (size_t)count >= remaining) {
            goto error;
        }

        written += (size_t)count;

        if (part + 1U < IPV4_OCTETS) {
            ++cursor;
        }
    }

    *output = buffer;
    return 0;

error:
    free(buffer);
    return -1;
}

int main(int argc, char *argv[])
{
    char *output = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        program_name = argc > 0 && argv != NULL && argv[0] != NULL
                           ? argv[0]
                           : "program";
        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], &output) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}