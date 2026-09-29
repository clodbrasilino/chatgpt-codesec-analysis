#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DIGITS_BUF_SIZE 32

long long next_bigger(long long n)
{
    char digits[DIGITS_BUF_SIZE];
    int len;
    int i;
    int pivot;
    int swap_idx;
    char tmp;
    int lo;
    int hi;
    long long result;

    if (n < 0) {
        return -1;
    }

    memset(digits, 0, sizeof(digits));

    len = snprintf(digits, sizeof(digits), "%lld", n);
    if (len < 0 || (size_t)len >= sizeof(digits)) {
        return -1;
    }

    pivot = -1;
    for (i = len - 2; i >= 0; i--) {
        if (digits[i] < digits[i + 1]) {
            pivot = i;
            break;
        }
    }

    if (pivot == -1) {
        return -1;
    }

    swap_idx = -1;
    for (i = len - 1; i > pivot; i--) {
        if (digits[i] > digits[pivot]) {
            swap_idx = i;
            break;
        }
    }

    if (swap_idx == -1) {
        return -1;
    }

    if (pivot >= DIGITS_BUF_SIZE || swap_idx >= DIGITS_BUF_SIZE) {
        return -1;
    }

    tmp = digits[pivot];
    digits[pivot] = digits[swap_idx];
    digits[swap_idx] = tmp;

    lo = pivot + 1;
    hi = len - 1;
    while (lo < hi && lo >= 0 && hi < DIGITS_BUF_SIZE) {
        tmp = digits[lo];
        digits[lo] = digits[hi];
        digits[hi] = tmp;
        lo++;
        hi--;
    }

    result = 0;
    for (i = 0; i < len && i < DIGITS_BUF_SIZE; i++) {
        int d = digits[i] - '0';
        if (d < 0 || d > 9) {
            return -1;
        }
        if (result > (LLONG_MAX - d) / 10) {
            return -1;
        }
        result = result * 10 + d;
    }

    return result;
}

int main(void)
{
    long long inputs[] = {12LL, 513LL, 2017LL, 414LL, 144LL, 9LL, 111LL, 531LL};
    size_t count = sizeof(inputs) / sizeof(inputs[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        long long res = next_bigger(inputs[i]);
        if (res == -1) {
            if (printf("%lld -> no bigger number possible\n", inputs[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("%lld -> %lld\n", inputs[i], res) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}