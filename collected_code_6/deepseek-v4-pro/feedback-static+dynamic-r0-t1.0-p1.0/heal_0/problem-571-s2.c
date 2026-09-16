#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmp_desc(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

int sum_of_pairs(int arr[], int n, int k) {
    if (arr == NULL || n <= 0 || k <= 0 || n < 2 * k) {
        return -1;
    }

    qsort(arr, n, sizeof(int), cmp_desc);

    int sum = 0;
    int used = 0;
    int i = 0;

    while (used < k && i < n - 1) {
        sum += arr[i] + arr[i + 1];
        used++;
        i += 2;
    }

    if (used < k) {
        return -1;
    }

    return sum;
}

int main(void) {
    int arr1[] = {5, 2, 4, 8, 1, 9};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int k1 = 2;
    int result1 = sum_of_pairs(arr1, n1, k1);
    if (result1 != -1) {
        printf("%d\n", result1);
    } else {
        printf("Invalid input or not enough elements for pairs\n");
    }

    int arr2[] = {1, 2, 3, 4, 5, 6};
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int k2 = 3;
    int result2 = sum_of_pairs(arr2, n2, k2);
    if (result2 != -1) {
        printf("%d\n", result2);
    } else {
        printf("Invalid input or not enough elements for pairs\n");
    }

    int arr3[] = {10, 20, 30};
    int n3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int k3 = 2;
    int result3 = sum_of_pairs(arr3, n3, k3);
    if (result3 != -1) {
        printf("%d\n", result3);
    } else {
        printf("Invalid input or not enough elements for pairs\n");
    }

    return 0;
}