#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t digit_sum(uint64_t value)
{
    uint64_t sum = 0;

    do {
        sum += value % UINT64_C(10);
        value /= UINT64_C(10);
    } while (value != 0);

    return sum;
}

static void divide_max_digit_sum(uint64_t number,
                                 uint64_t *first,
                                 uint64_t *second)
{
    uint64_t power = UINT64_C(1);

    while (power <= number / UINT64_C(10)) {
        power *= UINT64_C(10);
    }

    *first = power - UINT64_C(1);
    *second = number - *first;
}

static int read_number(uint64_t *number)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t value;
    int ch;

    if (number == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value == 0 ||
        value > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *number = (uint64_t)value;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t first;
    uint64_t second;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    divide_max_digit_sum(number, &first, &second);

    if (printf("%" PRIu64 " %" PRIu64 "\n", first, second) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n",
               digit_sum(first) + digit_sum(second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}