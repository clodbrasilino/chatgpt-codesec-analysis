#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    const char *cursor;
    size_t written = 0;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    cursor = input;

    for (unsigned int part = 0; part < 4; ++part) {
        char *end = NULL;
        unsigned long value;
        int count;

        if (*cursor == '\0') {
            return -1;
        }

        for (const char *p = cursor; *p != '\0' && *p != '.'; ++p) {
            if (*p < '0' || *p > '9') {
                return -1;
            }
        }

        errno = 0;
        value = strtoul(cursor, &end, 10);

        if (errno != 0 || end == cursor || value > 255UL) {
            return -1;
        }

        if ((part < 3U && *end != '.') ||
            (part == 3U && *end != '\0')) {
            return -1;
        }

        if (written >= output_size) {
            return -1;
        }

        if (part == 0U) {
            count = snprintf(output + written, output_size - written,
                             "%lu", value);
        } else {
            count = snprintf(output + written, output_size - written,
                             ".%lu", value);
        }

        if (count < 0 || (size_t)count >= output_size - written) {
            output[0] = '\0';
            return -1;
        }

        written += (size_t)count;
        cursor = (part < 3U) ? end + 1 : end;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char output[sizeof("255.255.255.255")];

    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
                                 ? argv[0]
                                 : "program";
        fprintf(stderr, "Usage: %s <IPv4 address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], output, sizeof output) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}