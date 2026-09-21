#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_natural_numbers(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half_count;
    uint64_t pair_sum;
    uint64_t sum;

    if (result == NULL || l == 0 || l > r) {
        return 0;
    }

    if ((l & UINT64_C(1)) != 0) {
        if (l == UINT64_MAX) {
            *result = 0;
            return 1;
        }
        first = l + UINT64_C(1);
    } else {
        first = l;
    }

    last = r - (r & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);

    if (first > UINT64_MAX - last) {
        return 0;
    }

    pair_sum = first + last;
    half_count = count / UINT64_C(2);

    if (half_count != 0 && pair_sum > UINT64_MAX / half_count) {
        return 0;
    }

    sum = half_count * pair_sum;

    if ((count & UINT64_C(1)) != 0) {
        if (sum > UINT64_MAX - last) {
            return 0;
        }
        sum += last;
    }

    *result = sum;
    return 1;
}

static int read_range(uint64_t *l, uint64_t *r)
{
    char *line;
    char *end;
    char *next;
    uintmax_t first;
    uintmax_t second;
    size_t capacity;

    if (l == NULL || r == NULL) {
        return 0;
    }

    line = NULL;
    capacity = 0;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    first = strtoumax(line, &end, 10);
    if (end == line || errno == ERANGE) {
        free(line);
        return 0;
    }

    next = end;
    errno = 0;
    second = strtoumax(next, &end, 10);
    if (end == next || errno == ERANGE) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || first > UINT64_MAX || second > UINT64_MAX) {
        free(line);
        return 0;
    }

    *l = (uint64_t)first;
    *r = (uint64_t)second;

    free(line);
    return 1;
}

int main(void)
{
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    if (!read_range(&l, &r)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_natural_numbers(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}