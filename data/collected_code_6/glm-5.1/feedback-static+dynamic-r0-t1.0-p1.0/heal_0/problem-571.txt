#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int max_disjoint_pairs_sum(int *arr, int n, int k) {
    if (arr == NULL || n < 2 || k <= 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), cmp);

    int sum = 0;
    int pairs = 0;
    int i = 0;

    while (i <= n - 2 && pairs < k) {
        if (arr[i] > 0 && arr[i + 1] > 0) {
            sum += arr[i] + arr[i + 1];
            pairs++;
            i += 2;
        } else {
            i++;
        }
    }

    return sum;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 2;
    int res1 = max_disjoint_pairs_sum(arr1, n1, k1);
    printf("%d\n", res1);

    int arr2[] = {5, -2, 8, -1, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 2;
    int res2 = max_disjoint_pairs_sum(arr2, n2, k2);
    printf("%d\n", res2);

    int *arr3 = NULL;
    int n3 = 5;
    int k3 = 1;
    int res3 = max_disjoint_pairs_sum(arr3, n3, k3);
    printf("%d\n", res3);

    return 0;
}