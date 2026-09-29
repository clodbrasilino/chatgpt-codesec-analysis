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
        char *end = NULL;
        unsigned long value;
        int written;
        const char *format = octet_index == 0 ? "%lu" : ".%lu";

        if (*cursor == '\0') {
            output[0] = '\0';
            return -1;
        }

        errno = 0;
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

        written = snprintf(output + used, output_size - used, format, value);
        if (written < 0 || (size_t)written >= output_size - used) {
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
    char *normalized;
    int status = EXIT_FAILURE;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4-address>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    normalized = malloc(IPV4_STRING_SIZE);
    if (normalized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, IPV4_STRING_SIZE) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
    } else if (printf("%s\n", normalized) >= 0) {
        status = EXIT_SUCCESS;
    }

    free(normalized);
    return status;
}