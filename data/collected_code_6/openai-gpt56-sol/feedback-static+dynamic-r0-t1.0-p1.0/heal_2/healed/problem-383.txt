#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_odd_bits(uint32_t value)
{
    return value ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (length == 0 || input[length - 1] != '\n') {
        if (!feof(stdin)) {
            int ch;
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 0);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n", toggle_odd_bits((uint32_t)value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}