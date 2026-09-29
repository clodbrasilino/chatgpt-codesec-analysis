#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_even_bits(uint32_t value)
{
    return value | UINT32_C(0x55555555);
}

static int read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
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

    int ch = fgetc(stdin);

    if (ch == '\n' || ch == EOF) {
        return 1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int main(void)
{
    char input[64];
    char *end = NULL;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    uintmax_t parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n",
               set_even_bits((uint32_t)parsed_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}