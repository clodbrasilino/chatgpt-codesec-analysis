#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum {
    PARITY_ERROR = -1,
    PARITY_EVEN = 0,
    PARITY_ODD = 1
} Parity;

static Parity last_element_parity_after_operations(
    const int64_t array[],
    size_t length,
    uint64_t p)
{
    if (array == NULL || length == 0U) {
        return PARITY_ERROR;
    }

    if (p == 0U) {
        return (array[length - 1U] % INT64_C(2) != 0)
                   ? PARITY_ODD
                   : PARITY_EVEN;
    }

    return PARITY_EVEN;
}

int main(void)
{
    size_t length;
    uint64_t p;
    int64_t last = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%zu %" SCNu64, &length, &p) != 2 || length == 0U) {
        return 1;
    }

    for (size_t i = 0U; i < length; ++i) {
        int64_t value;

        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &value) != 1) {
            return 1;
        }

        last = value;
    }

    const Parity result =
        last_element_parity_after_operations(&last, 1U, p);

    if (result == PARITY_ERROR) {
        return 1;
    }

    if (printf("%s\n", result == PARITY_EVEN ? "Even" : "Odd") < 0) {
        return 1;
    }

    return 0;
}