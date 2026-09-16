#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t digit_sum(uint64_t number)
{
    uint64_t sum = 0;

    do {
        sum += number % 10U;
        number /= 10U;
    } while (number != 0U);

    return sum;
}

static void divide_for_maximum_digit_sum(uint64_t number,
                                         uint64_t *first,
                                         uint64_t *second)
{
    uint64_t part = 0;
    uint64_t place = 1;
    uint64_t remaining = number;

    while (remaining >= 10U) {
        part += 9U * place;
        place *= 10U;
        remaining /= 10U;
    }

    if (part > number) {
        part /= 10U;
    }

    *first = part;
    *second = number - part;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t first;
    uint64_t second;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    divide_for_maximum_digit_sum((uint64_t)input, &first, &second);

    printf("%" PRIu64 " %" PRIu64 "\n", first, second);
    printf("%" PRIu64 "\n", digit_sum(first) + digit_sum(second));

    return EXIT_SUCCESS;
}