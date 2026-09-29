#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int is_power_of_two(uint64_t value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

static int find_nth_polite_number(uint64_t n, uint64_t *result)
{
    uint64_t value = 1;
    uint64_t count = 0;

    if (n == 0 || result == NULL) {
        return 0;
    }

    while (count < n) {
        if (value == UINT64_MAX) {
            return 0;
        }

        ++value;

        if (!is_power_of_two(value)) {
            ++count;
        }
    }

    *result = value;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!find_nth_polite_number((uint64_t)input, &result)) {
        fprintf(stderr, "Unable to compute the result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}