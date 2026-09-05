#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long long find_min_sum(int *a, int *b, int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return 0;
    }

    qsort(a, n, sizeof(int), compare);
    qsort(b, n, sizeof(int), compare);

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long diff = (long long)a[i] - (long long)b[i];
        if (diff < 0) {
            sum -= diff;
        } else {
            sum += diff;
        }
    }

    return sum;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    if (a == NULL || b == NULL) {
        free(a);
        free(b);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            free(a);
            free(b);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &b[i]) != 1) {
            free(a);
            free(b);
            return 1;
        }
    }

    long long result = find_min_sum(a, b, n);
    printf("%lld\n", result);

    free(a);
    free(b);

    return 0;
}