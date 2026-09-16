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

static void divide_max_digit_sum(uint64_t number, uint64_t *first, uint64_t *second)
{
    uint64_t power = 1U;

    while (power <= number / 10U) {
        power *= 10U;
    }

    *first = power - 1U;
    *second = number - *first;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uint64_t number;
    uint64_t first;
    uint64_t second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || number == 0U) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    divide_max_digit_sum(number, &first, &second);

    if (printf("%" PRIu64 " %" PRIu64 "\n", first, second) < 0 ||
        printf("%" PRIu64 "\n", digit_sum(first) + digit_sum(second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}