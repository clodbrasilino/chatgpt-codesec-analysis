#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t highest_power_of_two(uint64_t value)
{
    uint64_t result = UINT64_C(1);

    while (result <= value / UINT64_C(2)) {
        result *= UINT64_C(2);
    }

    return result;
}

int main(int argc, char * const argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value == 0 || value > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", highest_power_of_two((uint64_t)value));

    return EXIT_SUCCESS;
}