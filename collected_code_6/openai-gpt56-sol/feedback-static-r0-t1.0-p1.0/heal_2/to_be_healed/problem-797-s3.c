#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_odd_natural_numbers(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || l == 0 || l > r) {
        return 0;
    }

    first = l | UINT64_C(1);
    last = (r & UINT64_C(1)) != 0 ? r : r - UINT64_C(1);

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    factor = (first / UINT64_C(2)) +
             (last / UINT64_C(2)) +
             UINT64_C(1);

    if (factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char trailing;
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sscanf(input, "%" SCNu64 " %" SCNu64 " %c", &l, &r, &trailing) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_odd_natural_numbers(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}