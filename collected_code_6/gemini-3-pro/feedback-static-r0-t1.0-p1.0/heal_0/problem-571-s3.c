#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long long max_disjoint_pairs_sum(int arr[], size_t n, int k) {
    if (arr == NULL || n < 2) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare_ints);

    long long sum = 0;
    size_t i = n - 1;

    while (i > 0) {
        if (arr[i] - arr[i - 1] < k) {
            sum += (long long)arr[i] + (long long)arr[i - 1];
            if (i >= 2) {
                i -= 2;
            } else {
                break;
            }
        } else {
            i--;
        }
    }

    return sum;
}

int main(void) {
    int arr[] = {3, 5, 10, 15, 17, 12, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    long long result = max_disjoint_pairs_sum(arr, n, k);
    printf("%lld\n", result);

    int arr2[] = {5, 15, 10, 300};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 12;

    long long result2 = max_disjoint_pairs_sum(arr2, n2, k2);
    printf("%lld\n", result2);

    return 0;
}