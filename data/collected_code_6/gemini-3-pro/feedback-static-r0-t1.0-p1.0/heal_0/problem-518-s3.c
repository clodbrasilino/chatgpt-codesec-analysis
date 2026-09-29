#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool find_perfect_square_root(int64_t number, int64_t *result) {
    if (number < 0 || result == NULL) {
        return false;
    }

    if (number == 0 || number == 1) {
        *result = number;
        return true;
    }

    int64_t left = 1;
    int64_t right = number / 2;

    while (left <= right) {
        int64_t mid = left + (right - left) / 2;
        int64_t quotient = number / mid;
        int64_t remainder = number % mid;

        if (quotient == mid && remainder == 0) {
            *result = mid;
            return true;
        }

        if (mid < quotient) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

int main(void) {
    int64_t test_cases[] = {16, 25, 28, -4, 0, 1, 496};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int64_t result = 0;

    for (size_t i = 0; i < num_cases; ++i) {
        if (find_perfect_square_root(test_cases[i], &result)) {
            printf("%lld %lld\n", (long long)test_cases[i], (long long)result);
        } else {
            printf("%lld error\n", (long long)test_cases[i]);
        }
    }

    return 0;
}