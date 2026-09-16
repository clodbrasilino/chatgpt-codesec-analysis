#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t digit_sum(uint64_t value)
{
    uint64_t sum = 0;

    do {
        sum += value % 10U;
        value /= 10U;
    } while (value != 0U);

    return sum;
}

static void divide_max_digit_sum(uint64_t number, uint64_t *first,
                                 uint64_t *second)
{
    uint64_t part = 0;
    uint64_t place = 1;
    uint64_t remaining = number;

    while (remaining >= 10U) {
        part += 9U * place;
        remaining /= 10U;
        place *= 10U;
    }

    *first = part;
    *second = number - part;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t first;
    uint64_t second;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    divide_max_digit_sum((uint64_t)parsed, &first, &second);

    printf("%" PRIu64 " %" PRIu64 "\n", first, second);
    printf("Maximum digit sum: %" PRIu64 "\n",
           digit_sum(first) + digit_sum(second));

    return EXIT_SUCCESS;
}