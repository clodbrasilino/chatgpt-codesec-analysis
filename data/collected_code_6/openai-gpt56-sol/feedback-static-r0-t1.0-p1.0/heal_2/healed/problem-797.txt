#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_naturals(int64_t l, int64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || l < 1 || r < l) {
        return 0;
    }

    first = (uint64_t)l;
    last = (uint64_t)r;

    if ((first & UINT64_C(1)) == 0) {
        ++first;
    }

    if ((last & UINT64_C(1)) == 0) {
        --last;
    }

    if (first > last) {
        *result = UINT64_C(0);
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    factor = first / UINT64_C(2) + last / UINT64_C(2) +
             (first % UINT64_C(2) + last % UINT64_C(2)) / UINT64_C(2);

    if (factor != 0 && count > UINT64_MAX / factor) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

int main(void)
{
    intmax_t left_value;
    intmax_t right_value;
    int64_t l;
    int64_t r;
    uint64_t sum;
    int ch;

    errno = 0;
    if (scanf("%" SCNdMAX " %" SCNdMAX, &left_value, &right_value) != 2 ||
        errno == ERANGE ||
        left_value < INT64_MIN || left_value > INT64_MAX ||
        right_value < INT64_MIN || right_value > INT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    l = (int64_t)left_value;
    r = (int64_t)right_value;

    if (!sum_odd_naturals(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}