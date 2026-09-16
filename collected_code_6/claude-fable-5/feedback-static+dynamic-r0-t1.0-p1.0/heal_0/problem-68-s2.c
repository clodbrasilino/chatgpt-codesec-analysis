#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_monotonic(const int *arr, size_t n)
{
    bool increasing = true;
    bool decreasing = true;
    size_t i;

    if (arr == NULL || n < 2U) {
        return true;
    }

    for (i = 1U; i < n; i++) {
        if (arr[i] > arr[i - 1U]) {
            decreasing = false;
        }
        if (arr[i] < arr[i - 1U]) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

int main(void)
{
    const int a[] = {1, 2, 2, 3, 7};
    const int b[] = {9, 5, 5, 3, 1};
    const int c[] = {1, 3, 2, 4, 5};
    const int d[] = {42};

    if (is_monotonic(a, sizeof(a) / sizeof(a[0]))) {
        (void)printf("Array a is monotonic\n");
    } else {
        (void)printf("Array a is not monotonic\n");
    }

    if (is_monotonic(b, sizeof(b) / sizeof(b[0]))) {
        (void)printf("Array b is monotonic\n");
    } else {
        (void)printf("Array b is not monotonic\n");
    }

    if (is_monotonic(c, sizeof(c) / sizeof(c[0]))) {
        (void)printf("Array c is monotonic\n");
    } else {
        (void)printf("Array c is not monotonic\n");
    }

    if (is_monotonic(d, sizeof(d) / sizeof(d[0]))) {
        (void)printf("Array d is monotonic\n");
    } else {
        (void)printf("Array d is not monotonic\n");
    }

    return 0;
}