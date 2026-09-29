#include <stdio.h>
#include <stddef.h>

static int find_kth(const int a[], size_t a_len,
                    const int b[], size_t b_len,
                    size_t k, int *result)
{
    size_t a_start = 0;
    size_t b_start = 0;

    if (result == NULL || (a == NULL && a_len != 0) ||
        (b == NULL && b_len != 0) || k == 0 ||
        k > a_len + b_len) {
        return 0;
    }

    while (a_start < a_len && b_start < b_len) {
        if (k == 1) {
            *result = a[a_start] <= b[b_start] ? a[a_start] : b[b_start];
            return 1;
        }

        size_t half = k / 2;
        size_t a_remaining = a_len - a_start;
        size_t b_remaining = b_len - b_start;
        size_t a_step = half < a_remaining ? half : a_remaining;
        size_t b_step = half < b_remaining ? half : b_remaining;

        if (a[a_start + a_step - 1] <= b[b_start + b_step - 1]) {
            a_start += a_step;
            k -= a_step;
        } else {
            b_start += b_step;
            k -= b_step;
        }
    }

    if (a_start < a_len) {
        *result = a[a_start + k - 1];
    } else {
        *result = b[b_start + k - 1];
    }

    return 1;
}

int main(void)
{
    const int a[] = {1, 3, 5, 7, 9};
    const int b[] = {2, 4, 6, 8, 10};
    const size_t k = 6;
    int result;

    if (!find_kth(a, sizeof(a) / sizeof(a[0]),
                  b, sizeof(b) / sizeof(b[0]),
                  k, &result)) {
        fputs("Unable to find the requested element.\n", stderr);
        return 1;
    }

    if (printf("%d\n", result) < 0) {
        return 1;
    }

    return 0;
}