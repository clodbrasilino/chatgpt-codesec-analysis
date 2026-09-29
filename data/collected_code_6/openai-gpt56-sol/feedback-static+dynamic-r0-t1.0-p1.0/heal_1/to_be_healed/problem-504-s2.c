#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    b = n + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (a != 0U && a > UINT64_MAX / a) {
        return 0;
    }

    *result = a * a;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    int status;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    status = scanf("%" SCNu64, &n);
    if (status != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    if (!cube_sum(n, &result)) {
        fputs("Result exceeds the uint64_t range\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}