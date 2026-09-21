#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t set_odd_bits(uint64_t value)
{
    return value | UINT64_C(0xAAAAAAAAAAAAAAAA);
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 0);

    if (end == input || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", set_odd_bits((uint64_t)value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}