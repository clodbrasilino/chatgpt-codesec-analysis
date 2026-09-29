#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_even_natural_numbers(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half_count;
    uint64_t pair_sum;

    if (result == NULL || l == 0U || l > r) {
        return 0;
    }

    first = l + (l & UINT64_C(1));
    last = r - (r & UINT64_C(1));

    if (first > r || first > last) {
        *result = 0U;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    half_count = count / UINT64_C(2);
    pair_sum = first + last;

    if ((count & UINT64_C(1)) != 0U) {
        if (half_count != 0U && pair_sum > UINT64_MAX / half_count) {
            return 0;
        }

        *result = half_count * pair_sum;

        if (last > UINT64_MAX - *result) {
            return 0;
        }

        *result += last;
    } else {
        if (half_count != 0U && pair_sum > UINT64_MAX / half_count) {
            return 0;
        }

        *result = half_count * pair_sum;
    }

    return 1;
}

int main(void)
{
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &l, &r) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_even_natural_numbers(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}