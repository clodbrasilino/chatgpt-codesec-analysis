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
        return (array[length - 1U] & INT64_C(1)) != 0
                   ? PARITY_ODD
                   : PARITY_EVEN;
    }

    return PARITY_EVEN;
}

int main(void)
{
    size_t length = 0U;
    uint64_t p = 0U;

    if (scanf("%zu %" SCNu64, &length, &p) != 2 || length == 0U) {
        return 1;
    }

    int64_t last = 0;

    for (size_t i = 0U; i < length; ++i) {
        int64_t value = 0;

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