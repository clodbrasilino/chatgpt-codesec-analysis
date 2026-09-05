#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int min_sum_abs_diff(int *a, int *b, int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return -1;
    }

    qsort(a, n, sizeof(int), compare);
    qsort(b, n, sizeof(int), compare);

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long diff = (long long)a[i] - (long long)b[i];
        if (diff < 0) {
            diff = -diff;
        }
        sum += diff;
    }

    if (sum > 2147483647) {
        return -1;
    }

    return (int)sum;
}

int main() {
    int a[] = {3, 2, 1};
    int b[] = {2, 1, 3};
    int n = sizeof(a) / sizeof(a[0]);

    int result = min_sum_abs_diff(a, b, n);
    printf("%d\n", result);

    return 0;
}