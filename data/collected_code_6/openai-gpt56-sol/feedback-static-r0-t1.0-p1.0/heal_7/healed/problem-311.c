#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    for (uint32_t mask = UINT32_C(1) << 31; mask != 0; mask >>= 1) {
        if ((value & mask) == 0) {
            return value | mask;
        }
    }

    return value;
}

static int read_input(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;
    while (length < size && buffer[length] != '\0') {
        ++length;
    }

    if (length == size) {
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    int ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int main(void)
{
    char input[128];

    if (!read_input(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint32_t result = set_leftmost_unset_bit((uint32_t)parsed);
    printf("%" PRIu32 "\n", result);

    return EXIT_SUCCESS;
}