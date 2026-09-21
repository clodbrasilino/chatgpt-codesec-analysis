#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum { IPV4_STRING_SIZE = 16 };

static int remove_leading_zeroes(const char *input, char *output,
                                 size_t output_size)
{
    const char *p;
    size_t offset = 0;

    if (input == NULL || output == NULL || output_size < IPV4_STRING_SIZE) {
        return -1;
    }

    p = input;

    for (unsigned int part = 0; part < 4; ++part) {
        char *end = NULL;
        unsigned long value;
        int written;

        if (*p == '\0') {
            return -1;
        }

        errno = 0;
        value = strtoul(p, &end, 10);

        if (errno != 0 || end == p || value > 255UL) {
            return -1;
        }

        if ((part < 3U && *end != '.') ||
            (part == 3U && *end != '\0')) {
            return -1;
        }

        if (part == 0U) {
            written = snprintf(output + offset, output_size - offset,
                               "%lu", value);
        } else {
            written = snprintf(output + offset, output_size - offset,
                               ".%lu", value);
        }

        if (written < 0 || (size_t)written >= output_size - offset) {
            output[0] = '\0';
            return -1;
        }

        offset += (size_t)written;
        p = (part < 3U) ? end + 1 : end;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *result;
    int status = EXIT_FAILURE;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4 address>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = malloc(IPV4_STRING_SIZE);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], result, IPV4_STRING_SIZE) != 0) {
        fprintf(stderr, "Invalid IPv4 address\n");
    } else if (printf("%s\n", result) >= 0) {
        status = EXIT_SUCCESS;
    }

    free(result);
    return status;
}