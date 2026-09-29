#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void)
{
    char buffer[128];
    char *cursor;
    char *end;
    uintmax_t parsed;
    uint64_t number;
    uint64_t first;
    uint64_t second;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    cursor = buffer;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return EXIT_FAILURE;
    }

    parsed = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed == 0 ||
        parsed > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed;
    divide_max_digit_sum(number, &first, &second);

    if (printf("%" PRIu64 " %" PRIu64 "\n", first, second) < 0 ||
        printf("%" PRIu64 "\n",
               digit_sum(first) + digit_sum(second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}