#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int print_binary(uint64_t value)
{
    char binary[sizeof(value) * 8U + 1U];
    size_t index = sizeof(binary) - 1U;

    binary[index] = '\0';

    do {
        if (index == 0U) {
            return -1;
        }

        binary[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1U;
    } while (value != 0U);

    return puts(binary + index) == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative decimal integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Input must be a non-negative decimal integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        value > UINT64_MAX) {
        fprintf(stderr, "Invalid or out-of-range decimal integer.\n");
        return EXIT_FAILURE;
    }

    if (print_binary((uint64_t)value) != 0) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}