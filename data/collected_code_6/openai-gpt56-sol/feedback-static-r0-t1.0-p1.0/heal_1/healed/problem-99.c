#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void print_binary(uint64_t value)
{
    char binary[UINT64_WIDTH + 1];
    size_t index = sizeof(binary) - 1;

    binary[index] = '\0';

    do {
        binary[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    } while (value != 0);

    puts(binary + index);
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative decimal integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        value > UINT64_MAX) {
        fputs("Invalid decimal integer\n", stderr);
        return EXIT_FAILURE;
    }

    print_binary((uint64_t)value);
    return EXIT_SUCCESS;
}