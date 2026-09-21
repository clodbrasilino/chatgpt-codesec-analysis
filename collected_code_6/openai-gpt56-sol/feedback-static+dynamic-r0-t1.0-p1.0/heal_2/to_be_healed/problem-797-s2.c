#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_odd_naturals(uint64_t l, uint64_t r, uint64_t *result)
{
    if (result == NULL || l == 0 || l > r) {
        return 0;
    }

    uint64_t first = l | UINT64_C(1);
    uint64_t last = (r & UINT64_C(1)) != 0 ? r : r - UINT64_C(1);

    if (first > last) {
        *result = 0;
        return 1;
    }

    uint64_t count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    uint64_t factor = first + count - UINT64_C(1);

    if (factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

int main(void)
{
    uint64_t l;
    uint64_t r;
    uint64_t sum;
    char trailing;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &l, &r) != 2 ||
        scanf(" %c", &trailing) == 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_odd_naturals(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}