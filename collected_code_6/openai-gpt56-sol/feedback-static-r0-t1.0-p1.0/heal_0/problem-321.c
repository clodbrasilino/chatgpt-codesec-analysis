#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int is_demlo_number(uint64_t number)
{
    uint64_t square = number * number;
    uint64_t multiplier = 1;

    while (multiplier <= number) {
        if (square % 10U != multiplier % 10U) {
            return 0;
        }

        square /= 10U;
        multiplier /= 10U;

        if (multiplier == 0U) {
            break;
        }
    }

    return 1;
}

int main(void)
{
    char input[64];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno != 0 || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_C(3037000499)) {
        return EXIT_FAILURE;
    }

    printf("%s\n", is_demlo_number((uint64_t)value) ? "Demlo number"
                                                    : "Not a Demlo number");

    return EXIT_SUCCESS;
}