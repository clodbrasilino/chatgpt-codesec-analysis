#include <stdio.h>
#include <stddef.h>

static int kth_element(const int *a, size_t a_len,
                       const int *b, size_t b_len,
                       size_t k, int *result)
{
    if (result == NULL || k == 0 || k > a_len + b_len) {
        return -1;
    }

    if ((a == NULL && a_len != 0) || (b == NULL && b_len != 0)) {
        return -1;
    }

    while (a_len > 0 && b_len > 0) {
        if (k == 1) {
            *result = a[0] < b[0] ? a[0] : b[0];
            return 0;
        }

        size_t a_step = k / 2;
        if (a_step > a_len) {
            a_step = a_len;
        }

        size_t b_step = k - a_step;
        if (b_step > b_len) {
            b_step = b_len;
            a_step = k - b_step;
        }

        if (a[a_step - 1] <= b[b_step - 1]) {
            a += a_step;
            a_len -= a_step;
            k -= a_step;
        } else {
            b += b_step;
            b_len -= b_step;
            k -= b_step;
        }
    }

    if (a_len == 0) {
        *result = b[k - 1];
    } else {
        *result = a[k - 1];
    }

    return 0;
}

int main(void)
{
    const int a[] = {1, 3, 5, 7, 9};
    const int b[] = {2, 4, 6, 8, 10};
    const size_t a_len = sizeof(a) / sizeof(a[0]);
    const size_t b_len = sizeof(b) / sizeof(b[0]);
    size_t k = 0;
    int result = 0;

    if (printf("Enter k: ") < 0) {
        return 1;
    }

    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (kth_element(a, a_len, b, b_len, k, &result) != 0) {
        fprintf(stderr, "k is out of range\n");
        return 1;
    }

    if (printf("%d\n", result) < 0) {
        return 1;
    }

    return 0;
}