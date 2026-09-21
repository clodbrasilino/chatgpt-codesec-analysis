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
    /* Possible weaknesses found:
     *  The scope of the variable 'half' can be reduced. [variableScope]
     */
    uint64_t half;
    uint64_t pair_sum;

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

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    pair_sum = first + last;

    if ((count & UINT64_C(1)) == 0) {
        half = count / UINT64_C(2);
        if (half != 0 && pair_sum > UINT64_MAX / half) {
            return 0;
        }
        *result = half * pair_sum;
    } else {
        pair_sum /= UINT64_C(2);
        if (pair_sum != 0 && count > UINT64_MAX / pair_sum) {
            return 0;
        }
        *result = count * pair_sum;
    }

    return 1;
}

static int parse_range(const char *text, int64_t *l, int64_t *r)
{
    char *end;
    intmax_t left;
    intmax_t right;

    if (text == NULL || l == NULL || r == NULL) {
        return 0;
    }

    errno = 0;
    left = strtoimax(text, &end, 10);
    if (text == end || errno == ERANGE || left < INT64_MIN || left > INT64_MAX) {
        return 0;
    }

    text = end;
    errno = 0;
    right = strtoimax(text, &end, 10);
    if (text == end || errno == ERANGE || right < INT64_MIN || right > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *l = (int64_t)left;
    *r = (int64_t)right;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    int64_t l;
    int64_t r;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_range(input, &l, &r) == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_odd_naturals(l, r, &sum) == 0) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}