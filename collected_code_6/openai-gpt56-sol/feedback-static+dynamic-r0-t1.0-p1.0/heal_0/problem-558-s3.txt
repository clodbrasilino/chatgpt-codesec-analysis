#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t magnitude(int64_t value)
{
    return value < 0 ? (uint64_t)(-(value + 1)) + UINT64_C(1)
                     : (uint64_t)value;
}

static uint64_t digit_distance(int64_t first, int64_t second)
{
    uint64_t left = magnitude(first);
    uint64_t right = magnitude(second);
    uint64_t distance = 0;

    do {
        const uint64_t left_digit = left % UINT64_C(10);
        const uint64_t right_digit = right % UINT64_C(10);

        distance += left_digit > right_digit
                        ? left_digit - right_digit
                        : right_digit - left_digit;

        left /= UINT64_C(10);
        right /= UINT64_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

int main(void)
{
    int64_t first;
    int64_t second;

    if (scanf("%" SCNd64 " %" SCNd64, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return 1;
    }

    return 0;
}