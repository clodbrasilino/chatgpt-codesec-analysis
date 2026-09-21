#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define IPV4_OCTETS 4U
#define IPV4_TEXT_SIZE 16U

static int remove_leading_zeroes(const char *input,
                                 char *output,
                                 size_t output_size)
{
    const char *cursor;
    size_t written = 0;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    output[0] = '\0';
    cursor = input;

    for (unsigned int part = 0; part < IPV4_OCTETS; ++part) {
        char *end;
        unsigned long value;
        int count;
        size_t remaining;

        if (*cursor == '\0') {
            return -1;
        }

        for (const char *p = cursor; *p != '\0' && *p != '.'; ++p) {
            if (*p < '0' || *p > '9') {
                return -1;
            }
        }

        errno = 0;
        end = NULL;
        value = strtoul(cursor, &end, 10);

        if (errno != 0 || end == cursor || value > 255UL) {
            return -1;
        }

        if ((part < IPV4_OCTETS - 1U && *end != '.') ||
            (part == IPV4_OCTETS - 1U && *end != '\0')) {
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
                         part == 0U ? "%lu" : ".%lu", value);

        if (count < 0 || (size_t)count >= remaining) {
            output[0] = '\0';
            return -1;
        }

        written += (size_t)count;
        cursor = part < IPV4_OCTETS - 1U ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *output;
    int result;

    if (argc != 2) {
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

    result = remove_leading_zeroes(argv[1], output, IPV4_TEXT_SIZE);
    if (result != 0) {
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